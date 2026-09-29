/*******************************************************************************
  * @file     HT8_PTM.c
  * @brief    This file provides all the PTM firmware functions.
  * @author   Holtek Semiconductor Inc.
  * @version  V1.0.0
  * @date     2024-3-18
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
#include "HT8_PTM.h"

/*******************************************************************************
  * @brief    PTM0 initialization function.
  * @param    None
  * @retval   None
 *******************************************************************************/
void PTM0_Init(void)
{
/*======================= Select PTM0 operating mode =========================*/
    #ifdef  PTM0_TIMER_COUNTER_MODE
            _pt0m1 = 1; _pt0m0 = 1;     /*Select PTM0 timer/counter Mode*/

    #elif   PTM0_PWM_OUTPUT_MODE
            _pt0m1 = 1; _pt0m0 = 0;
            _pt0io1 = 1; _pt0io0 = 0;   /*Select PTM0 PWM Output Mode*/

    #elif   PTM0_SINGLE_PULSE_OUTPUT_MODE
            _pt0m1 = 1; _pt0m0 = 0;
            _pt0io1 = 1; _pt0io0 = 1;   /*Select PTM0 Single Pulse Output Mode*/

    #elif   PTM0_COMPARE_MATCH_MODE
            _pt0m1 = 0; _pt0m0 = 0;     /*Select PTM0 Compare Match Output Mode*/

    #elif   PTM0_CAPTURE_INPUT_MODE
            _pt0m1 = 0; _pt0m0 = 1;     /*Select PTM0 Capture Input Mode*/

    #endif
/*================= The end of Select PTM0 operating mode ====================*/

/*======================= Select PTM0 counter clock ==========================*/
    /* Select PTM0 Counter clock Fsys/4 */
    #ifdef  PTM0_FSYS_DIV4
            _pt0ck2 = 0; _pt0ck1 = 0; _pt0ck0 = 0;

    /* Select PTM0 Counter clock Fsys */
    #elif   PTM0_FSYS
            _pt0ck2 = 0; _pt0ck1 = 0; _pt0ck0 = 1;

    /* Select PTM0 Counter clock FH/16 */
    #elif   PTM0_FH_DIV16
            _pt0ck2 = 0; _pt0ck1 = 1; _pt0ck0 = 0;

    /* Select PTM0 Counter clock FH/64 */
    #elif   PTM0_FH_DIV64
            _pt0ck2 = 0; _pt0ck1 = 1; _pt0ck0 = 1;

    /* Select PTM0 Counter clock Fsub */
    #elif   PTM0_FSUB
            _pt0ck2 = 1; _pt0ck1 = 0; _pt0ck0 = 0;

    /* Select PTM0 Counter clock TCKn rising edge clock */
    #elif   PTM0_TCK_RISING_EDGE
            _pt0ck2 = 1; _pt0ck1 = 1; _pt0ck0 = 0;

    /* Select PTM0 Counter clock TCKn falling edge clock */
    #elif   PTM0_TCK_FALLING_EDGE
            _pt0ck2 = 1; _pt0ck1 = 1; _pt0ck0 = 1;

    #endif
/*================== The end of Select PTM0 counter clock ====================*/

/*=================== Select PTM0 counter clear condition ====================*/
    /* PTM0 Counter Clear condition selection PTM0 Comparator A match */
    #ifdef  PTM0_CCRA_MATCH
            _pt0cclr = 1;

    /* PTM0 Counter Clear condition selection PTM0 Comparator P match */
    #elif   PTM0_CCRP_MATCH
            _pt0cclr = 0;

    #endif
/*============= The end of Select PTM0 counter clear condition ===============*/

}


/*******************************************************************************
  * @brief    PTM0 PWM configure function.
  *           Specify the following parameters in HT8_PTM.h:
  *              1. PTP0 output control
  *              2. PTP0 output polarity control
  * @param    None
  * @retval   None
 *******************************************************************************/
void PTM0_PwmOutputConfig(void)
{
/*=========================== PTP0 output control ============================*/
    #ifdef  PTM0_ACTIVE_LOW
            _pt0oc = 0;                 /*Active low*/

    #elif   PTM0_ACTIVE_HIGH
            _pt0oc = 1;                 /*Active high*/

    #endif
/*===================== The end of PTP0 output control =======================*/

/*====================== PTP0 output polarity control ========================*/
    #ifdef  PTM0_NON_INVERTED
            _pt0pol = 0;                /*No inverted*/

    #elif   PTM0_INVERTED
            _pt0pol = 1;                /*Inverted*/

    #endif
/*================= The end of PTP0 output polarity control ==================*/
}


/*******************************************************************************
  * @brief    PTM0 PWM update function.
  * @param    TempCCRA: CCRA value
  *           the TempCCRA value range is 1 ~ 65535.
  * @param    TempCCRP: CCRP value
  *           the TempCCRP value range is 0 ~ 65535:
  *              [1].when TempCCRP = 0, the PWM Duty = TempCCRA / 65536
  *              [2].when TempCCRP > 0, the PWM Duty = TempCCRA / TempCCRP
  * @retval   None
 *******************************************************************************/
void PTM0_PwmUpdate(u16 TempCCRA,u16 TempCCRP)
{
    _ptm0al = TempCCRA & 0x00ff;
    _ptm0ah = TempCCRA >> 8;
    _ptm0rpl = TempCCRP & 0x00ff;
    _ptm0rph = TempCCRP >> 8;
}


/*******************************************************************************
  * @brief    PTM0 SinglePulse configure function.
  *           Specify the following parameters in HT8_PTM.h:
  *              1. PTP0 output control
  *              2. PTP0 output polarity control
  *              3. PTCK0 trigger control
  * @param    None
  * @retval   None
 *******************************************************************************/
void PTM0_SinglePulseOutputConfig(void)
{
/*=========================== PTP0 output control ============================*/
    #ifdef  PTM0_ACTIVE_LOW
            _pt0oc = 0;                 /*Active low*/

    #elif   PTM0_ACTIVE_HIGH
            _pt0oc = 1;                 /*Active high*/

    #endif
/*===================== The end of PTP0 output control =======================*/

/*====================== PTP0 output polarity control ========================*/
    #ifdef  PTM0_NON_INVERTED
            _pt0pol = 0;                /*No inverted*/

    #elif   PTM0_INVERTED
            _pt0pol = 1;                /*Inverted*/

    #endif
/*================= The end of PTP0 output polarity control ==================*/
}


/*******************************************************************************
  * @brief    PTM0 SinglePulse update function.
  * @param    TempCCRA: CCRA value
  *           the TempCCRA value range is 1 ~ 65535,
  *           the pulse width = TempCCRA * Tclock.
  * @retval   None
 *******************************************************************************/
void PTM0_SinglePulseUpdate(u16 TempCCRA)
{
    _ptm0al = TempCCRA & 0x00ff;
    _ptm0ah = TempCCRA >> 8;
}


/*******************************************************************************
  * @brief    PTM0 timer/counter mode period config function.
  * @param    TempPeriod: Period value
  *           1. if select CCRA_MATCH, the TempPeriod value range is 1 ~ 65535,
  *              the overflow time = TempPeriod * Tclock.
  *           2. if select CCRP_MATCH, the TempPeriod value range is 0 ~ 65535:
  *              [1].when TempPeriod = 0, the overflow time = 65536 * Tclock
  *              [2].when TempPeriod > 0,
  *                  the overflow time = TempPeriod * Tclock
  * @retval   None
 *******************************************************************************/
void PTM0_CounterModeConfig(u16 TempPeriod)
{
    #ifdef  PTM0_CCRA_MATCH
            _ptm0al = TempPeriod & 0x00ff;
            _ptm0ah = TempPeriod >> 8;

    #elif   PTM0_CCRP_MATCH
            _ptm0rpl = TempPeriod & 0x00ff;
            _ptm0rph = TempPeriod >> 8;

    #endif
}


/*******************************************************************************
  * @brief    PTM0 compare match output config function.
  *           Specify the following parameters in HT8_PTM.h:
  *              1. Select PTM0 function in Compare match output mode
  *              2. PTP0 output control
  *              3. PTP0 output polarity control
  * @param    None
  * @retval   None
 *******************************************************************************/
void PTM0_CompareMatchOutputConfig(void)
{
/*=========== Select PTM0 function in Compare match output mode ==============*/
    #ifdef  PTM0_NO_CHANGE
            _pt0io1 = 0; _pt0io0 = 0;

    #elif   PTM0_OUTPUT_LOW
            _pt0io1 = 0; _pt0io0 = 1;

    #elif   PTM0_OUTPUT_HIGH
            _pt0io1 = 1; _pt0io0 = 0;

    #elif   PTM0_OUTPUT_TOGGLE
            _pt0io1 = 1; _pt0io0 = 1;

    #endif
/*====== The end of Select PTM0 function in Compare match output mode ========*/

/*=========================== PTP0 output control ============================*/
    #ifdef  PTM0_INITIAL_LOW
            _pt0oc = 0;

    #elif   PTM0_INITIAL_HIGH
            _pt0oc = 1;

    #endif
/*===================== The end of PTP0 output control =======================*/

/*====================== PTP0 output polarity control ========================*/
    #ifdef  PTM0_NON_INVERTED
            _pt0pol = 0;

    #elif   PTM0_INVERTED
            _pt0pol = 1;

    #endif
/*================= The end of PTP0 output polarity control ==================*/
}


/*******************************************************************************
  * @brief    PTM0 compare match output update function.
  * @param    TempMatchTime: MatchTime value
  *           1. if select CCRA_MATCH,the TempMatchTime value range is 1~65535,
  *              the match time = TempMatchTime * Tclock.
  *           2. if select CCRP_MATCH,the TempMatchTime value range is 0~65535: 
  *              [1]. when TempMatchTime = 0,
  *                   the match time = 65536 * Tclock
  *              [2]. when TempMatchTime > 0,
  *                   the match time = TempMatchTime * Tclock
  * @retval   None
 *******************************************************************************/
void PTM0_CompareMatchOutputUpdate(u16 TempMatchTime)
{
    #ifdef  PTM0_CCRA_MATCH
            _ptm0al = TempMatchTime & 0x00ff;
            _ptm0ah = TempMatchTime >> 8;

    #elif   PTM0_CCRP_MATCH
            _ptm0al = 1;
            _ptm0ah = 0;
            _ptm0rpl = TempMatchTime & 0x00ff;
            _ptm0rph = TempMatchTime >> 8;

    #endif
}

/*******************************************************************************
  * @brief    PTM0 Capture Input config function.
  *           Specify the following parameters in HT8_PTM.h:
  *              1. Select Trigger Pin
  * @param    None
  * @retval   None
 *******************************************************************************/
void PTM0_CaptureInputConfig(void)
{
/*==================== Select PTM0 Trigger Pin function ======================*/
    #ifdef  PTM0_CAPTURE_PTP0I
            _pt0capts = 0;

    #elif   PTM0_CAPTURE_PTCK0
            _pt0capts = 1;

    #endif
/*=============== The end of Select PTM0 Trigger Pin function ================*/
}


/*******************************************************************************
  * @brief    PTM1 initialization function.
  * @param    None
  * @retval   None
 *******************************************************************************/
void PTM1_Init(void)
{
/*======================= Select PTM1 operating mode =========================*/
    #ifdef  PTM1_TIMER_COUNTER_MODE
            _pt1m1 = 1; _pt1m0 = 1;     /*Select PTM1 timer/counter Mode*/

    #elif   PTM1_PWM_OUTPUT_MODE
            _pt1m1 = 1; _pt1m0 = 0;
            _pt1io1 = 1; _pt1io0 = 0;   /*Select PTM1 PWM Output Mode*/

    #elif   PTM1_SINGLE_PULSE_OUTPUT_MODE
            _pt1m1 = 1; _pt1m0 = 0;
            _pt1io1 = 1; _pt1io0 = 1;   /*Select PTM1 Single Pulse Output Mode*/

    #elif   PTM1_COMPARE_MATCH_MODE
            _pt1m1 = 0; _pt1m0 = 0;     /*Select PTM1 Compare Match Output Mode*/

    #elif   PTM1_CAPTURE_INPUT_MODE
            _pt1m1 = 0; _pt1m0 = 1;     /*Select PTM1 Capture Input Mode*/

    #endif
/*================= The end of Select PTM1 operating mode ====================*/

/*======================= Select PTM1 counter clock ==========================*/
    /* Select PTM1 Counter clock Fsys/4 */
    #ifdef  PTM1_FSYS_DIV4
            _pt1ck2 = 0; _pt1ck1 = 0; _pt1ck0 = 0;

    /* Select PTM1 Counter clock Fsys */
    #elif   PTM1_FSYS
            _pt1ck2 = 0; _pt1ck1 = 0; _pt1ck0 = 1;

    /* Select PTM1 Counter clock FH/16 */
    #elif   PTM1_FH_DIV16
            _pt1ck2 = 0; _pt1ck1 = 1; _pt1ck0 = 0;

    /* Select PTM1 Counter clock FH/64 */
    #elif   PTM1_FH_DIV64
            _pt1ck2 = 0; _pt1ck1 = 1; _pt1ck0 = 1;

    /* Select PTM1 Counter clock Fsub */
    #elif   PTM1_FSUB
            _pt1ck2 = 1; _pt1ck1 = 0; _pt1ck0 = 0;

    /* Select PTM1 Counter clock TCKn rising edge clock */
    #elif   PTM1_TCK_RISING_EDGE
            _pt1ck2 = 1; _pt1ck1 = 1; _pt1ck0 = 0;

    /* Select PTM1 Counter clock TCKn falling edge clock */
    #elif   PTM1_TCK_FALLING_EDGE
            _pt1ck2 = 1; _pt1ck1 = 1; _pt1ck0 = 1;

    #endif
/*================== The end of Select PTM1 counter clock ====================*/

/*=================== Select PTM1 counter clear condition ====================*/
    /* PTM1 Counter Clear condition selection PTM1 Comparator A match */
    #ifdef  PTM1_CCRA_MATCH
            _pt1cclr = 1;

    /* PTM1 Counter Clear condition selection PTM1 Comparator P match */
    #elif   PTM1_CCRP_MATCH
            _pt1cclr = 0;

    #endif
/*============= The end of Select PTM1 counter clear condition ===============*/

}


/*******************************************************************************
  * @brief    PTM1 PWM configure function.
  *           Specify the following parameters in HT8_PTM.h:
  *              1. PTP1 output control
  *              2. PTP1 output polarity control
  * @param    None
  * @retval   None
 *******************************************************************************/
void PTM1_PwmOutputConfig(void)
{
/*=========================== PTP1 output control ============================*/
    #ifdef  PTM1_ACTIVE_LOW
            _pt1oc = 0;                 /*Active low*/

    #elif   PTM1_ACTIVE_HIGH
            _pt1oc = 1;                 /*Active high*/

    #endif
/*===================== The end of PTP1 output control =======================*/

/*====================== PTP1 output polarity control ========================*/
    #ifdef  PTM1_NON_INVERTED
            _pt1pol = 0;                /*No inverted*/

    #elif   PTM1_INVERTED
            _pt1pol = 1;                /*Inverted*/

    #endif
/*================= The end of PTP1 output polarity control ==================*/
}


/*******************************************************************************
  * @brief    PTM1 PWM update function.
  * @param    TempCCRA: CCRA value
  *           the TempCCRA value range is 1 ~ 65535.
  * @param    TempCCRP: CCRP value
  *           the TempCCRP value range is 0 ~ 65535:
  *              [1].when TempCCRP = 0, the PWM Duty = TempCCRA / 65536
  *              [2].when TempCCRP > 0, the PWM Duty = TempCCRA / TempCCRP
  * @retval   None
 *******************************************************************************/
void PTM1_PwmUpdate(u16 TempCCRA,u16 TempCCRP)
{
    _ptm1al = TempCCRA & 0x00ff;
    _ptm1ah = TempCCRA >> 8;
    _ptm1rpl = TempCCRP & 0x00ff;
    _ptm1rph = TempCCRP >> 8;
}


/*******************************************************************************
  * @brief    PTM1 SinglePulse configure function.
  *           Specify the following parameters in HT8_PTM.h:
  *              1. PTP1 output control
  *              2. PTP1 output polarity control
  *              3. PTCK1 trigger control
  * @param    None
  * @retval   None
 *******************************************************************************/
void PTM1_SinglePulseOutputConfig(void)
{
/*=========================== PTP1 output control ============================*/
    #ifdef  PTM1_ACTIVE_LOW
            _pt1oc = 0;                 /*Active low*/

    #elif   PTM1_ACTIVE_HIGH
            _pt1oc = 1;                 /*Active high*/

    #endif
/*===================== The end of PTP1 output control =======================*/

/*====================== PTP1 output polarity control ========================*/
    #ifdef  PTM1_NON_INVERTED
            _pt1pol = 0;                /*No inverted*/

    #elif   PTM1_INVERTED
            _pt1pol = 1;                /*Inverted*/

    #endif
/*================= The end of PTP1 output polarity control ==================*/
}


/*******************************************************************************
  * @brief    PTM1 SinglePulse update function.
  * @param    TempCCRA: CCRA value
  *           the TempCCRA value range is 1 ~ 65535,
  *           the pulse width = TempCCRA * Tclock.
  * @retval   None
 *******************************************************************************/
void PTM1_SinglePulseUpdate(u16 TempCCRA)
{
    _ptm1al = TempCCRA & 0x00ff;
    _ptm1ah = TempCCRA >> 8;
}


/*******************************************************************************
  * @brief    PTM1 timer/counter mode period config function.
  * @param    TempPeriod: Period value
  *           1. if select CCRA_MATCH, the TempPeriod value range is 1 ~ 65535,
  *              the overflow time = TempPeriod * Tclock.
  *           2. if select CCRP_MATCH, the TempPeriod value range is 0 ~ 65535:
  *              [1].when TempPeriod = 0, the overflow time = 65536 * Tclock
  *              [2].when TempPeriod > 0,
  *                  the overflow time = TempPeriod * Tclock
  * @retval   None
 *******************************************************************************/
void PTM1_CounterModeConfig(u16 TempPeriod)
{
    #ifdef  PTM1_CCRA_MATCH
            _ptm1al = TempPeriod & 0x00ff;
            _ptm1ah = TempPeriod >> 8;

    #elif   PTM1_CCRP_MATCH
            _ptm1rpl = TempPeriod & 0x00ff;
            _ptm1rph = TempPeriod >> 8;

    #endif
}


/*******************************************************************************
  * @brief    PTM1 compare match output config function.
  *           Specify the following parameters in HT8_PTM.h:
  *              1. Select PTM1 function in Compare match output mode
  *              2. PTP1 output control
  *              3. PTP1 output polarity control
  * @param    None
  * @retval   None
 *******************************************************************************/
void PTM1_CompareMatchOutputConfig(void)
{
/*=========== Select PTM1 function in Compare match output mode ==============*/
    #ifdef  PTM1_NO_CHANGE
            _pt1io1 = 0; _pt1io0 = 0;

    #elif   PTM1_OUTPUT_LOW
            _pt1io1 = 0; _pt1io0 = 1;

    #elif   PTM1_OUTPUT_HIGH
            _pt1io1 = 1; _pt1io0 = 0;

    #elif   PTM1_OUTPUT_TOGGLE
            _pt1io1 = 1; _pt1io0 = 1;

    #endif
/*====== The end of Select PTM1 function in Compare match output mode ========*/

/*=========================== PTP1 output control ============================*/
    #ifdef  PTM1_INITIAL_LOW
            _pt1oc = 0;

    #elif   PTM1_INITIAL_HIGH
            _pt1oc = 1;

    #endif
/*===================== The end of PTP1 output control =======================*/

/*====================== PTP1 output polarity control ========================*/
    #ifdef  PTM1_NON_INVERTED
            _pt1pol = 0;

    #elif   PTM1_INVERTED
            _pt1pol = 1;

    #endif
/*================= The end of PTP1 output polarity control ==================*/
}


/*******************************************************************************
  * @brief    PTM1 compare match output update function.
  * @param    TempMatchTime: MatchTime value
  *           1. if select CCRA_MATCH,the TempMatchTime value range is 1~65535,
  *              the match time = TempMatchTime * Tclock.
  *           2. if select CCRP_MATCH,the TempMatchTime value range is 0~65535: 
  *              [1]. when TempMatchTime = 0,
  *                   the match time = 65536 * Tclock
  *              [2]. when TempMatchTime > 0,
  *                   the match time = TempMatchTime * Tclock
  * @retval   None
 *******************************************************************************/
void PTM1_CompareMatchOutputUpdate(u16 TempMatchTime)
{
    #ifdef  PTM1_CCRA_MATCH
            _ptm1al = TempMatchTime & 0x00ff;
            _ptm1ah = TempMatchTime >> 8;

    #elif   PTM1_CCRP_MATCH
            _ptm1al = 1;
            _ptm1ah = 0;
            _ptm1rpl = TempMatchTime & 0x00ff;
            _ptm1rph = TempMatchTime >> 8;

    #endif
}

/*******************************************************************************
  * @brief    PTM1 Capture Input config function.
  *           Specify the following parameters in HT8_PTM.h:
  *              1. Select Trigger Pin
  * @param    None
  * @retval   None
 *******************************************************************************/
void PTM1_CaptureInputConfig(void)
{
/*==================== Select PTM1 Trigger Pin function ======================*/
    #ifdef  PTM1_CAPTURE_PTP1I
            _pt1capts = 0;

    #elif   PTM1_CAPTURE_PTCK1
            _pt1capts = 1;

    #endif
/*=============== The end of Select PTM1 Trigger Pin function ================*/
}

/*********** (C) COPYRIGHT 2019 Holtek Semiconductor Inc **********END OF FILE*/
