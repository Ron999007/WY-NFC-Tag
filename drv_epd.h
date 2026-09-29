#ifndef DRV_EPD_H
#define DRV_EPD_H

//#include "cc_generated_files\CodeConfig.h"
#include "SW_Lib/HT8_Type.h"

/* =========================================================================
 * Hardware Pin Mapping for HT66F2390 E-Paper Control Interface
 * SIM Hardware SPI Pins:
 * SCK  = PC3
 * SDO  = PC2
 * SDI  = PB7
 * ========================================================================= */

#define EPD_CS_PIN    _pc0
#define EPD_CS_DIR    _pcc0

#define EPD_BUSY_PIN  _pd0
#define EPD_BUSY_DIR  _pdc0

#define EPD_RST_PIN   _pd1
#define EPD_RST_DIR   _pdc1

#define EPD_DC_PIN    _pc1
#define EPD_DC_DIR    _pcc1

/**
 * @brief Structure for table-driven EPD initialization commands.
 */
typedef struct {
    u8 cmd;          
    u8 data_len;     
    u8 data_bytes[8]; 
    u8 wait_idle;    
    u16 delay_ms;    
} EPD_InitCmd_t;

/**
 * @brief Initialize EPD hardware GPIO pins and SPI module.
 * @param None
 * @retval None
 */
void drv_EPD_HardwareInit(void);

/**
 * @brief Execute standard initialization sequence for UC8253.
 * @param None
 * @retval None
 */
void drv_EPD_Init(void);

/**
 * @brief Prepares EPD for Partial Refresh without hardware reset to retain RAM.
 * @param None
 * @retval None
 */
void drv_EPD_Init_Partial(void);

/**
 * @brief Execute fast initialization sequence for UC8253 (No flashing).
 * @param None
 * @retval None
 */
void drv_EPD_Init_Fast(void);

/**
 * @brief Prepares EPD SRAM by configuring resolution windows and clearing OLD data.
 * @param None
 * @retval None
 */
void drv_EPD_StartFrame(void);

/**
 * @brief Writes a block of image data into the EPD SRAM via Hardware SIM.
 * @param data: Pointer to the image data array.
 * @param len: Number of bytes to write.
 * @retval None
 */
void drv_EPD_SendDataBlock(u8 *data, u8 len);

/**
 * @brief Triggers partial screen refresh.
 * @param None
 * @retval None
 */
void drv_EPD_Update_Partial_Trigger(void);

/**
 * @brief Triggers screen refresh following official timing.
 * @param None
 * @retval None
 */
void drv_EPD_Update_Trigger(void);

/**
 * @brief  Puts the EPD controller into Deep Sleep mode (0x07) for ultra-low power consumption.
 * Note: SRAM contents will be lost upon entering Deep Sleep.
 * @param  None
 * @retval None
 */
void drv_EPD_Sleep(void);

/**
 * @brief Non-blocking background polling task for EPD completion.
 * @param None
 * @retval None
 */
void drv_EPD_Background_Task(void);

#endif /* DRV_EPD_H */