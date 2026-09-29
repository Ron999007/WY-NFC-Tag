/*******************************************************************************
  * @file     HT8_ADC.h
  * @brief    The header file of the ADC library.
  * @author   Holtek Semiconductor Inc.
  * @version  V1.0.0
  * @date     2023-2-13
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
#ifndef _HT8_ADC_H_
#define _HT8_ADC_H_

/* Includes-------------------------------------------------------------------*/
#include "HT8_MCU_IP_SEL.h"

/* Exported constants---------------------------------------------------------*/
#define ADC_ENABLE()            (_adcen = 1)
#define ADC_DISABLE()           (_adcen = 0)

#define ADC_ISR_ENABLE()        (_ade = 1)
#define ADC_ISR_DISABLE()       (_ade = 0)
#define ADC_SET_ISR_FLAG()      (_adf = 1)
#define ADC_CLEAR_ISR_FLAG()    (_adf = 0)
#define ADC_GET_ISR_FLAG()      _adf

#define ADC_VBG_ENABLE()        (_vbgen = 1)
#define ADC_VBG_DISABLE()       (_vbgen = 0)

#define ADC_TS_ENABLE()         (_tsen = 1)
#define ADC_TS_DISABLE()        (_tsen = 0)

#define ADC_START()             {_start = 0; _start = 1; _start = 0;}

/*===================== Select ADC Temperature Sensor ========================*/
//  #define ADC_TS_ON               (1)
    #define ADC_TS_OFF              (1)
/*================ The end of Select ADC Temperature Sensor ==================*/

/*============================= Select ADC VBG ===============================*/
//  #define ADC_VBG_ON              (1)
    #define ADC_VBG_OFF             (1)
/*======================= The end of Select ADC VBG ==========================*/

/*========================= Select ADC Resolution ============================*/
    #define ADC_12BIT_MODE          (1)
//  #define ADC_10BIT_MODE          (1)
/*==================== The end of Select ADC Resolution ======================*/

/*========================= Select ADC Clock Rate ============================*/
//  #define ADC_CK_RATE_2M          (1)
//  #define ADC_CK_RATE_1M          (1)
//  #define ADC_CK_RATEs_500K       (1)
    #define ADC_CK_RATE_100_250K    (1)
/*==================== The end of Select ADC Clock Rate ======================*/

/*============================ Select ADC clock ==============================*/
//  #define ADC_CLOCK_FSYS          (1)
//  #define ADC_CLOCK_FSYS_DIV2     (1)
//  #define ADC_CLOCK_FSYS_DIV4     (1)
//  #define ADC_CLOCK_FSYS_DIV8     (1)
//  #define ADC_CLOCK_FSYS_DIV16    (1)
//  #define ADC_CLOCK_FSYS_DIV32    (1)
    #define ADC_CLOCK_FSYS_DIV64    (1)
//  #define ADC_CLOCK_FSYS_DIV128   (1)
/*======================= The end of Select ADC clock ========================*/

/*====================== Select ADC reference voltage ========================*/
//  #define ADC_REF_VOLTAGE_VREF    (1)
    #define ADC_REF_VOLTAGE_VDD     (1)
//  #define ADC_REF_VOLTAGE_VTSVREF (1)
/*================= The end of Select ADC reference voltage ==================*/

/*========================= Select ADC data format ===========================*/
    #define ADC_VALUE_ALIGN_LEFT    (1)
//  #define ADC_VALUE_ALIGN_RIGHT   (1)

    #ifdef  ADC_VALUE_ALIGN_LEFT
            #ifdef  ADC_12BIT_MODE
                    #define ADC_READ_VALUE()    (_sadoh << 4) | (_sadol >> 4)

            #elif   ADC_10BIT_MODE
                    #define ADC_READ_VALUE()    (_sadoh << 2) | (_sadol >> 6)
            #endif
    #else
            #define ADC_READ_VALUE()    (_sadoh << 8) | _sadol
    #endif
/*======================= The end of ADC data format =========================*/

/*******************************************************************************
  * @brief    Enumeration of ADC input.
 *******************************************************************************/
typedef enum 
{
    ADC_CH0 = (u8)0x00,             /*Analog channel 0*/
    ADC_CH1 = (u8)0x01,             /*Analog channel 1*/
    ADC_CH2 = (u8)0x02,             /*Analog channel 2*/
    ADC_CH3 = (u8)0x03,             /*Analog channel 3*/
    ADC_CH4 = (u8)0x04,             /*Analog channel 4*/
    ADC_CH5 = (u8)0x05,             /*Analog channel 5*/
    ADC_CH6 = (u8)0x06,             /*Analog channel 6*/
    ADC_CH7 = (u8)0x07,             /*Analog channel 7*/

    ADC_CH_INTERNAL_VBG = (u8)0x20,
    ADC_CH_INTERNAL_VTSO = (u8)0x40,
    ADC_CH_INTERNAL_VSS = (u8)0x60,
}ADC_Channel_TypeDef;


/* Exported functions---------------------------------------------------------*/
void ADC_Init(void);
void ADC_SelectChannel(u8 ADC_Channel);
u16 ADC_GetValue(void);
u16 ADC_GetChannelValue(u8 ADC_Channel);

#endif

/*********** (C) COPYRIGHT 2019 Holtek Semiconductor Inc **********END OF FILE*/
