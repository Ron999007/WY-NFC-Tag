/*******************************************************************************
  * @file     HT8_SYS_Clock.h
  * @brief    The header file of the System clock library.
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
#ifndef _HT8_SYS_Clock_H_
#define _HT8_SYS_Clock_H_

/* Includes-------------------------------------------------------------------*/
#include "HT8_MCU_IP_SEL.h"

/* Exported constants---------------------------------------------------------*/

/*======================= Select High frequency clock ========================*/
//  #define FH_HIRC_2M      (1)
//  #define FH_HIRC_4M      (1)
    #define FH_HIRC_8M      (1)
//  #define FH_MIRC_64K     (1)
//  #define FH_MIRC_128K    (1)
//  #define FH_MIRC_256K    (1)
//  #define FH_MIRC_512K    (1)

/* HXT frequency is smaller or equal than 10MHz */
//  #define FH_HXT_SE10M    (1)

/* HXT frequency is larger than 10MHz */
//  #define FH_HXT_L10M     (1)
/*================= The end of Select High frequency clock ===================*/

/*======================= Select Low frequency clock =========================*/
    #define FSUB_LIRC           (1)
//  #define FSUB_LXT_SU_DIS     (1)
//  #define FSUB_LXT_SU_EN      (1)
/*================= The end of Select Low frequency clock ====================*/

/*========================== Select system clock  ============================*/
    #define SYSCLOCK_FH         (1)
//  #define SYSCLOCK_FH_DIV2    (1)
//  #define SYSCLOCK_FH_DIV4    (1)
//  #define SYSCLOCK_FH_DIV8    (1)
//  #define SYSCLOCK_FH_DIV16   (1)
//  #define SYSCLOCK_FH_DIV32   (1)
//  #define SYSCLOCK_FH_DIV64   (1)
//  #define SYSCLOCK_FSUB       (1)
/*===================== The end of Select system clock  ======================*/

/*******************************************************************************
  * @brief    Enumeration of HALT mode.
 *******************************************************************************/
typedef enum 
{
    HALT_SLEEP  = (u8)0x00,     /*Sleep mode*/
    HALT_IDLE0  = (u8)0x01,     /*IDLE0 mode*/
    HALT_IDLE1  = (u8)0x03,     /*IDLE1 mode*/
    HALT_IDLE2  = (u8)0x02,     /*IDLE2 mode*/
}HALT_Mode_TypeDef;


/* Exported functions---------------------------------------------------------*/
void SysClock_Init(void);
void EnterHaltMode(u8 Halt_Mode);

#endif

/*********** (C) COPYRIGHT 2019 Holtek Semiconductor Inc **********END OF FILE*/
