/*******************************************************************************
  * @file     HT8_PTM.h
  * @brief    The header file of the PTM library.
  * @author   Holtek Semiconductor Inc.
  * @version  V1.0.0
  * @date     2024-3-19
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
#ifndef _HT8_PTM_H_
#define _HT8_PTM_H_

/* Includes-------------------------------------------------------------------*/
#include "HT8_MCU_IP_SEL.h"

/* Exported constants---------------------------------------------------------*/
#define PTM0_ENABLE()               (_pt0on = 1)
#define PTM0_DISABLE()              (_pt0on = 0)
#define PTM0_CCRA_ISR_ENABLE()      (_ptm0ae = 1)
#define PTM0_CCRA_ISR_DISABLE()     (_ptm0ae = 0)
#define PTM0_SET_CCRA_ISR_FLAG()    (_ptm0af = 1)
#define PTM0_CLEAR_CCRA_ISR_FLAG()  (_ptm0af = 0)
#define PTM0_CCRP_ISR_ENABLE()      (_ptm0pe = 1)
#define PTM0_CCRP_ISR_DISABLE()     (_ptm0pe = 0)
#define PTM0_SET_CCRP_ISR_FLAG()    (_ptm0pf = 1)
#define PTM0_CLEAR_CCRP_ISR_FLAG()  (_ptm0pf = 0)
#define PTM0_PAUSE()                (_pt0pau = 1)
#define PTM0_RUN()                  (_pt0pau = 0)
#define PTM0_GET_CCRA_ISR_FLAG()    _ptm0af
#define PTM0_GET_CCRP_ISR_FLAG()    _ptm0pf

#define PTM1_ENABLE()               (_pt1on = 1)
#define PTM1_DISABLE()              (_pt1on = 0)
#define PTM1_CCRA_ISR_ENABLE()      (_ptm1ae = 1)
#define PTM1_CCRA_ISR_DISABLE()     (_ptm1ae = 0)
#define PTM1_SET_CCRA_ISR_FLAG()    (_ptm1af = 1)
#define PTM1_CLEAR_CCRA_ISR_FLAG()  (_ptm1af = 0)
#define PTM1_CCRP_ISR_ENABLE()      (_ptm1pe = 1)
#define PTM1_CCRP_ISR_DISABLE()     (_ptm1pe = 0)
#define PTM1_SET_CCRP_ISR_FLAG()    (_ptm1pf = 1)
#define PTM1_CLEAR_CCRP_ISR_FLAG()  (_ptm1pf = 0)
#define PTM1_PAUSE()                (_pt1pau = 1)
#define PTM1_RUN()                  (_pt1pau = 0)
#define PTM1_GET_CCRA_ISR_FLAG()    _ptm1af
#define PTM1_GET_CCRP_ISR_FLAG()    _ptm1pf


/*=============== Select PTMn function in Capture input mode =================*/
/* Input capture at rising edge */
#define PTM0_CAPTURE_RISING_EDGE()      {_pt0io1 = 0; _pt0io0 = 0;}

/* Input capture at falling edge */
#define PTM0_CAPTURE_FALLING_EDGE()     {_pt0io1 = 0; _pt0io0 = 1;}

/* Input capture at rising/falling edge */
#define PTM0_CAPTURE_BOTH_EDGE()        {_pt0io1 = 1; _pt0io0 = 0;}

/* Input capture disable */
#define PTM0_CAPTURE_DISABLE()          {_pt0io1 = 1; _pt0io0 = 1;}

/* Input capture at rising edge */
#define PTM1_CAPTURE_RISING_EDGE()      {_pt1io1 = 0; _pt1io0 = 0;}

/* Input capture at falling edge */
#define PTM1_CAPTURE_FALLING_EDGE()     {_pt1io1 = 0; _pt1io0 = 1;}

/* Input capture at rising/falling edge */
#define PTM1_CAPTURE_BOTH_EDGE()        {_pt1io1 = 1; _pt1io0 = 0;}

/* Input capture disable */
#define PTM1_CAPTURE_DISABLE()          {_pt1io1 = 1; _pt1io0 = 1;}


/*======================= Select PTMn operating mode =========================*/
//  #define PTM0_TIMER_COUNTER_MODE         (1)
//  #define PTM0_PWM_OUTPUT_MODE            (1)
  #define PTM0_COMPARE_MATCH_MODE         (1)
//  #define PTM0_CAPTURE_INPUT_MODE         (1)
//  #define PTM0_SINGLE_PULSE_OUTPUT_MODE   (1)

//  #define PTM1_TIMER_COUNTER_MODE         (1)
//  #define PTM1_PWM_OUTPUT_MODE            (1)
//  #define PTM1_COMPARE_MATCH_MODE         (1)
//  #define PTM1_CAPTURE_INPUT_MODE         (1)
//  #define PTM1_SINGLE_PULSE_OUTPUT_MODE   (1)

/*================= The end of Select PTMn operating mode ====================*/

/*======================= Select PTMn counter clock ==========================*/
//  #define PTM0_FSYS_DIV4              (1)
    #define PTM0_FSYS                   (1)
//  #define PTM0_FH_DIV16               (1)
//  #define PTM0_FH_DIV64               (1)
//  #define PTM0_FSUB                   (1)
//  #define PTM0_TCK_RISING_EDGE        (1)
//  #define PTM0_TCK_FALLING_EDGE       (1)

//  #define PTM1_FSYS_DIV4              (1)
//  #define PTM1_FSYS                   (1)
//  #define PTM1_FH_DIV16               (1)
//  #define PTM1_FH_DIV64               (1)
//  #define PTM1_FSUB                   (1)
//  #define PTM1_TCK_RISING_EDGE        (1)
//  #define PTM1_TCK_FALLING_EDGE       (1)

/*================== The end of Select PTMn counter clock ====================*/

/*=================== Select PTMn counter clear condition ====================*/
    #define PTM0_CCRA_MATCH             (1)
//  #define PTM0_CCRP_MATCH             (1)

//  #define PTM1_CCRA_MATCH             (1)
//  #define PTM1_CCRP_MATCH             (1)

/*============= The end of Select PTMn counter clear condition ===============*/

/*========================= PWM OUTPUT MODE setting ==========================*/
#ifdef  PTM0_PWM_OUTPUT_MODE
    
    /* PTP0 output control */
    //  #define PTM0_ACTIVE_LOW         (1)
    //  #define PTM0_ACTIVE_HIGH        (1)
    /* The end of PTP0 output control */
    
    /* PTP0 output polarity control */
    //  #define PTM0_NON_INVERTED       (1)
    //  #define PTM0_INVERTED           (1)
    /* The end of PTP0 output polarity control */
#endif

#ifdef  PTM1_PWM_OUTPUT_MODE
    
    /* PTP1 output control */
    //  #define PTM1_ACTIVE_LOW         (1)
    //  #define PTM1_ACTIVE_HIGH        (1)
    /* The end of PTP1 output control */
    
    /* PTP1 output polarity control */
    //  #define PTM1_NON_INVERTED       (1)
    //  #define PTM1_INVERTED           (1)
    /* The end of PTP1 output polarity control */
#endif

/*=================== The end of PWM OUTPUT MODE setting =====================*/

/*==================== SINGLE PULSE OUTPUT MODE setting ======================*/
#ifdef  PTM0_SINGLE_PULSE_OUTPUT_MODE
    
    /* PTP0 output control */
    //  #define PTM0_ACTIVE_LOW         (1)
    //  #define PTM0_ACTIVE_HIGH        (1)
    /* The end of PTP0 output control */
    
    /* PTP0 output polarity control */
    //  #define PTM0_NON_INVERTED       (1)
    //  #define PTM0_INVERTED           (1)
    /* The end of PTP0 output polarity control */
#endif

#ifdef  PTM1_SINGLE_PULSE_OUTPUT_MODE
    
    /* PTP1 output control */
    //  #define PTM1_ACTIVE_LOW         (1)
    //  #define PTM1_ACTIVE_HIGH        (1)
    /* The end of PTP1 output control */
    
    /* PTP1 output polarity control */
    //  #define PTM1_NON_INVERTED       (1)
    //  #define PTM1_INVERTED           (1)
    /* The end of PTP1 output polarity control */
#endif

/*=============== The end of SINGLE PULSE OUTPUT MODE setting ================*/

/*======================= TIMER COUNTER MODE setting =========================*/
#ifdef  PTM0_TIMER_COUNTER_MODE
    
    #define PTM0_GET_COUNTER_VALUE()    (_ptm0dh<<8 | _ptm0dl)
#endif

#ifdef  PTM1_TIMER_COUNTER_MODE
    
    #define PTM1_GET_COUNTER_VALUE()    (_ptm1dh<<8 | _ptm1dl)
#endif

/*================= The end of TIMER COUNTER MODE setting ====================*/

/*======================= COMPARE MATCH MODE setting =========================*/
#ifdef  PTM0_COMPARE_MATCH_MODE
    
    /* Select PTM0 function in Compare match output mode */
      #define PTM0_NO_CHANGE          (1)
    //  #define PTM0_OUTPUT_LOW         (1)
    //  #define PTM0_OUTPUT_HIGH        (1)
    //  #define PTM0_OUTPUT_TOGGLE      (1)
    /* The end of Select PTMn function in Compare match output mode */
    
    /* PTP0 output control */
    //  #define PTM0_INITIAL_LOW        (1)
      #define PTM0_INITIAL_HIGH       (1)
    /* The end of PTP0 output control */
    
    /* PTP0 output polarity control */
      #define PTM0_NON_INVERTED       (1)
    //  #define PTM0_INVERTED           (1)
    /* The end of PTP0 output polarity control */
#endif

#ifdef  PTM1_COMPARE_MATCH_MODE
    
    /* Select PTM1 function in Compare match output mode */
    //  #define PTM1_NO_CHANGE          (1)
    //  #define PTM1_OUTPUT_LOW         (1)
    //  #define PTM1_OUTPUT_HIGH        (1)
    //  #define PTM1_OUTPUT_TOGGLE      (1)
    /* The end of Select PTMn function in Compare match output mode */
    
    /* PTP1 output control */
    //  #define PTM1_INITIAL_LOW        (1)
    //  #define PTM1_INITIAL_HIGH       (1)
    /* The end of PTP1 output control */
    
    /* PTP1 output polarity control */
    //  #define PTM1_NON_INVERTED       (1)
    //  #define PTM1_INVERTED           (1)
    /* The end of PTP1 output polarity control */
#endif

/*================= The end of COMPARE MATCH MODE setting ====================*/

/*======================= CAPTURE INPUT MODE setting =========================*/
#ifdef  PTM0_CAPTURE_INPUT_MODE
    
    /* Select PTM0 Trigger Pin function */
    //  #define PTM0_CAPTURE_PTP0I      (1)     /*From PTP0I pin*/
    //  #define PTM0_CAPTURE_PTCK0      (1)     /*From PTCK0 pin*/
    /* The end of Select PTM0 Trigger Pin function */
    
    /* GET PTM0 CAPTURE VALUE function */
    #define PTM0_GET_CAPTURE_VALUE()        (_ptm0ah<<8 | _ptm0al)
#endif

#ifdef  PTM1_CAPTURE_INPUT_MODE
    
    /* Select PTM1 Trigger Pin function */
    //  #define PTM1_CAPTURE_PTP1I      (1)     /*From PTP1I pin*/
    //  #define PTM1_CAPTURE_PTCK1      (1)     /*From PTCK1 pin*/
    /* The end of Select PTM1 Trigger Pin function */
    
    /* GET PTM1 CAPTURE VALUE function */
    #define PTM1_GET_CAPTURE_VALUE()        (_ptm1ah<<8 | _ptm1al)
#endif

/*================= The end of CAPTURE INPUT MODE setting ====================*/


/* Exported functions---------------------------------------------------------*/
void PTM0_Init(void);
void PTM0_PwmOutputConfig(void);
void PTM0_PwmUpdate(u16 TempCCRA,u16 TempCCRP);
void PTM0_SinglePulseOutputConfig(void);
void PTM0_SinglePulseUpdate(u16 TempCCRA);
void PTM0_CounterModeConfig(u16 TempPeriod);
void PTM0_CompareMatchOutputConfig(void);
void PTM0_CompareMatchOutputUpdate(u16 TempMatchTime);
void PTM0_CaptureInputConfig(void);

void PTM1_Init(void);
void PTM1_PwmOutputConfig(void);
void PTM1_PwmUpdate(u16 TempCCRA,u16 TempCCRP);
void PTM1_SinglePulseOutputConfig(void);
void PTM1_SinglePulseUpdate(u16 TempCCRA);
void PTM1_CounterModeConfig(u16 TempPeriod);
void PTM1_CompareMatchOutputConfig(void);
void PTM1_CompareMatchOutputUpdate(u16 TempMatchTime);
void PTM1_CaptureInputConfig(void);

#endif

/*********** (C) COPYRIGHT 2019 Holtek Semiconductor Inc **********END OF FILE*/
