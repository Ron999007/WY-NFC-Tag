/*******************************************************************************
  * @file     HT8_TimeBase.c
  * @brief    This file provides all the TimeBase firmware functions.
  * @author   Holtek Semiconductor Inc.
  * @version  V1.0.0
  * @date     2022-11-22
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
#include "HT8_TimeBase.h"

/*******************************************************************************
  * @brief    TimeBase0 initialization function.
  * @param    None
  * @retval   None
 *******************************************************************************/
void TimeBase0_Init(void)
{
/*========================= Select TimeBase0 clock ===========================*/
    #ifdef  TB0_CLOCK_FSYS
            _clksel01 = 0; _clksel00 = 0;

    #elif   TB0_CLOCK_FSYS_DIV4
            _clksel01 = 0; _clksel00 = 1;

    #elif   TB0_CLOCK_FSUB 
            _clksel01 = 1; _clksel00 = 0;

    #elif   TB0_CLOCK_f4KHZ
            _clksel01 = 1; _clksel00 = 1;

    #endif
/*=================== The end of Select TimeBase0 clock ======================*/

/*==================== Select TimeBasen time-out period ======================*/
    #ifdef  TB0_Period_2_8
            _tb02 = 0; _tb01 = 0; _tb00 = 0;

    #elif   TB0_Period_2_9
            _tb02 = 0; _tb01 = 0; _tb00 = 1;

    #elif   TB0_Period_2_10
            _tb02 = 0; _tb01 = 1; _tb00 = 0;

    #elif   TB0_Period_2_11
            _tb02 = 0; _tb01 = 1; _tb00 = 1;

    #elif   TB0_Period_2_12
            _tb02 = 1; _tb01 = 0; _tb00 = 0;

    #elif   TB0_Period_2_13
            _tb02 = 1; _tb01 = 0; _tb00 = 1;

    #elif   TB0_Period_2_14
            _tb02 = 1; _tb01 = 1; _tb00 = 0;

    #elif   TB0_Period_2_15
            _tb02 = 1; _tb01 = 1; _tb00 = 1;

    #endif
/*=============== The end of Select TimeBase0 time-out period ================*/
}

/*******************************************************************************
  * @brief    TimeBase1 initialization function.
  * @param    None
  * @retval   None
 *******************************************************************************/
void TimeBase1_Init(void)
{
/*========================= Select TimeBase1 clock ===========================*/
    #ifdef  TB1_CLOCK_FSYS
            _clksel11 = 0; _clksel10 = 0;

    #elif   TB1_CLOCK_FSYS_DIV4
            _clksel11 = 0; _clksel10 = 1;

    #elif   TB1_CLOCK_FSUB 
            _clksel11 = 1; _clksel10 = 0;

    #elif   TB1_CLOCK_f4KHZ
            _clksel11 = 1; _clksel10 = 1;

    #endif
/*=================== The end of Select TimeBase1 clock ======================*/

/*==================== Select TimeBasen time-out period ======================*/
    #ifdef  TB1_Period_2_8
            _tb12 = 0; _tb11 = 0; _tb10 = 0;

    #elif   TB1_Period_2_9
            _tb12 = 0; _tb11 = 0; _tb10 = 1;

    #elif   TB1_Period_2_10
            _tb12 = 0; _tb11 = 1; _tb10 = 0;

    #elif   TB1_Period_2_11
            _tb12 = 0; _tb11 = 1; _tb10 = 1;

    #elif   TB1_Period_2_12
            _tb12 = 1; _tb11 = 0; _tb10 = 0;

    #elif   TB1_Period_2_13
            _tb12 = 1; _tb11 = 0; _tb10 = 1;

    #elif   TB1_Period_2_14
            _tb12 = 1; _tb11 = 1; _tb10 = 0;

    #elif   TB1_Period_2_15
            _tb12 = 1; _tb11 = 1; _tb10 = 1;

    #endif
/*=============== The end of Select TimeBase1 time-out period ================*/
}


/*********** (C) COPYRIGHT 2019 Holtek Semiconductor Inc **********END OF FILE*/
