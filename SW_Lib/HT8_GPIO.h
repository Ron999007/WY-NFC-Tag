/*******************************************************************************
  * @file     HT8_GPIO.h
  * @brief    The header file of the GPIO library.
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

/* Define to prevent recursive inclusion--------------------------------------*/
#ifndef _HT8_GPIO_H_
#define _HT8_GPIO_H_

/* Includes-------------------------------------------------------------------*/
#include "HT8_MCU_IP_SEL.h"

/* Exported constants---------------------------------------------------------*/
#define READ_PORT_FUNC_ENABLE()     (_iecc = 0b11001010)/*Enable read port function*/
#define READ_PORT_FUNC_DISABLE()    (_iecc = 0b00000000)/*Disable read port function*/

/*========= Select Pull-high resistor when low voltage power supply ==========*/
    #define RPH_60K_3V      (1)     /*All pin RPH are 60k£[ @ 3V*/
//  #define RPH_15K_3V      (1)     /*All pin RPH are 15k£[ @ 3V*/
/*=== The end of Select Pull-high resistor when low voltage power supply =====*/

/*======================= Select GPIO PC3~PC0 Power ==========================*/
//  #define PC3_PC0_POWER_VDD       (1)     /*Power from VDD*/
    #define PC3_PC0_POWER_VDDIO     (1)     /*Power from VDDIO*/
/*================== The end of Select GPIO PC3~PC0 Power ====================*/

/*===================== SW LCD COM level output define =======================*/
#define PD0_COM         {_pds01 = 1; _pds00 = 1;}
#define PD0_Out_H       {_pds01 = 0; _pds00 = 0; _pdc0 = 0; _pd0 = 1;}
#define PD0_Out_L       {_pds01 = 0; _pds00 = 0; _pdc0 = 0; _pd0 = 0;}

#define PD1_COM         {_pds03 = 1; _pds02 = 1;}
#define PD1_Out_H       {_pds03 = 0; _pds02 = 0; _pdc1 = 0; _pd1 = 1;}
#define PD1_Out_L       {_pds03 = 0; _pds02 = 0; _pdc1 = 0; _pd1 = 0;}

#define PD2_COM         {_pds05 = 1; _pds04 = 1;}
#define PD2_Out_H       {_pds05 = 0; _pds04 = 0; _pdc2 = 0; _pd2 = 1;}
#define PD2_Out_L       {_pds05 = 0; _pds04 = 0; _pdc2 = 0; _pd2 = 0;}

#define PD3_COM         {_pds07 = 1; _pds06 = 1;}
#define PD3_Out_H       {_pds07 = 0; _pds06 = 0; _pdc3 = 0; _pd3 = 1;}
#define PD3_Out_L       {_pds07 = 0; _pds06 = 0; _pdc3 = 0; _pd3 = 0;}

/*=============== The end of SW LCD COM level output define ==================*/


/*=========================== Select PA0 function ============================*/
//  #define PA0_Outout_H    (1)     /*Output mode, output high*/
    #define PA0_Outout_L    (1)     /*Output mode, output low*/
//  #define PA0_Input       (1)     /*Input mode, floating*/
//  #define PA0_Input_PU    (1)     /*Input mode, pull up*/
//  #define PA0_WU          (1)     /*Wake up enable*/
//  #define PA0_PU          (1)     /*Pull up enable*/
/*===================== The end of Select PA0 function =======================*/

/*=========================== Select PA1 function ============================*/
//  #define PA1_Outout_H    (1)     /*Output mode, output high*/
//  #define PA1_Outout_L    (1)     /*Output mode, output low*/
    #define PA1_Input       (1)     /*Input mode, floating*/
//  #define PA1_Input_PU    (1)     /*Input mode, pull up*/
//  #define PA1_INT1        (1)     /*External interrupt 1 function*/
//  #define PA1_STP         (1)     /*STM output function*/
//  #define PA1_WU          (1)     /*Wake up enable*/
    #define PA1_PU          (1)     /*Pull up enable*/
/*===================== The end of Select PA1 function =======================*/

/*=========================== Select PA2 function ============================*/
//  #define PA2_Outout_H    (1)     /*Output mode, output high*/
    #define PA2_Outout_L    (1)     /*Output mode, output low*/
//  #define PA2_Input       (1)     /*Input mode, floating*/
//  #define PA2_Input_PU    (1)     /*Input mode, pull up*/
//  #define PA2_WU          (1)     /*Wake up enable*/
//  #define PA2_PU          (1)     /*Pull up enable*/
/*===================== The end of Select PA2 function =======================*/

/*=========================== Select PA3 function ============================*/
//  #define PA3_Outout_H    (1)     /*Output mode, output high*/
//  #define PA3_Outout_L    (1)     /*Output mode, output low*/
    #define PA3_Input       (1)     /*Input mode, floating*/
//  #define PA3_Input_PU    (1)     /*Input mode, pull up*/
//  #define PA3_INT0        (1)     /*External interrupt 0 function*/
//  #define PA3_PTP0        (1)     /*PTM0 output function*/
    #define PA3_WU          (1)     /*Wake up enable*/
    #define PA3_PU          (1)     /*Pull up enable*/
/*===================== The end of Select PA3 function =======================*/

/*=========================== Select PA4 function ============================*/
//  #define PA4_Outout_H    (1)     /*Output mode, output high*/
//  #define PA4_Outout_L    (1)     /*Output mode, output low*/
//  #define PA4_Input       (1)     /*Input mode, floating*/
//  #define PA4_Input_PU    (1)     /*Input mode, pull up*/
//  #define PA4_PTCK0       (1)     /*PTM0 TCK input function*/
    #define PA4_VDDIO       (1)     /*PC3~PC0 pin power*/
//  #define PA4_WU          (1)     /*Wake up enable*/
//  #define PA4_PU          (1)     /*Pull up enable*/
/*===================== The end of Select PA4 function =======================*/

/*=========================== Select PA5 function ============================*/
//  #define PA5_Outout_H    (1)     /*Output mode, output high*/
//  #define PA5_Outout_L    (1)     /*Output mode, output low*/
    #define PA5_Input       (1)     /*Input mode, floating*/
//  #define PA5_Input_PU    (1)     /*Input mode, pull up*/
//  #define PA5_STCK        (1)     /*STM TCK input function*/
//  #define PA5_WU          (1)     /*Wake up enable*/
    #define PA5_PU          (1)     /*Pull up enable*/
/*===================== The end of Select PA5 function =======================*/

/*=========================== Select PA6 function ============================*/
//  #define PA6_Outout_H    (1)     /*Output mode, output high*/
//  #define PA6_Outout_L    (1)     /*Output mode, output low*/
//  #define PA6_Input       (1)     /*Input mode, floating*/
//  #define PA6_Input_PU    (1)     /*Input mode, pull up*/
//  #define PA6_PTP0I       (1)     /*PTM0 input function*/
//  #define PA6_WU          (1)     /*Wake up enable*/
//  #define PA6_PU          (1)     /*Pull up enable*/
/*===================== The end of Select PA6 function =======================*/

/*=========================== Select PA7 function ============================*/
//  #define PA7_Outout_H    (1)     /*Output mode, output high*/
//  #define PA7_Outout_L    (1)     /*Output mode, output low*/
//  #define PA7_Input       (1)     /*Input mode, floating*/
//  #define PA7_Input_PU    (1)     /*Input mode, pull up*/
//  #define PA7_PTP0I       (1)     /*PTM0 input function*/
//  #define PA7_WU          (1)     /*Wake up enable*/
//  #define PA7_PU          (1)     /*Pull up enable*/
/*===================== The end of Select PA7 function =======================*/

/*=========================== Select PB0 function ============================*/
//  #define PB0_Outout_H    (1)     /*Output mode, output high*/
//  #define PB0_Outout_L    (1)     /*Output mode, output low*/
    #define PB0_Input       (1)     /*Input mode, floating*/
//  #define PB0_Input_PU    (1)     /*Input mode, pull up*/
//  #define PB0_AN0         (1)     /*A/D channel 0 function*/
//  #define PB0_VREF        (1)     /*ADC reference voltage input function*/
    #define PB0_PU          (1)     /*Pull up enable*/
/*===================== The end of Select PB0 function =======================*/

/*=========================== Select PB1 function ============================*/
//  #define PB1_Outout_H    (1)     /*Output mode, output high*/
//  #define PB1_Outout_L    (1)     /*Output mode, output low*/
    #define PB1_Input       (1)     /*Input mode, floating*/
//  #define PB1_Input_PU    (1)     /*Input mode, pull up*/
//  #define PB1_STCK        (1)     /*STM TCK input function*/
//  #define PB1_AN1         (1)     /*A/D channel 1 function*/
    #define PB1_PU          (1)     /*Pull up enable*/
/*===================== The end of Select PB1 function =======================*/

/*=========================== Select PB2 function ============================*/
    #define PB2_Outout_H    (1)     /*Output mode, output high*/
//  #define PB2_Outout_L    (1)     /*Output mode, output low*/
//  #define PB2_Input       (1)     /*Input mode, floating*/
//  #define PB2_Input_PU    (1)     /*Input mode, pull up*/
//  #define PB2_PTCK0       (1)     /*PTM0 TCK input function*/
//  #define PB2_AN2         (1)     /*A/D channel 2 function*/
//  #define PB2_PU          (1)     /*Pull up enable*/
/*===================== The end of Select PB2 function =======================*/

/*=========================== Select PB3 function ============================*/
//  #define PB3_Outout_H    (1)     /*Output mode, output high*/
//  #define PB3_Outout_L    (1)     /*Output mode, output low*/
    #define PB3_Input       (1)     /*Input mode, floating*/
//  #define PB3_Input_PU    (1)     /*Input mode, pull up*/
//  #define PB3_PTCK1       (1)     /*PTM1 TCK input function*/
//  #define PB3_AN3         (1)     /*A/D channel 3 function*/
    #define PB3_PU          (1)     /*Pull up enable*/
/*===================== The end of Select PB3 function =======================*/

/*=========================== Select PB4 function ============================*/
    #define PB4_Outout_H    (1)     /*Output mode, output high*/
//  #define PB4_Outout_L    (1)     /*Output mode, output low*/
//  #define PB4_Input       (1)     /*Input mode, floating*/
//  #define PB4_Input_PU    (1)     /*Input mode, pull up*/
//  #define PB4_INT0        (1)     /*External interrupt 0 function*/
//  #define PB4_PTP0B       (1)     /*PTM0B output function*/
//  #define PB4_AN4         (1)     /*A/D channel 4 function*/
//  #define PB4_PU          (1)     /*Pull up enable*/
/*===================== The end of Select PB4 function =======================*/

/*=========================== Select PB5 function ============================*/
//  #define PB5_Outout_H    (1)     /*Output mode, output high*/
//  #define PB5_Outout_L    (1)     /*Output mode, output low*/
    #define PB5_Input       (1)     /*Input mode, floating*/
//  #define PB5_Input_PU    (1)     /*Input mode, pull up*/
//  #define PB5_INT1        (1)     /*External interrupt 1 function*/
//  #define PB5_STPB        (1)     /*STMB output function*/
//  #define PB5_AN5         (1)     /*A/D channel 5 function*/
    #define PB5_PU          (1)     /*Pull up enable*/
/*===================== The end of Select PB5 function =======================*/

/*=========================== Select PB6 function ============================*/
//  #define PB6_Outout_H    (1)     /*Output mode, output high*/
    #define PB6_Outout_L    (1)     /*Output mode, output low*/
//  #define PB6_Input       (1)     /*Input mode, floating*/
//  #define PB6_Input_PU    (1)     /*Input mode, pull up*/
//  #define PB6_STPI        (1)     /*STM input function*/
//  #define PB6_AN6         (1)     /*A/D channel 6 function*/
//  #define PB6_PU          (1)     /*Pull up enable*/
/*===================== The end of Select PB6 function =======================*/

/*=========================== Select PB7 function ============================*/
//  #define PB7_Outout_H    (1)     /*Output mode, output high*/
//  #define PB7_Outout_L    (1)     /*Output mode, output low*/
    #define PB7_Input       (1)     /*Input mode, floating*/
//  #define PB7_Input_PU    (1)     /*Input mode, pull up*/
//  #define PB7_RESB        (1)     /*Reset pin function*/
//  #define PB7_AN7         (1)     /*A/D channel 7 function*/
    #define PB7_PU          (1)     /*Pull up enable*/
/*===================== The end of Select PB7 function =======================*/

/*=========================== Select PC0 function ============================*/
//  #define PC0_Outout_H    (1)     /*Output mode, output high*/
    #define PC0_Outout_L    (1)     /*Output mode, output low*/
//  #define PC0_Input       (1)     /*Input mode, floating*/
//  #define PC0_Input_PU    (1)     /*Input mode, pull up*/
//  #define PC0_STPI        (1)     /*STM input function*/
//  #define PC0_SCSB        (1)     /*SIM SCSB function*/
    #define PC0_PU          (1)     /*Pull up enable*/
/*===================== The end of Select PC0 function =======================*/

/*=========================== Select PC1 function ============================*/
    #define PC1_Outout_H    (1)     /*Output mode, output high*/
//  #define PC1_Outout_L    (1)     /*Output mode, output low*/
//  #define PC1_Input       (1)     /*Input mode, floating*/
//  #define PC1_Input_PU    (1)     /*Input mode, pull up*/
//  #define PC1_SDI         (1)     /*SIM SDI function*/
//  #define PC1_SDA         (1)     /*SIM SDA function*/
//  #define PC1_URX_UTX     (1)     /*USIM UART RX function or (RX & TX) function*/
    #define PC1_PU          (1)     /*Pull up enable*/
/*===================== The end of Select PC1 function =======================*/

/*=========================== Select PC2 function ============================*/
//  #define PC2_Outout_H    (1)     /*Output mode, output high*/
//  #define PC2_Outout_L    (1)     /*Output mode, output low*/
//  #define PC2_Input       (1)     /*Input mode, floating*/
//  #define PC2_Input_PU    (1)     /*Input mode, pull up*/
    #define PC2_SDO         (1)     /*SIM SDO function*/
//  #define PC2_UTX         (1)     /*USIM UART TX function*/
    #define PC2_PU          (1)     /*Pull up enable*/
/*===================== The end of Select PC2 function =======================*/

/*=========================== Select PC3 function ============================*/
//  #define PC3_Outout_H    (1)     /*Output mode, output high*/
//  #define PC3_Outout_L    (1)     /*Output mode, output low*/
//  #define PC3_Input       (1)     /*Input mode, floating*/
//  #define PC3_Input_PU    (1)     /*Input mode, pull up*/
    #define PC3_SCK         (1)     /*SIM SCK function*/
//  #define PC3_SCL         (1)     /*SIM SCL function*/
    #define PC3_PU          (1)     /*Pull up enable*/
/*===================== The end of Select PC3 function =======================*/

/*=========================== Select PC4 function ============================*/
//  #define PC4_Outout_H    (1)     /*Output mode, output high*/
//  #define PC4_Outout_L    (1)     /*Output mode, output low*/
    #define PC4_Input       (1)     /*Input mode, floating*/
//  #define PC4_Input_PU    (1)     /*Input mode, pull up*/
    #define PC4_PU          (1)     /*Pull up enable*/
/*===================== The end of Select PC4 function =======================*/

/*=========================== Select PC5 function ============================*/
//  #define PC5_Outout_H    (1)     /*Output mode, output high*/
//  #define PC5_Outout_L    (1)     /*Output mode, output low*/
    #define PC5_Input       (1)     /*Input mode, floating*/
//  #define PC5_Input_PU    (1)     /*Input mode, pull up*/
    #define PC5_PU          (1)     /*Pull up enable*/
/*===================== The end of Select PC5 function =======================*/

/*=========================== Select PC6 function ============================*/
//  #define PC6_Outout_H    (1)     /*Output mode, output high*/
//  #define PC6_Outout_L    (1)     /*Output mode, output low*/
    #define PC6_Input       (1)     /*Input mode, floating*/
//  #define PC6_Input_PU    (1)     /*Input mode, pull up*/
//  #define PC6_PTP1I       (1)     /*PTM1 input function*/
    #define PC6_PU          (1)     /*Pull up enable*/
/*===================== The end of Select PC6 function =======================*/

/*=========================== Select PC7 function ============================*/
//  #define PC7_Outout_H    (1)     /*Output mode, output high*/
//  #define PC7_Outout_L    (1)     /*Output mode, output low*/
    #define PC7_Input       (1)     /*Input mode, floating*/
//  #define PC7_Input_PU    (1)     /*Input mode, pull up*/
    #define PC7_PU          (1)     /*Pull up enable*/
/*===================== The end of Select PC7 function =======================*/

/*=========================== Select PD0 function ============================*/
//  #define PD0_Outout_H    (1)     /*Output mode, output high*/
//  #define PD0_Outout_L    (1)     /*Output mode, output low*/
    #define PD0_Input       (1)     /*Input mode, floating*/
//  #define PD0_Input_PU    (1)     /*Input mode, pull up*/
//  #define PD0_PTCK1       (1)     /*PTM1 TCK input function*/
//  #define PD0_SCOM0       (1)     /*LCD function SCOM0*/
    #define PD0_PU          (1)     /*Pull up enable*/
/*===================== The end of Select PD0 function =======================*/

/*=========================== Select PD1 function ============================*/
    #define PD1_Outout_H    (1)     /*Output mode, output high*/
//  #define PD1_Outout_L    (1)     /*Output mode, output low*/
//  #define PD1_Input       (1)     /*Input mode, floating*/
//  #define PD1_Input_PU    (1)     /*Input mode, pull up*/
//  #define PD1_PTP1I       (1)     /*PTM1 input function*/
//  #define PD1_SCOM1       (1)     /*LCD function SCOM1*/
    #define PD1_PU          (1)     /*Pull up enable*/
/*===================== The end of Select PD1 function =======================*/

/*=========================== Select PD2 function ============================*/
//  #define PD2_Outout_H    (1)     /*Output mode, output high*/
//  #define PD2_Outout_L    (1)     /*Output mode, output low*/
    #define PD2_Input       (1)     /*Input mode, floating*/
//  #define PD2_Input_PU    (1)     /*Input mode, pull up*/
//  #define PD2_PTP1        (1)     /*PTM1 output function*/
//  #define PD2_SCOM2       (1)     /*LCD function SCOM2*/
    #define PD2_PU          (1)     /*Pull up enable*/
/*===================== The end of Select PD2 function =======================*/

/*=========================== Select PD3 function ============================*/
//  #define PD3_Outout_H    (1)     /*Output mode, output high*/
//  #define PD3_Outout_L    (1)     /*Output mode, output low*/
    #define PD3_Input       (1)     /*Input mode, floating*/
//  #define PD3_Input_PU    (1)     /*Input mode, pull up*/
//  #define PD3_PTP1B       (1)     /*PTM1B output function*/
//  #define PD3_SCOM3       (1)     /*LCD function SCOM3*/
    #define PD3_PU          (1)     /*Pull up enable*/
/*===================== The end of Select PD3 function =======================*/

/*=========================== Select PD4 function ============================*/
//  #define PD4_Outout_H    (1)     /*Output mode, output high*/
//  #define PD4_Outout_L    (1)     /*Output mode, output low*/
    #define PD4_Input       (1)     /*Input mode, floating*/
//  #define PD4_Input_PU    (1)     /*Input mode, pull up*/
    #define PD4_PU          (1)     /*Pull up enable*/
/*===================== The end of Select PD4 function =======================*/

/*=========================== Select PD5 function ============================*/
//  #define PD5_Outout_H    (1)     /*Output mode, output high*/
//  #define PD5_Outout_L    (1)     /*Output mode, output low*/
    #define PD5_Input       (1)     /*Input mode, floating*/
//  #define PD5_Input_PU    (1)     /*Input mode, pull up*/
    #define PD5_PU          (1)     /*Pull up enable*/
/*===================== The end of Select PD5 function =======================*/

/*===================== Select PA3~PA0 source current ========================*/
    #define PA3_PA0_Level_0     (1)     /*PA3~PA0 source current Level 0*/
//  #define PA3_PA0_Level_1     (1)     /*PA3~PA0 source current Level 1*/
//  #define PA3_PA0_Level_2     (1)     /*PA3~PA0 source current Level 2*/
//  #define PA3_PA0_Level_3     (1)     /*PA3~PA0 source current Level 3*/
/*================ The end of Select PA3~PA0 source current ==================*/

/*===================== Select PA7~PA4 source current ========================*/
    #define PA7_PA4_Level_0     (1)     /*PA7~PA4 source current Level 0*/
//  #define PA7_PA4_Level_1     (1)     /*PA7~PA4 source current Level 1*/
//  #define PA7_PA4_Level_2     (1)     /*PA7~PA4 source current Level 2*/
//  #define PA7_PA4_Level_3     (1)     /*PA7~PA4 source current Level 3*/
/*================ The end of Select PA7~PA4 source current ==================*/

/*===================== Select PB3~PB0 source current ========================*/
    #define PB3_PB0_Level_0     (1)     /*PB3~PB0 source current Level 0*/
//  #define PB3_PB0_Level_1     (1)     /*PB3~PB0 source current Level 1*/
//  #define PB3_PB0_Level_2     (1)     /*PB3~PB0 source current Level 2*/
//  #define PB3_PB0_Level_3     (1)     /*PB3~PB0 source current Level 3*/
/*================ The end of Select PB3~PB0 source current ==================*/

/*===================== Select PB7~PB4 source current ========================*/
    #define PB7_PB4_Level_0     (1)     /*PB7~PB4 source current Level 0*/
//  #define PB7_PB4_Level_1     (1)     /*PB7~PB4 source current Level 1*/
//  #define PB7_PB4_Level_2     (1)     /*PB7~PB4 source current Level 2*/
//  #define PB7_PB4_Level_3     (1)     /*PB7~PB4 source current Level 3*/
/*================ The end of Select PB7~PB4 source current ==================*/

/*===================== Select PC3~PC0 source current ========================*/
    #define PC3_PC0_Level_0     (1)     /*PC3~PC0 source current Level 0*/
//  #define PC3_PC0_Level_1     (1)     /*PC3~PC0 source current Level 1*/
//  #define PC3_PC0_Level_2     (1)     /*PC3~PC0 source current Level 2*/
//  #define PC3_PC0_Level_3     (1)     /*PC3~PC0 source current Level 3*/
/*================ The end of Select PC3~PC0 source current ==================*/

/*===================== Select PC7~PC4 source current ========================*/
    #define PC7_PC4_Level_0     (1)     /*PC7~PC4 source current Level 0*/
//  #define PC7_PC4_Level_1     (1)     /*PC7~PC4 source current Level 1*/
//  #define PC7_PC4_Level_2     (1)     /*PC7~PC4 source current Level 2*/
//  #define PC7_PC4_Level_3     (1)     /*PC7~PC4 source current Level 3*/
/*================ The end of Select PC7~PC4 source current ==================*/

/*===================== Select PD3~PD0 source current ========================*/
    #define PD3_PD0_Level_0     (1)     /*PD3~PD0 source current Level 0*/
//  #define PD3_PD0_Level_1     (1)     /*PD3~PD0 source current Level 1*/
//  #define PD3_PD0_Level_2     (1)     /*PD3~PD0 source current Level 2*/
//  #define PD3_PD0_Level_3     (1)     /*PD3~PD0 source current Level 3*/
/*================ The end of Select PD3~PD0 source current ==================*/

/*===================== Select PD5~PD4 source current ========================*/
    #define PD5_PD4_Level_0     (1)     /*PD5~PD4 source current Level 0*/
//  #define PD5_PD4_Level_1     (1)     /*PD5~PD4 source current Level 1*/
//  #define PD5_PD4_Level_2     (1)     /*PD5~PD4 source current Level 2*/
//  #define PD5_PD4_Level_3     (1)     /*PD5~PD4 source current Level 3*/
/*================ The end of Select PD5~PD4 source current ==================*/

/* Exported functions---------------------------------------------------------*/
void GPIO_Init(void);

#endif

/************************ (C) COPYRIGHT 2019 Holtek Semiconductor Inc ************************END OF FILE****/
