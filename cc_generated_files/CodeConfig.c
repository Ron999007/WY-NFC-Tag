/*******************************************************************************
  * @file     CodeConfig.c
  * @brief    CodeConfig setting file.
  * @author   Holtek Semiconductor Inc.
  * @version  V1.0.0
  * @date     2026-08-31
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

#include "CodeConfig.h"

void System_Init()
{
    /*Begin System_Init()*/


	SysClock_Init();
	GPIO_Init();
	TimeBase1_Init();
	USIM_SIM_Init();
    /*End System_Init()*/
}


void System_Setting()
{
    /*Begin System_Setting()*/
	EMI_ENABLE();



	READ_PORT_FUNC_DISABLE();
	TB1_CLEAR_ISR_FLAG();
	TB1_ISR_ENABLE();
	TB1_ENABLE();
	PSC1_ENABLE();
	USIM_SIM_ENABLE();
    /*End System_Setting()*/
}


/*********** (C) COPYRIGHT 2019 Holtek Semiconductor Inc **********END OF FILE*/
