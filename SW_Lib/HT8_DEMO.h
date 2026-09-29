/*******************************************************************************
  * @file     HT8_DEMO.h
  * @brief    The header file of the DEMO library.
  * @author   Holtek Semiconductor Inc.
  * @version  V1.0.0
  * @date     2023-2-7
 *******************************************************************************
  * @attention
  *
  * Firmware Disclaimer Information

  * 1. The customer hereby acknowledges and agrees that the program technical
  *    documentation, including the code, which is supplied by 
  *    Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") 
  *    is the proprietary and confidential intellectual property of HOLTEK,
  *    and is protected by copyright law and other intellectual property laws.
  *
  * 2. The customer hereby acknowledges and agrees that the program technical
  *    documentation, including the code, is confidential information belonging
  *    to HOLTEK, and must not be disclosed to any third parties other than
  *    HOLTEK and the customer.
  *
  * 3. The program technical documentation, including the code,
  *    is provided "as is" and for customer reference only.
  *    After delivery by HOLTEK, the customer shall use the program
  *    technical documentation,including the code, at their own risk.
  *    HOLTEK disclaims any expressed, implied or statutory warranties,
  *    including the warranties of merchantability,
  *    satisfactory quality and fitness for a particular purpose.
  *
  * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 ******************************************************************************/

/* Define to prevent recursive inclusion--------------------------------------*/
#ifndef _HT8_DEMO_H_
#define _HT8_DEMO_H_

/* Includes-------------------------------------------------------------------*/
#include "HT8_MCU_IP_SEL.h"

/* Exported constants---------------------------------------------------------*/
#ifndef Indicator_pin
#define Indicator_pin           _acc
#endif

/* Exported functions---------------------------------------------------------*/
/* For public */
void DEMO_Init(void);
void DEMO_Setting(void);

/* For ADC function Demo */
void ADC_InterruptMode_Demo(void);
void ADC_PollingMode_Demo(void);

/* For External Interrupt function Demo */
void EINT_PollingMode_Demo(void);
void EINT_InterruptMode_Demo(void);

/* For EEPROM function Demo */
void EEPROM_Write_Read_Demo(void);

/* For System Clock function Demo */
void SYS_Clock_Demo(void);

/* For LVR function Demo */
void LVR_Demo(void);

/* For LVD function Demo */
void LVD_PollingMode_Demo(void);

/* For WDT function Demo */
void WDT_Halt_TO_Demo(void);

/* For TimeBase function Demo */
void TIMEBASE_PollingMode_Demo(void);

/* For STM function Demo */
void STM_Timer_Counter_PollingMode_Demo(void);
void STM_Single_Pulse_Output_Mode_Demo(void);
void STM_Capture_Input_InterruptMode_Demo(void);

/* For PTM function Demo */
void PTM_Timer_Counter_PollingMode_Demo(void);
void PTM_Single_Pulse_Output_Mode_Demo(void);
void PTM_Capture_Input_InterruptMode_Demo(void);

/* For S/W UART function Demo */
void SW_UART_Receive_Transmit_Demo(void);

/* For USIM function Demo */
void USIM_UART_Receive_Transmit_Demo(void);
void USIM_SPI_Master_PollingMode_Demo(void);

/* For SW I2C Master function Demo */
void SW_I2C_Master_Demo(void);

/* For SW SPI Master function Demo */
void SW_SPI_Master_Demo(void);

extern vu16 g_ADC_ISR_Value;        /*AD conversion value (Interrupt)*/
extern vu8  g_ADC_Finish;           /*AD conversion complete flag*/
extern u16  g_ConversionValue;      /*AD conversion value*/

extern u8   g_EEPROM_DATA;          /*EEPROM Byte Write/Read data*/
extern vu8  g_EEPROM_WR_Finish;     /*EEPEOM Wirte and read complete flag*/


extern vu8  g_USIM_UART_RX_FLAG;    /*USIM UART receive success flag*/


extern vu8  g_SW_UART_RX_Data;
extern vu8  g_SW_UART_RX_Status;

extern vu8  g_SW_I2C_complete_flag;
extern vu8  g_SW_I2C_RX_Data;

extern vu8  g_PTM_Capture_Finish;   /*PTM capture complete flag*/
extern vu16 g_PTM_ISR_Value[2];     /*PTM capture value(ISR)*/
extern vu8  g_PTM_Capture_cnt;      /*PTM capture count*/
extern vu8  g_PTM_CCRP_OV_cnt;      /*PTM CCRP overflow count*/

extern vu8  g_STM_Capture_Finish;   /*STM capture complete flag*/
extern vu16 g_STM_ISR_Value[2];     /*STM capture value(ISR)*/
extern vu8  g_STM_Capture_cnt;      /*STM capture count*/
extern vu8  g_STM_CCRP_OV_cnt;      /*STM CCRP overflow count*/

extern vu8  g_SW_SPI_Tx_Buf;
extern vu8  g_SW_SPI_Rx_Buf;


#endif
/*********** (C) COPYRIGHT 2019 Holtek Semiconductor Inc **********END OF FILE*/
