#include "cc_generated_files\CodeConfig.h"
#include "task_nfc_passthrough.h"
#include "A9225-A.h"
#include "drv_epd.h"
#include "sys_tick.h"
#include "HT66L2550A.h"
//#include "uart_printf.h"

/* Hardware FD (Field Detect) Pin Mapping */
#define NFC_FD_PIN _pa3

/* 
 * Static buffer for continuous packet processing.
 * Using a single 64-byte unified array directly maps to the BC45B4211 SRAM 
 * without needing extra memory-copy operations, saving HT66L2550A RAM overhead.
 */
static u8 sram_buf[PROTOCOL_PACKET_SIZE];
u32 gu32_nfc_timer;

/*******************************************************************************
 * @brief    Calculate the actual input voltage in millivolts (mV) using integer math.
 * @param    adc_raw_value: The 12-bit ADC raw data from AN3 (0 ~ 4095).
 * @retval   Actual pre-divider voltage in millivolts (mV).
 *******************************************************************************/
unsigned int Calculate_Input_Voltage_mV(unsigned int adc_raw_value)
{
    unsigned long voltage_mv = 0;

    /* Step 1: Calculate voltage at the MCU pin in mV */
    /* Cast to 32-bit (unsigned long) to prevent overflow during multiplication */
    voltage_mv = ((unsigned long)adc_raw_value * VREF_MV) / ADC_MAX_STEP;

    /* Step 2: Compensate for the external hardware voltage divider */
    /* Multiply by 23, then divide by 3 to restore the original voltage */
    voltage_mv = (voltage_mv * DIVIDER_MULT) / DIVIDER_DIV;

    /* Cast back to 16-bit integer since max voltage ~10000mV fits in 16 bits */
    return (unsigned int)voltage_mv;
}

/* ====================================================================
 * Local CRC16 Utility
 * ==================================================================== */
/**
 * @brief Calculate CRC16 for data integrity check
 */
static u16 tag_crc16(u8 *data, u16 len, u16 init_val) {
    u16 crc = init_val;
    u16 i;
    u8 j;
    
    for (i = 0; i < len; i++) {
        crc ^= (u16)data[i];
        for (j = 0; j < 8; j++) {
            if (crc & 0x0001) crc = (crc >> 1) ^ 0x8408;
            else              crc >>= 1;
        }
    }
    return crc;
}

void Task_NFC_PassThrough_Init(void)
{
	u8 dummy_buf[16];
   
    /* 1. Force SRAM ownership to I2C side (Disable PTHRU, set DIR to I2C) */
    A9225A_RegisterWrite(0xFE, 0x00, 0xFF, 0x01);
    
    /* Short delay for internal Tag state machine switching */
    SysTick_DelayMs(10); 

    /* 2. Dummy read the last SRAM block (0xFB) to force FD pin release */
    /* Because ownership is now I2C, this will ACK and read successfully */
    A9225A_MemoryRead(0xFB, dummy_buf);

    /* 3. Hand SRAM ownership back to NFC side and enable Pass-Through */
    /* 0x7D = PTHRU_ON | FD_OFF(11b) | FD_ON(11b) | TRANSFER_DIR(NFC->I2C) */
    A9225A_RegisterWrite(0xFE, 0x00, 0xFF, 0x7D);
    
    //UART_PrintStr("[NFC] Pass-Through Task Initialized.\r\n");
}

void Task_NFC_PassThrough_Process(void)
{
	u16 timeout;
	unsigned int vol_mv = 0;
	
	/* When FD pin is pulled low (NFC data from Reader is ready in SRAM) */
    if (NFC_FD_PIN == 0) {
        
        /* Clear Watchdog during intensive data transfer */
        GCC_CLRWDT(); 
        gu32_nfc_timer = SysTick_GetTicks();
        
        /* Read 64 bytes directly into the unified sram_buf array via pointer offsets */
        /* Hardware direction is already Rx (0x7D) */
        A9225A_MemoryRead(0xF8, &sram_buf[0]);
        A9225A_MemoryRead(0xF9, &sram_buf[16]);
        A9225A_MemoryRead(0xFA, &sram_buf[32]);
        A9225A_MemoryRead(0xFB, &sram_buf[48]);
        
        /* Extract Protocol Header */
        u8 cmd = sram_buf[0];
        u16 pkt_idx = sram_buf[1] | ((u16)sram_buf[2] << 8);
        
        /* Calculate and Verify CRC (over the first 62 bytes) */
        u16 calc_crc = tag_crc16(sram_buf, 62, 0x6363);
        u16 rx_crc   = sram_buf[62] | ((u16)sram_buf[63] << 8);
        
        u8 process_status = STATUS_FAIL;
        
        if (calc_crc == rx_crc) {
            process_status = STATUS_PASS;
            
            /* ====================================================
             * Application Command Dispatcher
             * ==================================================== */
            switch (cmd) {
				case CMD_INIT_EPD:
                    drv_EPD_Init();
                    drv_EPD_StartFrame();
                    
                    sram_buf[4] = TAG_FW_VER_MAJOR;
                    sram_buf[5] = TAG_FW_VER_MINOR;
                    sram_buf[6] = TAG_FW_VER_PATCH;
                    break;
                    
                case CMD_IMG_TRANSFER:
                    drv_EPD_SendDataBlock(&sram_buf[3], PROTOCOL_PAYLOAD_SIZE);
                    break;
                    
                case CMD_POLL_VOLTAGE:
                    /* Read ADC and encode 16-bit voltage into payload [Byte 4, 5] */
                    vol_mv = Calculate_Input_Voltage_mV(ADC_GetChannelValue(3));
                    sram_buf[4] = (u8)(vol_mv & 0xFF);
                    sram_buf[5] = (u8)((vol_mv >> 8) & 0xFF);
                    break;
                    
                case CMD_UPDATE_EPD:
                    /* Reader confirmed voltage is sufficient, execute EPD refresh */
                    drv_EPD_Update_Trigger();
                    break;
                    
                case CMD_UPDATE_FAIL:
                    /* Reader timed out (10s), aborting update process */
                    /* Optional: Sleep or reset EPD state machine here */
                    break;
                    
                case CMD_FW_UPGRADE:
                    /* TODO: Implement Firmware OTA Flash Write for HT66L2540A */
                    // IAP_WriteFlashChunk(pkt_idx, &sram_buf[3], PROTOCOL_PAYLOAD_SIZE);
                    break;
                    
                default:
                    process_status = STATUS_FAIL;
                    break;
            }
        }
        
        /* Prepare ACK Frame Response inside the same buffer */
        sram_buf[0] = cmd | CMD_ACK_MASK;          /* Mask command with 0x80 (e.g., 0x81) */
        sram_buf[1] = (u8)(pkt_idx & 0xFF);        /* Echo Index LSB */
        sram_buf[2] = (u8)((pkt_idx >> 8) & 0xFF); /* Echo Index MSB */
        sram_buf[3] = process_status;              /* Data Integrity Verification Status */
        
        /* Switch TRANSFER_DIR to Tx Mode (I2C -> NFC) */
        A9225A_RegisterWrite(0xFE, 0x00, 0xFF, 0x7C);
        
        /* Write the 64-byte ACK frame directly from sram_buf back to SRAM */
        A9225A_MemoryWrite(0xF8, &sram_buf[0]);
        A9225A_MemoryWrite(0xF9, &sram_buf[16]);
        A9225A_MemoryWrite(0xFA, &sram_buf[32]);
        A9225A_MemoryWrite(0xFB, &sram_buf[48]);
        
        /* Block until Reader reads the SRAM via RF */
        timeout = 60000;
        while (NFC_FD_PIN == 1 && timeout > 0) { 
            GCC_CLRWDT(); 
            timeout--;
        }
        
        /* Force SRAM ownership to I2C side (Disable PTHRU, set DIR to I2C) */
	    A9225A_RegisterWrite(0xFE, 0x00, 0xFF, 0x01);
	    
	    /* Short delay for internal Tag state machine switching */
	    SysTick_DelayMs(1); 
	
	    /* Dummy read the last SRAM block (0xFB) to force FD pin release */
	    /* Because ownership is now I2C, this will ACK and read successfully */
	    A9225A_MemoryRead(0xFB, &sram_buf[48]);
        
        /* Revert back to Rx Mode (NFC -> I2C) for the next packet */
        A9225A_RegisterWrite(0xFE, 0x00, 0xFF, 0x7D);
        
        timeout = 60000;
        while (NFC_FD_PIN == 0 && timeout > 0) { 
            GCC_CLRWDT(); 
            timeout--;
        }
    }
}