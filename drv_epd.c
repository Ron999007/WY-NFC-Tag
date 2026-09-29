#include "SW_Lib/ht8_usim.h"
#include "drv_epd.h"
#include "sys_tick.h"

#define SPI_TRANS_FUNC(x)  USIM_SPI_MasterSendData(x)

/**
 * @brief Hardware states for non-blocking background task.
 */
typedef enum {
    EPD_HW_STATE_IDLE = 0,
    EPD_HW_STATE_REFRESHING,
    EPD_HW_STATE_POWER_OFF
} EPD_HwState_t;

static volatile EPD_HwState_t epd_hw_state = EPD_HW_STATE_IDLE;

/**
 * @brief  Software delay loop for timing requirements.
 *         Clears watchdog to prevent MCU reset during long delays.
 * @param  ms: Delay time in milliseconds.
 * @retval None
 */
static void EPD_DelayMs(u16 ms)
{
    GCC_CLRWDT();
    SysTick_DelayMs(ms);
    GCC_CLRWDT();
}

/**
 * @brief  Send a command byte to the E-paper controller via Hardware USIM SPI.
 * @param  cmd: Command byte.
 * @retval None
 */
static void EPD_WriteCmd(u8 cmd)
{
    EPD_CS_PIN = 0;
    EPD_DC_PIN = 0;
    
    SPI_TRANS_FUNC(cmd);
    
    EPD_CS_PIN = 1;
}

/**
 * @brief  Send a data byte to the E-paper controller via Hardware USIM SPI.
 * @param  data: Data byte.
 * @retval None
 */
static void EPD_WriteData(u8 data)
{
    EPD_CS_PIN = 0;
    EPD_DC_PIN = 1;
    
    SPI_TRANS_FUNC(data);
    
    EPD_CS_PIN = 1;
}

/**
 * @brief  Safe wait with timeout for EPD busy pin to become FREE (High).
 *         Active low: 0 = BUSY, 1 = FREE.
 * @retval None
 */
static void EPD_SafeWaitIdle(void)
{
    u32 timeout = 40000000;
    
    GCC_CLRWDT();      
    SysTick_DelayMs(5); 

    while((EPD_BUSY_PIN == 0) && (timeout > 0))
    {
        timeout--;
        if ((timeout % 5000) == 0) 
        {
            GCC_CLRWDT(); 
        }
    }
    GCC_CLRWDT();
}

/**
 * @brief  Initialize the GPIO ports and the Hardware USIM SPI module.
 * @retval None
 */
void EPD_HardwareInit(void)
{
    EPD_CS_DIR = 0;
    EPD_DC_DIR = 0;  
    EPD_RST_DIR = 0; 
    EPD_BUSY_DIR = 1;

    EPD_CS_PIN = 1;
    
    /* Initialize Hardware USIM in SPI Master mode */
    USIM_SIM_Init();
}

/**
 * @brief  Common reset and power-on routine.
 *         Configures panel settings, resolution, and power settings.
 * @retval None
 */
void drv_EPD_Init(void)
{
    EPD_HardwareInit();

    /* Hardware Reset */
    EPD_DelayMs(100);
    EPD_RST_PIN = 0;
    EPD_DelayMs(20);
    EPD_RST_PIN = 1;
    EPD_DelayMs(20);

    EPD_SafeWaitIdle();

    /* Panel Setting (PSR) */
    EPD_WriteCmd(0x00);
    EPD_WriteData(0x13); /* KW/R mode, Scan down, Shift left */
    EPD_WriteData(0x8D); /* Default VCOM behavior */
    
    /* Power Setting (PWR) */
    //EPD_WriteCmd(0x01);
    //EPD_WriteData(0x03); 
    //EPD_WriteData(0x13);
    //EPD_WriteData(0x3F); 
    //EPD_WriteData(0x3F);
    //EPD_WriteData(0x0D);

    /* Resolution Setting (TRES): 240 x 416 */
    EPD_WriteCmd(0x61);
    EPD_WriteData(0xF0); /* HRES = 240 */
    EPD_WriteData(0x01); /* VRES_H = 416 >> 8 */
    EPD_WriteData(0xA0); /* VRES_L = 416 & 0xFF */
    
    /* Booster soft start */
	//EPD_WriteCmd(0x06); // Booster Soft Start (BTST) 
	//EPD_WriteData(0x87); // Phase A: 30ms, Strength 1 
	//EPD_WriteData(0x8F); // Phase B: 30ms, Strength 2 
	//EPD_WriteData(0x17); // Phase C: Strength 3
    
    /* VCOM and Data Interval Setting (CDI) */
    EPD_WriteCmd(0x50);
    EPD_WriteData(0xD7); /* Default VCOM and 10 Hsync */

    /* Note: We do NOT send Power On (0x04) here because we will use 
       Auto Sequence (0x17) which handles Power On automatically. */
    /* Power on */
    //EPD_WriteCmd(0x04); 
    //EPD_SafeWaitIdle();
}

/**
 * @brief  Initialize for Partial Refresh. 
 * @retval None
 */
void drv_EPD_Init_Partial(void)
{
    EPD_WriteCmd(0x04); /* Power on */
    EPD_SafeWaitIdle();
    EPD_WriteCmd(0x13); /* Prepare for partial window */
}

/**
 * @brief  Prepares the EPD SRAM by writing OLD data (0xFF) first,
 *         then prepares to receive NEW data.
 * @retval None
 */
void drv_EPD_StartFrame(void)
{
    u16 i;

    /* DTM1(0x10): Write OLD Image Data (Clear with white) */
    EPD_WriteCmd(0x10);
    
    /* Optimized SPI burst to reduce CS/DC toggling */
    EPD_CS_PIN = 0;
    EPD_DC_PIN = 1;

    for(i = 0; i < 12480; i++) /* 240 * 416 / 8 = 12480 bytes */
    {
        GCC_CLRWDT();
        SPI_TRANS_FUNC(0xFF);
    }
    EPD_CS_PIN = 1;

    /* DTM2(0x13): Prepare to receive NEW Image Data */
    EPD_WriteCmd(0x13); 
}

/**
 * @brief  Writes a block of image data bytes into the EPD SRAM.
 * @param  data: Pointer to the image data array.
 * @param  len: Number of bytes to transmit.
 * @retval None
 */
void drv_EPD_SendDataBlock(u8 *data, u8 len)
{
    u8 i;
    EPD_CS_PIN = 0;
    EPD_DC_PIN = 1;

    for(i = 0; i < len; i++)
    {
        SPI_TRANS_FUNC(data[i]);
    }
    EPD_CS_PIN = 1;
}

/**
 * @brief  Triggers screen refresh. Uses Auto Sequence for NFC passive mode.
 * @retval None
 */
void drv_EPD_Update_Trigger(void)
{
    /* AUTO(0x17): Auto Sequence. 
       Automatically executes PON -> DRF -> POF -> DSLP 
       Highly recommended for NFC passive systems to save MCU power. */
    EPD_WriteCmd(0x17);
    EPD_WriteData(0xA7);
    
    epd_hw_state = EPD_HW_STATE_IDLE; /* Controller handles the rest */
    
    
    //EPD_WriteCmd(0x12);           
    //epd_hw_state = EPD_HW_STATE_REFRESHING;
}

/**
 * @brief  Triggers partial screen refresh following official timing.
 * @retval None
 */
void drv_EPD_Update_Partial_Trigger(void)
{
    /* PTIN (0x91): Partial In */
    EPD_WriteCmd(0x91);  
    
    /* PTL (0x90): Partial Window Configuration (7 Bytes required) */
    EPD_WriteCmd(0x90);
    EPD_WriteData(0);          /* X_Start = 0 */
    EPD_WriteData(29);         /* X_End = 29 (240/8 - 1) */
    EPD_WriteData(0);          /* Y_Start MSB = 0 */
    EPD_WriteData(0);          /* Y_Start LSB = 0 */
    EPD_WriteData(415 >> 8);   /* Y_End MSB = 1 */
    EPD_WriteData(415 & 0xFF); /* Y_End LSB = 159 (0x9F) */
    EPD_WriteData(0x01);       /* PT_SCAN = 0x01 (Only scan partial window) */

    /* DRF(0x12): Display Refresh */
    EPD_WriteCmd(0x12);               
    epd_hw_state = EPD_HW_STATE_REFRESHING;
}

/**
 * @brief  Puts the EPD controller into Deep Sleep mode (0x07) manually.
 * @retval None
 */
void drv_EPD_Sleep(void)
{
    /* POF(0x02): Power OFF command */
    EPD_WriteCmd(0x02);
    EPD_SafeWaitIdle();
    
    /* DSLP(0x07): Deep Sleep command with check code 0xA5 */
    EPD_WriteCmd(0x07);
    EPD_WriteData(0xA5);
    
    epd_hw_state = EPD_HW_STATE_IDLE;
}

/**
 * @brief  Non-blocking background polling task for EPD completion.
 *         (Left empty as Auto Sequence handles the flow now)
 * @retval None
 */
/**
 * @brief  Non-blocking background polling task for EPD completion.
 */
void drv_EPD_Background_Task(void)
{
    if (epd_hw_state == EPD_HW_STATE_IDLE) return;
    
    if (EPD_BUSY_PIN == 0) return;

    switch (epd_hw_state)
    {
        case EPD_HW_STATE_REFRESHING:
            SysTick_DelayMs(10);
            if (EPD_BUSY_PIN == 0) return;
            
            /* PTOUT (0x92): Partial Out (退出局部刷新模式) */
            /* 必須在 BUSY 拉高 (刷新結束) 後發送，確保 IC 狀態正常 */
            EPD_WriteCmd(0x92);
            
            /* POF(R02H): Power OFF[cite: 2] */
            EPD_WriteCmd(0x02);
            epd_hw_state = EPD_HW_STATE_POWER_OFF;
            break;

        case EPD_HW_STATE_POWER_OFF:
            SysTick_DelayMs(10);
            if (EPD_BUSY_PIN == 0) return;
            
            /* DSLP(R07H): Deep Sleep[cite: 2] */
            //EPD_WriteCmd(0x07);
            //EPD_WriteData(0xA5); 
            epd_hw_state = EPD_HW_STATE_IDLE;
            break;

        default:
            epd_hw_state = EPD_HW_STATE_IDLE;
            break;
    }
}