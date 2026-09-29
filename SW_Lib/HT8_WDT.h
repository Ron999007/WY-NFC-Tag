/*******************************************************************************
  * @file     HT8_WDT.h
  * @brief    The header file of the WDT library.
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

/* Define to prevent recursive inclusion--------------------------------------*/
#ifndef _HT8_WDT_H_
#define _HT8_WDT_H_

/* Includes-------------------------------------------------------------------*/
#include "HT8_MCU_IP_SEL.h"

/* Exported constants---------------------------------------------------------*/

#define WDT_ENABLE()        {_wdtc = (_wdtc & 0b00000111) | 0b01010000;}
#define WDT_DISABLE()       {_wdtc = (_wdtc & 0b00000111) | 0b10101000;}

/*======================== WDT overflow time select ==========================*/
//  #define WDT_OF_TIME_2_8     (1)     /*WDT overflow time 2^8/fWDT*/
//  #define WDT_OF_TIME_2_10    (1)     /*WDT overflow time 2^10/fWDT*/
//  #define WDT_OF_TIME_2_12    (1)     /*WDT overflow time 2^12/fWDT*/
//  #define WDT_OF_TIME_2_14    (1)     /*WDT overflow time 2^14/fWDT*/
//  #define WDT_OF_TIME_2_15    (1)     /*WDT overflow time 2^15/fWDT*/
//  #define WDT_OF_TIME_2_16    (1)     /*WDT overflow time 2^16/fWDT*/
//  #define WDT_OF_TIME_2_17    (1)     /*WDT overflow time 2^17/fWDT*/
//  #define WDT_OF_TIME_2_18    (1)     /*WDT overflow time 2^18/fWDT*/
/*=================== The end of WDT overflow time select ====================*/

/* Exported functions---------------------------------------------------------*/
void WDT_Init(void);

#endif

/*********** (C) COPYRIGHT 2019 Holtek Semiconductor Inc **********END OF FILE*/
