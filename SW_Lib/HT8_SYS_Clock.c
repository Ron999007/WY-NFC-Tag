/*******************************************************************************
  * @file     HT8_SYS_Clock.c
  * @brief    This file provides all the System clock firmware functions.
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
#include "HT8_SYS_Clock.h"

/*******************************************************************************
  * @brief    System clock initialization function.
  * @param    None
  * @retval   None
 *******************************************************************************/
void SysClock_Init(void)
{
/*======================= Select High frequency clock ========================*/
    #ifdef  FH_HIRC_2M
            _ircen = 1; _irc2 = 0; _irc1 = 0; _irc0 = 0; while(!_ircf); _fhs = 0;

    #elif   FH_HIRC_4M
            _ircen = 1; _irc2 = 0; _irc1 = 0; _irc0 = 1; while(!_ircf); _fhs = 0;

    #elif   FH_HIRC_8M
            _ircen = 1; _irc2 = 0; _irc1 = 1; _irc0 = 0; while(!_ircf); _fhs = 0;

    #elif   FH_MIRC_64K
            _ircen = 1; _irc2 = 1; _irc1 = 0; _irc0 = 0; while(!_ircf); _fhs = 0;

    #elif   FH_MIRC_128K
            _ircen = 1; _irc2 = 1; _irc1 = 0; _irc0 = 1; while(!_ircf); _fhs = 0;

    #elif   FH_MIRC_256K
            _ircen = 1; _irc2 = 1; _irc1 = 1; _irc0 = 0; while(!_ircf); _fhs = 0;

    #elif   FH_MIRC_512K
            _ircen = 1; _irc2 = 1; _irc1 = 1; _irc0 = 1; while(!_ircf); _fhs = 0;

    #elif   FH_HXT_SE10M
            _pas15 = 1; _pas14 = 1; _pas17 = 1; _pas16 = 1;
            _hxtm = 0; _hxten = 1; while(!_hxtf); _fhs = 1;

    #elif   FH_HXT_L10M
            _pas15 = 1; _pas14 = 1; _pas17 = 1; _pas16 = 1;
            _hxtm = 1; _hxten = 1; while(!_hxtf); _fhs = 1;

    #endif

/*================= The end of Select High frequency clock ===================*/

/*======================= Select Low frequency clock =========================*/
    #ifdef  FSUB_LIRC
            _fss = 0;

    #elif   FSUB_LXT_SU_DIS
            _pcs13 = 1; _pcs12 = 1; _pcs11 = 1; _pcs10 = 1;
            _lxtsp = 0; _lxten = 1; while(!_lxtf); _fss = 1;

    #elif   FSUB_LXT_SU_EN
            _pcs13 = 1; _pcs12 = 1; _pcs11 = 1; _pcs10 = 1;
            _lxtsp = 1; _lxten = 1; while(!_lxtf); _fss = 1;

    #endif

/*================= The end of Select Low frequency clock ====================*/

/*========================== Select system clock  ============================*/
    #ifdef  SYSCLOCK_FH
            _cks2 = 0; _cks1 = 0; _cks0 = 0;    /*Set FH as Fsys*/

    #elif   SYSCLOCK_FH_DIV2
            _cks2 = 0; _cks1 = 0; _cks0 = 1;    /*Set FH/2 as Fsys*/

    #elif   SYSCLOCK_FH_DIV4
            _cks2 = 0; _cks1 = 1; _cks0 = 0;    /*Set FH/4 as Fsys*/

    #elif   SYSCLOCK_FH_DIV8
            _cks2 = 0; _cks1 = 1; _cks0 = 1;    /*Set FH/8 as Fsys*/

    #elif   SYSCLOCK_FH_DIV16
            _cks2 = 1; _cks1 = 0; _cks0 = 0;    /*Set FH/16 as Fsys*/

    #elif   SYSCLOCK_FH_DIV32
            _cks2 = 1; _cks1 = 0; _cks0 = 1;    /*Set FH/32 as Fsys*/

    #elif   SYSCLOCK_FH_DIV64
            _cks2 = 1; _cks1 = 1; _cks0 = 0;    /*Set FH/64 as Fsys*/

    #elif   SYSCLOCK_FSUB
            _cks2 = 1; _cks1 = 1; _cks0 = 1;    /*Set FSUB(32.768K or 32K) as Fsys*/

    #endif

    GCC_DELAY(100);                             /*Clock switching delay time*/

/*===================== The end of Select system clock  ======================*/

}


/*******************************************************************************
  * @brief    Halt mode setting function.
  * @param    HALT_Mode: Specifies the HALT Mode.
  *           the HALT_Mode can have one of the values of HALT_Mode_TypeDef.
  * @retval   None
 *******************************************************************************/
void EnterHaltMode(u8 Halt_Mode)
{
    _scc &= 0xfc;
    _scc |= Halt_Mode;
    _halt();
}


/*********** (C) COPYRIGHT 2019 Holtek Semiconductor Inc **********END OF FILE*/
