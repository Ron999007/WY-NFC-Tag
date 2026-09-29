#include "cc_generated_files\CodeConfig.h"
#include "task_nfc_passthrough.h"
#include "A9225-A.h"
#include "drv_epd.h"
//#include "uart_printf.h"
#include "sys_tick.h"
#include "HT66L2550A.h"

/* Hardware FD (Field Detect) Pin Mapping */
#define NFC_FD_PIN _pa3

/* EPD Image Transmission Constants */
#define EPD_TOTAL_BYTES  12480
#define CHUNK_SIZE       64
#define TOTAL_CHUNKS     (EPD_TOTAL_BYTES / CHUNK_SIZE) /* 195 chunks */

u32 gu32_nfc_timer;

/* 
 * Extern buffers defined in A9225-A.c to save RAM space. 
 * Reusing these arrays prevents memory overflow on HT66L2550A.
 */
extern u8 g_SRAM_Data_1[16];
extern u8 g_SRAM_Data_2[16];
extern u8 g_SRAM_Data_3[16];
extern u8 g_SRAM_Data_4[16];

/* State Machine Enumeration for NFC streaming */
typedef enum {
    NFC_STATE_WAIT_FIRST_PACKET = 0,
    NFC_STATE_STREAMING,
    NFC_STATE_REFRESH_EPD
} NFC_Task_State_t;

static NFC_Task_State_t nfc_state = NFC_STATE_WAIT_FIRST_PACKET;
static u16 received_chunks = 0;

void Task_NFC_PassThrough_Init(void)
{
    received_chunks = 0;
    nfc_state = NFC_STATE_WAIT_FIRST_PACKET;
    
    /* Initialize Pass-Through mode on BC45B4211 */
    NFC_Tag_PassThrough_Init();
    
    //UART_PrintStr("[NFC] Pass-Through Task Initialized.\r\n");
}

void Task_NFC_PassThrough_Process(void)
{
//	u8 i;
	
    switch(nfc_state)
    {
        case NFC_STATE_WAIT_FIRST_PACKET:
            /* Wait for the first FD falling edge indicating NFC write from Reader */
            if (NFC_FD_PIN == 0)
            {
                //UART_PrintStr("[NFC] First packet detected. Init EPD...\r\n");
                
                /* Initialize EPD and clear old data from SRAM */
                drv_EPD_Init();
                drv_EPD_StartFrame();

                /* Transition to streaming state immediately to process this first packet */
                nfc_state = NFC_STATE_STREAMING;
                received_chunks = 0;
            }
            break;

        case NFC_STATE_STREAMING:
            /* Poll the FD pin to detect when 64-byte SRAM is full */
            if (NFC_FD_PIN == 0)
            {
            	gu32_nfc_timer = SysTick_GetTicks();
                /* Clear Watchdog during intensive data transfer */
                GCC_CLRWDT(); 

                /* Step 1: Switch SRAM ownership to I2C */
                A9225A_RegisterWrite(0xFE, 0x00, 0xFF, 0x01);

                /* Step 2: Read 64 bytes from SRAM (Blocks 0xF8 to 0xFB) */
                A9225A_MemoryRead(0xF8, g_SRAM_Data_1);
                A9225A_MemoryRead(0xF9, g_SRAM_Data_2);
                A9225A_MemoryRead(0xFA, g_SRAM_Data_3);
                A9225A_MemoryRead(0xFB, g_SRAM_Data_4);
#if 0                
                for(i=0; i<16; i++){
                	if(g_SRAM_Data_1[i] != i) _pb5 = 0;	
                	_pb5 = 1;
               	}
               	
                for(i=0; i<16; i++){
                	if(g_SRAM_Data_2[i] != (i+16)) _pb5 = 0;	
                	_pb5 = 1;
               	}
               	
                for(i=0; i<16; i++){
                	if(g_SRAM_Data_3[i] != (i+32)) _pb5 = 0;	
                	_pb5 = 1;
               	}               	               	
 
                for(i=0; i<16; i++){
                	if(g_SRAM_Data_4[i] != (i+48)) _pb5 = 0;	
                	_pb5 = 1;
               	}
#endif               	                
                /* Step 3: Stream data to EPD via SPI */
                drv_EPD_SendDataBlock(g_SRAM_Data_1, 16);
                drv_EPD_SendDataBlock(g_SRAM_Data_2, 16);
                drv_EPD_SendDataBlock(g_SRAM_Data_3, 16);
                drv_EPD_SendDataBlock(g_SRAM_Data_4, 16);

                /* Step 4: Return SRAM ownership to NFC for the next chunk */
                A9225A_RegisterWrite(0xFE, 0x00, 0xFF, 0x7D);

                received_chunks++;

                /* Check if the entire image (195 chunks) has been received */
                if (received_chunks >= TOTAL_CHUNKS)
                {
                    //UART_PrintStr("[NFC] All chunks received. Refreshing EPD...\r\n");
                    nfc_state = NFC_STATE_REFRESH_EPD;
                }
            }
            
            if((SysTick_GetTicks()-gu32_nfc_timer) >= 10000)	// 320 ms
            {
				Task_NFC_PassThrough_Init();            	
            }
            break;

        case NFC_STATE_REFRESH_EPD:
            /* Trigger physical refresh on the E-Paper display */
            drv_EPD_Update_Trigger();
            
            /* Reset state to wait for the next NFC tap */
            received_chunks = 0;
            nfc_state = NFC_STATE_WAIT_FIRST_PACKET;
            //nfc_state = NFC_STATE_WAIT;
            break;

        default:
            nfc_state = NFC_STATE_WAIT_FIRST_PACKET;
            break;
    }
}