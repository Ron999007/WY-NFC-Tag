/*******************************************************************************
  * @file     HT8_STM.c
  * @brief    This file provides all the STM firmware functions.
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
#include "HT8_STM.h"

/*******************************************************************************
  * @brief    STM initialization function.
  * @param    None
  * @retval   None
 *******************************************************************************/
void STM_Init(void)
{
/*======================= Select STM operating mode ==========================*/
    #ifdef  STM_TIMER_COUNTER_MODE
            _stm1 = 1; _stm0 = 1;       /*Select STM timer/counter Mode*/

    #elif   STM_PWM_OUTPUT_MODE
            _stm1 = 1; _stm0 = 0;
            _stio1 = 1; _stio0 = 0;     /*Select STM PWM Output Mode*/

    #elif   STM_SINGLE_PULSE_OUTPUT_MODE
            _stm1 = 1; _stm0 = 0;
            _stio1 = 1; _stio0 = 1;     /*Select STM Single Pulse Output Mode*/

    #elif   STM_COMPARE_MATCH_MODE
            _stm1 = 0; _stm0 = 0;       /*Select STM Compare Match Output Mode*/

    #elif   STM_CAPTURE_INPUT_MODE
            _stm1 = 0; _stm0 = 1;       /*Select STM Capture Input Mode*/

    #endif
/*================== The end of Select STM operating mode ====================*/

/*======================== Select STM counter clock ==========================*/
    /* Select STM Counter clock Fsys/4 */
    #ifdef  STM_FSYS_DIV4
            _stck2 = 0; _stck1 = 0; _stck0 = 0;

    /* Select STM Counter clock Fsys */
    #elif   STM_FSYS
            _stck2 = 0; _stck1 = 0; _stck0 = 1;

    /* Select STM Counter clock FH/16 */
    #elif   STM_FH_DIV16
            _stck2 = 0; _stck1 = 1; _stck0 = 0;

    /* Select STM Counter clock FH/64 */
    #elif   STM_FH_DIV64
            _stck2 = 0; _stck1 = 1; _stck0 = 1;

    /* Select STM Counter clock Fsub */
    #elif   STM_FSUB
            _stck2 = 1; _stck1 = 0; _stck0 = 0;

    /* Select STM Counter clock TCKn rising edge clock */
    #elif   STM_TCK_RISING_EDGE
            _stck2 = 1; _stck1 = 1; _stck0 = 0;

    /* Select STM Counter clock TCKn falling edge clock */
    #elif   STM_TCK_FALLING_EDGE
            _stck2 = 1; _stck1 = 1; _stck0 = 1;

    #endif
/*=================== The end of Select STM counter clock ====================*/

/*=================== Select STM counter clear condition =====================*/
    /* STM Counter Clear condition selection STM Comparator A match */
    #ifdef  STM_CCRA_MATCH
            _stcclr = 1;

    /* STM Counter Clear condition selection STM Comparator P match */
    #elif   STM_CCRP_MATCH
            _stcclr = 0;

    #endif
/*============= The end of Select STM counter clear condition ================*/

}


/*******************************************************************************
  * @brief    STM PWM configure function.
  *           Specify the following parameters in HT8_STM.h:
  *              1. STP output control
  *              2. STP output polarity control
  *              3. STM PWM period/duty control
  * @param    None
  * @retval   None
 *******************************************************************************/
void STM_PwmOutputConfig(void)
{
/*=========================== STP output control =============================*/
    #ifdef  STM_ACTIVE_LOW
            _stoc = 0;                  /*Active low*/

    #elif   STM_ACTIVE_HIGH
            _stoc = 1;                  /*Active high*/

    #endif
/*===================== The end of STP output control ========================*/

/*======================= STP output polarity control ========================*/
    #ifdef  STM_NON_INVERTED
            _stpol = 0;                 /*No inverted*/

    #elif   STM_INVERTED
            _stpol = 1;                 /*Inverted*/

    #endif
/*================= The end of STP output polarity control ===================*/

/*======================= STM PWM period/duty control ========================*/
    #ifdef  STM_CCRP_P_CCRA_D
            _stdpx = 0;                 /*CCRP - period; CCRA - duty*/

    #elif   STM_CCRP_D_CCRA_P
            _stdpx = 1;                 /*CCRP - duty; CCRA - period*/

    #endif
/*================= The end of STM PWM period/duty control ===================*/
}


/*******************************************************************************
  * @brief    STM PWM update function.
  * @param    TempCCRA: CCRA value
  *           the TempCCRA value range is 1 ~ 65535.
  * @param    TempCCRP: CCRP value
  *           the TempCCRP value range is 0 ~ 255:
  *              [1].when TempCCRP = 0, the PWM Duty = TempCCRA/65536,
  *                  frequency = 1/(65536*Tclock);
  *              [2].when TempCCRP > 0, the PWM Duty = TempCCRA/(256*TempCCRP),
  *                  frequency = 1/(256*TempCCRP*Tclock);
  * @retval   None
 *******************************************************************************/
void STM_PwmUpdate(u16 TempCCRA,u8 TempCCRP)
{
    _stmal = TempCCRA & 0x00ff;
    _stmah = TempCCRA >> 8;
    _stmrp = TempCCRP;
}


/*******************************************************************************
  * @brief    STM SinglePulse configure function.
  *           Specify the following parameters in HT8_STM.h:
  *              1. STP output control
  *              2. STP output polarity control
  *              3. PTCK trigger control
  * @param    None
  * @retval   None
 *******************************************************************************/
void STM_SinglePulseOutputConfig(void)
{
/*=========================== STP output control =============================*/
    #ifdef  STM_ACTIVE_LOW
            _stoc = 0;                  /*Active low*/

    #elif   STM_ACTIVE_HIGH
            _stoc = 1;                  /*Active high*/

    #endif
/*===================== The end of STP output control ========================*/

/*======================= STP output polarity control ========================*/
    #ifdef  STM_NON_INVERTED
            _stpol = 0;                 /*No inverted*/

    #elif   STM_INVERTED
            _stpol = 1;                 /*Inverted*/

    #endif
/*================= The end of STP output polarity control ===================*/
}


/*******************************************************************************
  * @brief    STM SinglePulse update function.
  * @param    TempCCRA: CCRA value
  *           the TempCCRA value range is 1 ~ 65535, 
  *           the pulse width = TempCCRA * Tclock.
  * @retval   None
 *******************************************************************************/
void STM_SinglePulseUpdate(u16 TempCCRA)
{
    _stmal = TempCCRA & 0x00ff;
    _stmah = TempCCRA >> 8;
}


/*******************************************************************************
  * @brief    STM timer/counter mode period config function.
  * @param    TempPeriod: Period value
  *           1. if select CCRA_MATCH, the TempPeriod value range is 1 ~ 65535,
  *              the overflow time = TempPeriod * Tclock.
  *           2. if select CCRP_MATCH, the TempPeriod value range is 0 ~ 255: 
  *              [1].when TempPeriod = 0, the overflow time = 65536 * Tclock
  *              [2].when TempPeriod > 0,
  *                  the overflow time = 256 * TempPeriod * Tclock
  * @retval   None
 *******************************************************************************/
void STM_CounterModeConfig(u16 TempPeriod)
{
    #ifdef  STM_CCRA_MATCH
            _stmal = TempPeriod & 0x00ff;
            _stmah = TempPeriod >> 8;

    #elif   STM_CCRP_MATCH
            _stmrp = TempPeriod & 0x00ff;

    #endif
}


/*******************************************************************************
  * @brief    STM compare match output config function.
  *           Specify the following parameters in HT8_STM.h:
  *              1. Select STM function in Compare match output mode
  *              2. STP output control
  *              3. STP output polarity control
  * @param    None
  * @retval   None
 *******************************************************************************/
void STM_CompareMatchOutputConfig(void)
{
/*============ Select STM function in Compare match output mode ==============*/
    #ifdef  STM_NO_CHANGE
            _stio1 = 0; _stio0 = 0;

    #elif   STM_OUTPUT_LOW
            _stio1 = 0; _stio0 = 1;

    #elif   STM_OUTPUT_HIGH
            _stio1 = 1; _stio0 = 0;

    #elif   STM_OUTPUT_TOGGLE
            _stio1 = 1; _stio0 = 1;

    #endif
/*======= The end of Select STM function in Compare match output mode ========*/

/*=========================== STP output control =============================*/
    #ifdef  STM_INITIAL_LOW
            _stoc = 0;

    #elif   STM_INITIAL_HIGH
            _stoc = 1;

    #endif
/*===================== The end of STP output control ========================*/

/*======================= STP output polarity control ========================*/
    #ifdef  STM_NON_INVERTED
            _stpol = 0;

    #elif   STM_INVERTED
            _stpol = 1;

    #endif
/*================= The end of STP output polarity control ===================*/
}


/*******************************************************************************
  * @brief    STM compare match output update function.
  * @param    TempMatchTime: MatchTime value
  *           1. if select CCRA_MATCH, the TempMatchTime value range is 1~65535,
  *              the match time = TempMatchTime * Tclock.
  *           2. if select CCRP_MATCH, the TempMatchTime value range is 0 ~ 255:
  *              [1]. when TempMatchTime = 0, the match time = 65536 * Tclock
  *              [2]. when TempMatchTime > 0,
  *                   the match time = 256 * TempMatchTime * Tclock
  * @retval   None
 *******************************************************************************/
void STM_CompareMatchOutputUpdate(u16 TempMatchTime)
{
    #ifdef  STM_CCRA_MATCH
            _stmal = TempMatchTime & 0x00ff;
            _stmah = TempMatchTime >> 8;

    #elif   STM_CCRP_MATCH
            _stmal = 1;
            _stmah = 0;
            _stmrp = TempMatchTime & 0x00ff;

    #endif
}


/*********** (C) COPYRIGHT 2019 Holtek Semiconductor Inc **********END OF FILE*/
