/*******************************************************************************
  * @file     HT8_ADC.c
  * @brief    This file provides all the ADC firmware functions.
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

/* Includes-------------------------------------------------------------------*/
#include "HT8_ADC.h"

/*******************************************************************************
  * @brief    ADC initialization function.
  * @param    None
  * @retval   None
 *******************************************************************************/
void ADC_Init(void)
{
/*===================== Select ADC Temperature Sensor ========================*/
    #ifdef  ADC_TS_ON
            ADC_TS_ENABLE();

    #elif   ADC_TS_OFF
            ADC_TS_DISABLE();

    #endif

/*================ The end of Select ADC Temperature Sensor ==================*/

/*============================= Select ADC VBG ===============================*/
    #ifdef  ADC_VBG_ON
            ADC_VBG_ENABLE();

    #elif   ADC_VBG_OFF
            ADC_VBG_DISABLE();

    #endif

/*======================= The end of Select ADC VBG ==========================*/

/*========================= Select ADC Resolution ============================*/
    #ifdef  ADC_12BIT_MODE
            _sabms = 0;                 /*Select 12-bit resolution mode*/

    #elif   ADC_10BIT_MODE
            _sabms = 1;                 /*Select 10-bit resolution mode*/

    #endif
/*==================== The end of Select ADC Resolution ======================*/

/*========================= Select ADC Clock Rate ============================*/
    #ifdef  ADC_CK_RATE_2M
            _sacms1 = 0; _sacms0 = 0;   /*Select ADC clock rate up to 2MHz*/

    #elif   ADC_CK_RATE_1M
            _sacms1 = 0; _sacms0 = 1;   /*Select ADC clock rate up to 1MHz*/

    #elif   ADC_CK_RATEs_500K
            _sacms1 = 1; _sacms0 = 0;   /*Select ADC clock rate up to 500kHz*/

    #elif   ADC_CK_RATE_100_250K
            _sacms1 = 1; _sacms0 = 1;   /*Select ADC clock rate limit 100kHz~250kHz*/

    #endif
/*==================== The end of Select ADC Clock Rate ======================*/

/*============================ Select ADC clock ==============================*/
    #ifdef  ADC_CLOCK_FSYS
            _sacks2 = 0; _sacks1 = 0; _sacks0 = 0;  /*Select ADC clock fsys*/

    #elif   ADC_CLOCK_FSYS_DIV2
            _sacks2 = 0; _sacks1 = 0; _sacks0 = 1;  /*Select ADC clock fsys/2*/

    #elif   ADC_CLOCK_FSYS_DIV4
            _sacks2 = 0; _sacks1 = 1; _sacks0 = 0;  /*Select ADC clock fsys/4*/

    #elif   ADC_CLOCK_FSYS_DIV8
            _sacks2 = 0; _sacks1 = 1; _sacks0 = 1;  /*Select ADC clock fsys/8*/

    #elif   ADC_CLOCK_FSYS_DIV16
            _sacks2 = 1; _sacks1 = 0; _sacks0 = 0;  /*Select ADC clock fsys/16*/

    #elif   ADC_CLOCK_FSYS_DIV32
            _sacks2 = 1; _sacks1 = 0; _sacks0 = 1;  /*Select ADC clock fsys/32*/

    #elif   ADC_CLOCK_FSYS_DIV64
            _sacks2 = 1; _sacks1 = 1; _sacks0 = 0;  /*Select ADC clock fsys/64*/

    #elif   ADC_CLOCK_FSYS_DIV128
            _sacks2 = 1; _sacks1 = 1; _sacks0 = 1;  /*Select ADC clock fsys/128*/

    #endif

/*======================= The end of Select ADC clock ========================*/

/*========================= Select ADC data format ===========================*/
    #ifdef  ADC_VALUE_ALIGN_RIGHT
            _adrfs = 1;                 /*12-bit: SADOH=D[11:8]; SADOL=D[7:0]*/
                                        /*10-bit: SADOH=D[9:8]; SADOL=D[7:0]*/

    #elif   ADC_VALUE_ALIGN_LEFT
            _adrfs = 0;                 /*12-bit: SADOH=D[11:4]; SADOL=D[3:0]*/
                                        /*10-bit: SADOH=D[9:2]; SADOL=D[1:0]*/

    #endif

/*======================= The end of ADC data format =========================*/

/*====================== Select ADC reference voltage ========================*/
    #ifdef  ADC_REF_VOLTAGE_VREF
            _savrs1 = 0; _savrs0 = 0;

    #elif   ADC_REF_VOLTAGE_VDD
            _savrs1 = 0; _savrs0 = 1;

    #elif   ADC_REF_VOLTAGE_VTSVREF
            _savrs1 = 1; _savrs0 = 0;

    #endif

/*================= The end of Select ADC reference voltage ==================*/

}


/*******************************************************************************
  * @brief    ADC channel setting function.
  * @param    ADC_Channel: Specifies the ADC channel
  *           the ADC_Channel can have one of the values of @ref ADC_Channel_TypeDef
  * @retval   None
 *******************************************************************************/
void ADC_SelectChannel(u8 ADC_Channel)
{
    _sadc1 &= 0b00011111;                   /*Set ADC input only comes from SAPIN*/

    if((ADC_Channel >= 0)&&(ADC_Channel < 8))
    {
        _sadc0 &= 0b11110000;

        _sadc0 |= ADC_Channel;              /*Select SAPIN input channel */
    }

    else
    {
        _sadc0 |= 0b00001111;               /*Select SAPIN input floating*/

        _sadc1 |= ADC_Channel;              /*Select internal ADC channel*/
    }
}


/*******************************************************************************
  * @brief    Get one sample of measured signal.
  * @param    None
  * @retval   Value: The value of the measured signal.
 *******************************************************************************/
u16 ADC_GetValue(void)
{
    u16 Value;

    ADC_START();                            /*Start AD converter*/

    while(1 == _adbz);                      /*Waitting AD conversion finish*/

    #ifdef  ADC_VALUE_ALIGN_RIGHT           /*AD conversion data alignment right*/
    {
            /* get the AD conversion value */
            Value = (_sadoh << 8) | _sadol;
    }

    #elif   ADC_VALUE_ALIGN_LEFT            /*AD conversion data alignment left*/
    {
            /* get the AD conversion value */
            #ifdef  ADC_12BIT_MODE
            {
                Value = (_sadoh << 4) | (_sadol >> 4);
            }

            #elif   ADC_10BIT_MODE
            {
                Value = (_sadoh << 2) | (_sadol >> 6);
            }
            #endif

    }
    #endif

    return Value;
}


/*******************************************************************************
  * @brief    Get one sample of measured signal form the designated ADC channel.
  * @param    ADC_Channel: Specifies the ADC channel.
  *           the ADC_Channel can have one of the values of @ref ADC_Channel_TypeDef.
  * @retval   AD_ConverterValue: The value of the measured signal.
 *******************************************************************************/
u16 ADC_GetChannelValue(u8 ADC_Channel)
{
    u16 AD_ConverterValue;

    _sadc1 &= 0b00011111;                   /*Set ADC input only comes from SAPIN*/

    if((ADC_Channel >= 0) && (ADC_Channel < 8))
    {
        _sadc0 &= 0b11110000;

        _sadc0 |= ADC_Channel;              /*Select SAPIN input channel */
    }

    else
    {
        _sadc0 |= 0b00001111;               /*Select SAPIN input floating*/

        _sadc1 |= ADC_Channel;              /*Select internal ADC channel*/
    }

    ADC_START();                            /*Start AD converter*/

    while(1 == _adbz);                      /*Waitting AD conversion finish*/

    #ifdef  ADC_VALUE_ALIGN_RIGHT           /*AD conversion data alignment right*/
    {
            /* get the AD conversion value */
            AD_ConverterValue = (_sadoh << 8) | _sadol;
    }

    #elif   ADC_VALUE_ALIGN_LEFT            /*AD conversion data alignment left*/
    {
            /* get the AD conversion value */
            #ifdef  ADC_12BIT_MODE
            {
                AD_ConverterValue = (_sadoh << 4) | (_sadol >> 4);
            }

            #elif   ADC_10BIT_MODE
            {
                AD_ConverterValue = (_sadoh << 2) | (_sadol >> 6);
            }
            #endif

    }
    #endif

    return AD_ConverterValue;
}


/*********** (C) COPYRIGHT 2019 Holtek Semiconductor Inc **********END OF FILE*/
