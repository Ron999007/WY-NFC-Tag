/*******************************************************************************
  * @file     HT8_STM.h
  * @brief    The header file of the STM library.
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
#ifndef _HT8_STM_H_
#define _HT8_STM_H_

/* Includes-------------------------------------------------------------------*/
#include "HT8_MCU_IP_SEL.h"

/* Exported constants---------------------------------------------------------*/
#define STM_ENABLE()                (_ston = 1)
#define STM_DISABLE()               (_ston = 0)

#define STM_CCRA_ISR_ENABLE()       (_stmae = 1)
#define STM_CCRA_ISR_DISABLE()      (_stmae = 0)
#define STM_SET_CCRA_ISR_FLAG()     (_stmaf = 1)
#define STM_CLEAR_CCRA_ISR_FLAG()   (_stmaf = 0)

#define STM_CCRP_ISR_ENABLE()       (_stmpe = 1)
#define STM_CCRP_ISR_DISABLE()      (_stmpe = 0)
#define STM_SET_CCRP_ISR_FLAG()     (_stmpf = 1)
#define STM_CLEAR_CCRP_ISR_FLAG()   (_stmpf = 0)

#define STM_PAUSE()                 (_stpau = 1)
#define STM_RUN()                   (_stpau = 0)

#define STM_GET_CCRA_ISR_FLAG()     _stmaf
#define STM_GET_CCRP_ISR_FLAG()     _stmpf


/*=============== Select STMn function in Capture input mode =================*/
/* Input capture at rising edge */
#define STM_CAPTURE_RISING_EDGE()       {_stio1 = 0; _stio0 = 0;}

/* Input capture at falling edge */
#define STM_CAPTURE_FALLING_EDGE()      {_stio1 = 0; _stio0 = 1;}

/* Input capture at rising/falling edge */
#define STM_CAPTURE_BOTH_EDGE()         {_stio1 = 1; _stio0 = 0;}

/* Input capture disable */
#define STM_CAPTURE_DISABLE()           {_stio1 = 1; _stio0 = 1;}

/*========= The end of Select STMn function in Capture input mode ============*/

/*======================= Select STMn operating mode =========================*/
//  #define STM_TIMER_COUNTER_MODE          (1)
//  #define STM_PWM_OUTPUT_MODE             (1)
//  #define STM_COMPARE_MATCH_MODE          (1)
//  #define STM_CAPTURE_INPUT_MODE          (1)
//  #define STM_SINGLE_PULSE_OUTPUT_MODE    (1)

/*================= The end of Select STMn operating mode ====================*/

/*======================= Select STMn counter clock ==========================*/
//  #define STM_FSYS_DIV4               (1)
//  #define STM_FSYS                    (1)
//  #define STM_FH_DIV16                (1)
//  #define STM_FH_DIV64                (1)
//  #define STM_FSUB                    (1)
//  #define STM_TCK_RISING_EDGE         (1)
//  #define STM_TCK_FALLING_EDGE        (1)

/*================== The end of Select STMn counter clock ====================*/

/*=================== Select STMn counter clear condition ====================*/
//  #define STM_CCRA_MATCH              (1)
//  #define STM_CCRP_MATCH              (1)

/*============= The end of Select STMn counter clear condition ===============*/

/*========================= PWM Output Mode setting ==========================*/
#ifdef  STM_PWM_OUTPUT_MODE
    
    /* STP output control */
    //  #define STM_ACTIVE_LOW          (1)
    //  #define STM_ACTIVE_HIGH         (1)
    /* The end of STP output control */
    
    /* STP output polarity control */
    //  #define STM_NON_INVERTED        (1)
    //  #define STM_INVERTED            (1)
    /* The end of STP output polarity control */
    
    /* STM PWM period/duty control */
    //  #define STM_CCRP_P_CCRA_D       (1)     /*CCRP - period; CCRA - duty*/
    //  #define STM_CCRP_D_CCRA_P       (1)     /*CCRP - duty; CCRA - period*/
    /* The end of STM PWM period/duty control */
#endif

/*=================== The end of PWM Output Mode setting =====================*/

/*==================== Single Pulse Output Mode setting ======================*/
#ifdef  STM_SINGLE_PULSE_OUTPUT_MODE
    
    /* STP output control */
    //  #define STM_ACTIVE_LOW          (1)
    //  #define STM_ACTIVE_HIGH         (1)
    /* The end of STP output control */
    
    /* STP output polarity control */
    //  #define STM_NON_INVERTED        (1)
    //  #define STM_INVERTED            (1)
    /* The end of STP output polarity control */
#endif

/*=============== The end of Single Pulse Output Mode setting ================*/

/*======================= Timer Counter Mode setting =========================*/
#ifdef  STM_TIMER_COUNTER_MODE
    
    #define STM_GET_COUNTER_VALUE()     (_stmdh<<8 | _stmdl)
#endif

/*================= The end of Timer Counter Mode setting ====================*/

/*======================= Compare Match Mode setting =========================*/
#ifdef  STM_COMPARE_MATCH_MODE
    
    /* Select STM function in Compare match output mode */
    //  #define STM_NO_CHANGE           (1)
    //  #define STM_OUTPUT_LOW          (1)
    //  #define STM_OUTPUT_HIGH         (1)
    //  #define STM_OUTPUT_TOGGLE       (1)
    /* The end of Select STMn function in Compare match output mode */
    
    /* STP output control */
    //  #define STM_INITIAL_LOW         (1)
    //  #define STM_INITIAL_HIGH        (1)
    /* The end of STP output control */
    
    /* STP output polarity control */
    //  #define STM_NON_INVERTED        (1)
    //  #define STM_INVERTED            (1)
    /* The end of STP output polarity control */
#endif

/*================= The end of Compare Match Mode setting ====================*/

/*======================= Capture Input Mode setting =========================*/
#ifdef  STM_CAPTURE_INPUT_MODE
    
    /* Get STM Capture value function */
    #define STM_GET_CAPTURE_VALUE()     (_stmah<<8 | _stmal)
#endif

/*================= The end of Capture Input Mode setting ====================*/

/* Exported functions---------------------------------------------------------*/
void STM_Init(void);
void STM_PwmOutputConfig(void);
void STM_PwmUpdate(u16 TempCCRA,u8 TempCCRP);
void STM_SinglePulseOutputConfig(void);
void STM_SinglePulseUpdate(u16 TempCCRA);
void STM_CounterModeConfig(u16 TempPeriod);
void STM_CompareMatchOutputConfig(void);
void STM_CompareMatchOutputUpdate(u16 TempMatchTime);


#endif

/*********** (C) COPYRIGHT 2019 Holtek Semiconductor Inc **********END OF FILE*/
