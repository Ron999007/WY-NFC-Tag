/*******************************************************************************
  * @file     HT8_GPIO.c
  * @brief    This file provides all the GPIO firmware functions.
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
#include "HT8_GPIO.h"

/*******************************************************************************
  * @brief    GPIO initialization function.
  * @param    None
  * @retval   None
  *******************************************************************************/
void GPIO_Init(void)
{
/*========= Select Pull-high resistor when low voltage power supply ==========*/
    #ifdef  RPH_60K_3V
            _lvpu = 0;

    #elif   RPH_15K_3V
            _lvpu = 1;

    #endif

/*=== The end of Select Pull-high resistor when low voltage power supply =====*/

/*======================= Select GPIO PC3~PC0 Power ==========================*/
    #ifdef  PC3_PC0_POWER_VDD
            _pmps1 = 0; _pmps0 = 0;

    #elif   PC3_PC0_POWER_VDDIO
            _pmps1 = 1; _pmps0 = 0;
    #endif

/*================== The end of Select GPIO PC3~PC0 Power ====================*/

/*=========================== Select PA0 function ============================*/
    #ifdef  PA0_Outout_H
            _pac0 = 0; _pa0 = 1;

    #elif   PA0_Outout_L
            _pac0 = 0; _pa0 = 0;

    #elif   PA0_Input
            _pac0 = 1; _papu0 = 0;

    #elif   PA0_Input_PU
            _pac0 = 1; _papu0 = 1;

    #endif

    #ifdef  PA0_WU
            _pawu0 = 1;
    #endif

    #ifdef  PA0_PU
            _papu0 = 1;
    #endif

/*===================== The end of Select PA0 function =======================*/

/*=========================== Select PA1 function ============================*/
    #ifdef  PA1_Outout_H
            _pas03 = 0; _pas02 = 0; _pac1 = 0; _pa1 = 1;

    #elif   PA1_Outout_L
            _pas03 = 0; _pas02 = 0; _pac1 = 0; _pa1 = 0;

    #elif   PA1_Input
            _pas03 = 0; _pas02 = 0; _pac1 = 1; _papu1 = 0;

    #elif   PA1_Input_PU
            _pas03 = 0; _pas02 = 0; _pac1 = 1; _papu1 = 1;

    #elif   PA1_INT1
            _int1ps = 0; _pas03 = 0; _pas02 = 0; _pac1 = 1;

    #elif   PA1_STP
            _pas03 = 1; _pas02 = 1;

    #endif

    #ifdef  PA1_WU
            _pawu1 = 1;
    #endif

    #ifdef  PA1_PU
            _papu1 = 1;
    #endif

/*===================== The end of Select PA1 function =======================*/

/*=========================== Select PA2 function ============================*/
    #ifdef  PA2_Outout_H
            _pac2 = 0; _pa2 = 1;

    #elif   PA2_Outout_L
            _pac2 = 0; _pa2 = 0;

    #elif   PA2_Input
            _pac2 = 1; _papu2 = 0;

    #elif   PA2_Input_PU
            _pac2 = 1; _papu2 = 1;

    #endif

    #ifdef  PA2_WU
            _pawu2 = 1;
    #endif

    #ifdef  PA2_PU
            _papu2 = 1;
    #endif

/*===================== The end of Select PA2 function =======================*/

/*=========================== Select PA3 function ============================*/
    #ifdef  PA3_Outout_H
            _pas07 = 0; _pas06 = 0; _pac3 = 0; _pa3 = 1;

    #elif   PA3_Outout_L
            _pas07 = 0; _pas06 = 0; _pac3 = 0; _pa3 = 0;

    #elif   PA3_Input
            _pas07 = 0; _pas06 = 0; _pac3 = 1; _papu3 = 0;

    #elif   PA3_Input_PU
            _pas07 = 0; _pas06 = 0; _pac3 = 1; _papu3 = 1;

    #elif   PA3_INT0
            _int0ps = 0; _pas07 = 0; _pas06 = 0; _pac3 = 1;

    #elif   PA3_PTP0
            _pas07 = 1; _pas06 = 1;

    #endif

    #ifdef  PA3_WU
            _pawu3 = 1;
    #endif

    #ifdef  PA3_PU
            _papu3 = 1;
    #endif

/*===================== The end of Select PA3 function =======================*/

/*=========================== Select PA4 function ============================*/
    #ifdef  PA4_Outout_H
            _pas11 = 0; _pas10 = 0; _pac4 = 0; _pa4 = 1;

    #elif   PA4_Outout_L
            _pas11 = 0; _pas10 = 0; _pac4 = 0; _pa4 = 0;

    #elif   PA4_Input
            _pas11 = 0; _pas10 = 0; _pac4 = 1; _papu4 = 0;

    #elif   PA4_Input_PU
            _pas11 = 0; _pas10 = 0; _pac4 = 1; _papu4 = 1;

    #elif   PA4_PTCK0
            _ptck0ps = 0; _pas11 = 0; _pas10 = 0; _pac4 = 1;

    #elif   PA4_VDDIO
            _pas11 = 1; _pas10 = 1;

    #endif

    #ifdef  PA4_WU
            _pawu4 = 1;
    #endif

    #ifdef  PA4_PU
            _papu4 = 1;
    #endif

/*===================== The end of Select PA4 function =======================*/

/*=========================== Select PA5 function ============================*/
    #ifdef  PA5_Outout_H
            _pac5 = 0; _pa5 = 1;

    #elif   PA5_Outout_L
            _pac5 = 0; _pa5 = 0;

    #elif   PA5_Input
            _pac5 = 1; _papu5 = 0;

    #elif   PA5_Input_PU
            _pac5 = 1; _papu5 = 1;

    #elif   PA5_STCK
            _stckps = 0; _pac5 = 1;

    #endif

    #ifdef  PA5_WU
            _pawu5 = 1;
    #endif

    #ifdef  PA5_PU
            _papu5 = 1;
    #endif

/*===================== The end of Select PA5 function =======================*/

/*=========================== Select PA6 function ============================*/
    #ifndef FH_HXT_SE10M

        #ifndef FH_HXT_L10M

            #ifdef  PA6_Outout_H
                    _pas15 = 0; _pas14 = 0; _pac6 = 0; _pa6 = 1;

            #elif   PA6_Outout_L
                    _pas15 = 0; _pas14 = 0; _pac6 = 0; _pa6 = 0;

            #elif   PA6_Input
                    _pas15 = 0; _pas14 = 0; _pac6 = 1; _papu6 = 0;

            #elif   PA6_Input_PU
                    _pas15 = 0; _pas14 = 0; _pac6 = 1; _papu6 = 1;

            #elif   PA6_PTP0I
                    _ptp0ips = 0; _pas15 = 0; _pas14 = 0;

            #endif

            #ifdef  PA6_WU
                    _pawu6 = 1;
            #endif

            #ifdef  PA6_PU
                    _papu6 = 1;
            #endif

        #endif

    #endif

/*===================== The end of Select PA6 function =======================*/

/*=========================== Select PA7 function ============================*/
    #ifndef FH_HXT_SE10M

        #ifndef FH_HXT_L10M

            #ifdef  PA7_Outout_H
                    _pas17 = 0; _pas16 = 0; _pac7 = 0; _pa7 = 1;

            #elif   PA7_Outout_L
                    _pas17 = 0; _pas16 = 0; _pac7 = 0; _pa7 = 0;

            #elif   PA7_Input
                    _pas17 = 0; _pas16 = 0; _pac7 = 1; _papu7 = 0;

            #elif   PA7_Input_PU
                    _pas17 = 0; _pas16 = 0; _pac7 = 1; _papu7 = 1;

            #elif   PA7_PTP0I
                    _ptp0ips = 1; _pas17 = 0; _pas16 = 0;

            #endif

            #ifdef  PA7_WU
                    _pawu7 = 1;
            #endif

            #ifdef  PA7_PU
                    _papu7 = 1;
            #endif

        #endif

    #endif

/*===================== The end of Select PA7 function =======================*/

/*=========================== Select PB0 function ============================*/
    #ifdef  PB0_Outout_H
            _pbs01 = 0; _pbs00 = 0; _pbc0 = 0; _pb0 = 1;

    #elif   PB0_Outout_L
            _pbs01 = 0; _pbs00 = 0; _pbc0 = 0; _pb0 = 0;

    #elif   PB0_Input
            _pbs01 = 0; _pbs00 = 0; _pbc0 = 1; _pbpu0 = 0;

    #elif   PB0_Input_PU
            _pbs01 = 0; _pbs00 = 0; _pbc0 = 1; _pbpu0 = 1;

    #elif   PB0_AN0
            _pbs01 = 1; _pbs00 = 0;

    #elif   PB0_VREF
            _pbs01 = 1; _pbs00 = 1;

    #endif

    #ifdef  PB0_PU
            _pbpu0 = 1;
    #endif

/*===================== The end of Select PB0 function =======================*/

/*=========================== Select PB1 function ============================*/
    #ifdef  PB1_Outout_H
            _pbs03 = 0; _pbs02 = 0; _pbc1 = 0; _pb1 = 1;

    #elif   PB1_Outout_L
            _pbs03 = 0; _pbs02 = 0; _pbc1 = 0; _pb1 = 0;

    #elif   PB1_Input
            _pbs03 = 0; _pbs02 = 0; _pbc1 = 1; _pbpu1 = 0;

    #elif   PB1_Input_PU
            _pbs03 = 0; _pbs02 = 0; _pbc1 = 1; _pbpu1 = 1;

    #elif   PB1_STCK
            _stckps = 1; _pbs03 = 0; _pbs02 = 0; _pbc1 = 1;

    #elif   PB1_AN1
            _pbs03 = 1; _pbs02 = 1;

    #endif

    #ifdef  PB1_PU
            _pbpu1 = 1;
    #endif

/*===================== The end of Select PB1 function =======================*/

/*=========================== Select PB2 function ============================*/
    #ifdef  PB2_Outout_H
            _pbs05 = 0; _pbs04 = 0; _pbc2 = 0; _pb2 = 1;

    #elif   PB2_Outout_L
            _pbs05 = 0; _pbs04 = 0; _pbc2 = 0; _pb2 = 0;

    #elif   PB2_Input
            _pbs05 = 0; _pbs04 = 0; _pbc2 = 1; _pbpu2 = 0;

    #elif   PB2_Input_PU
            _pbs05 = 0; _pbs04 = 0; _pbc2 = 1; _pbpu2 = 1;

    #elif   PB2_PTCK0
            _ptck0ps = 1; _pbs05 = 0; _pbs04 = 0; _pbc2 = 1;

    #elif   PB2_AN2
            _pbs05 = 1; _pbs04 = 1;

    #endif

    #ifdef  PB2_PU
            _pbpu2 = 1;
    #endif

/*===================== The end of Select PB2 function =======================*/

/*=========================== Select PB3 function ============================*/
    #ifdef  PB3_Outout_H
            _pbs07 = 0; _pbs06 = 0; _pbc3 = 0; _pb3 = 1;

    #elif   PB3_Outout_L
            _pbs07 = 0; _pbs06 = 0; _pbc3 = 0; _pb3 = 0;

    #elif   PB3_Input
            _pbs07 = 0; _pbs06 = 0; _pbc3 = 1; _pbpu3 = 0;

    #elif   PB3_Input_PU
            _pbs07 = 0; _pbs06 = 0; _pbc3 = 1; _pbpu3 = 1;

    #elif   PB3_PTCK1
            _ptck1ps = 1; _pbs07 = 0; _pbs06 = 0; _pbc3 = 1;

    #elif   PB3_AN3
            _pbs07 = 1; _pbs06 = 1;

    #endif

    #ifdef  PB3_PU
            _pbpu3 = 1;
    #endif

/*===================== The end of Select PB3 function =======================*/

/*=========================== Select PB4 function ============================*/
    #ifdef  PB4_Outout_H
            _pbs11 = 0; _pbs10 = 0; _pbc4 = 0; _pb4 = 1;

    #elif   PB4_Outout_L
            _pbs11 = 0; _pbs10 = 0; _pbc4 = 0; _pb4 = 0;

    #elif   PB4_Input
            _pbs11 = 0; _pbs10 = 0; _pbc4 = 1; _pbpu4 = 0;

    #elif   PB4_Input_PU
            _pbs11 = 0; _pbs10 = 0; _pbc4 = 1; _pbpu4 = 1;

    #elif   PB4_INT0
            _int0ps = 1; _pbs11 = 0; _pbs10 = 0; _pbc4 = 1;

    #elif   PB4_PTP0B
            _pbs11 = 1; _pbs10 = 0;

    #elif   PB4_AN4
            _pbs11 = 1; _pbs10 = 1;

    #endif

    #ifdef  PB4_PU
            _pbpu4 = 1;
    #endif

/*===================== The end of Select PB4 function =======================*/

/*=========================== Select PB5 function ============================*/
    #ifdef  PB5_Outout_H
            _pbs13 = 0; _pbs12 = 0; _pbc5 = 0; _pb5 = 1;

    #elif   PB5_Outout_L
            _pbs13 = 0; _pbs12 = 0; _pbc5 = 0; _pb5 = 0;

    #elif   PB5_Input
            _pbs13 = 0; _pbs12 = 0; _pbc5 = 1; _pbpu5 = 0;

    #elif   PB5_Input_PU
            _pbs13 = 0; _pbs12 = 0; _pbc5 = 1; _pbpu5 = 1;

    #elif   PB5_INT1
            _int1ps = 1; _pbs13 = 0; _pbs12 = 0; _pbc5 = 1;

    #elif   PB5_STPB
            _pbs13 = 1; _pbs12 = 0;

    #elif   PB5_AN5
            _pbs13 = 1; _pbs12 = 1;

    #endif

    #ifdef  PB5_PU
            _pbpu5 = 1;
    #endif

/*===================== The end of Select PB5 function =======================*/

/*=========================== Select PB6 function ============================*/
    #ifdef  PB6_Outout_H
            _pbs15 = 0; _pbs14 = 0; _pbc6 = 0; _pb6 = 1;

    #elif   PB6_Outout_L
            _pbs15 = 0; _pbs14 = 0; _pbc6 = 0; _pb6 = 0;

    #elif   PB6_Input
            _pbs15 = 0; _pbs14 = 0; _pbc6 = 1; _pbpu6 = 0;

    #elif   PB6_Input_PU
            _pbs15 = 0; _pbs14 = 0; _pbc6 = 1; _pbpu6 = 1;

    #elif   PB6_STPI
            _stpips = 0; _pbs15 = 0; _pbs14 = 0; _pbc6 = 1;

    #elif   PB6_AN6
            _pbs15 = 1; _pbs14 = 1;

    #endif

    #ifdef  PB6_PU
            _pbpu6 = 1;
    #endif

/*===================== The end of Select PB6 function =======================*/

/*=========================== Select PB7 function ============================*/
    #ifdef  PB7_Outout_H
            _rstc = 0b01010101; _pbs17 = 0; _pbs16 = 0; _pbc7 = 0; _pb7 = 1;

    #elif   PB7_Outout_L
            _rstc = 0b01010101; _pbs17 = 0; _pbs16 = 0; _pbc7 = 0; _pb7 = 0;

    #elif   PB7_Input
            _rstc = 0b01010101; _pbs17 = 0; _pbs16 = 0; _pbc7 = 1; _pbpu7 = 0;

    #elif   PB7_Input_PU
            _rstc = 0b01010101; _pbs17 = 0; _pbs16 = 0; _pbc7 = 1; _pbpu7 = 1;

    #elif   PB7_RESB
            _pbs17 = 0; _pbs16 = 0; _rstc = 0b10101010;

    #elif   PB7_AN7
            _rstc = 0b01010101; _pbs17 = 1; _pbs16 = 1;

    #endif

    #ifdef  PB7_PU
            _rstc = 0b01010101; _pbpu7 = 1;
    #endif

/*===================== The end of Select PB7 function =======================*/

/*=========================== Select PC0 function ============================*/
    #ifdef  PC0_Outout_H
            _pcs01 = 0; _pcs00 = 0; _pcc0 = 0; _pc0 = 1;

    #elif   PC0_Outout_L
            _pcs01 = 0; _pcs00 = 0; _pcc0 = 0; _pc0 = 0;

    #elif   PC0_Input
            _pcs01 = 0; _pcs00 = 0; _pcc0 = 1; _pcpu0 = 0;

    #elif   PC0_Input_PU
            _pcs01 = 0; _pcs00 = 0; _pcc0 = 1; _pcpu0 = 1;

    #elif   PC0_STPI
            _stpips = 1; _pcs01 = 0; _pcs00 = 0; _pcc0 = 1;

    #elif   PC0_SCSB
            _pcs01 = 1; _pcs00 = 1;

    #endif

    #ifdef  PC0_PU
            _pcpu0 = 1;
    #endif

/*===================== The end of Select PC0 function =======================*/

/*=========================== Select PC1 function ============================*/
    #ifdef  PC1_Outout_H
            _pcs03 = 0; _pcs02 = 0; _pcc1 = 0; _pc1 = 1;

    #elif   PC1_Outout_L
            _pcs03 = 0; _pcs02 = 0; _pcc1 = 0; _pc1 = 0;

    #elif   PC1_Input
            _pcs03 = 0; _pcs02 = 0; _pcc1 = 1; _pcpu1 = 0;

    #elif   PC1_Input_PU
            _pcs03 = 0; _pcs02 = 0; _pcc1 = 1; _pcpu1 = 1;

    #elif   PC1_SDI
            _pcs03 = 1; _pcs02 = 1;

    #elif   PC1_SDA
            _pcs03 = 1; _pcs02 = 1;

    #elif   PC1_URX_UTX
            _pcs03 = 1; _pcs02 = 1;

    #endif

    #ifdef  PC1_PU
            _pcpu1 = 1;
    #endif

/*===================== The end of Select PC1 function =======================*/

/*=========================== Select PC2 function ============================*/
    #ifdef  PC2_Outout_H
            _pcs05 = 0; _pcs04 = 0; _pcc2 = 0; _pc2 = 1;

    #elif   PC2_Outout_L
            _pcs05 = 0; _pcs04 = 0; _pcc2 = 0; _pc2 = 0;

    #elif   PC2_Input
            _pcs05 = 0; _pcs04 = 0; _pcc2 = 1; _pcpu2 = 0;

    #elif   PC2_Input_PU
            _pcs05 = 0; _pcs04 = 0; _pcc2 = 1; _pcpu2 = 1;

    #elif   PC2_SDO
            _pcs05 = 1; _pcs04 = 1;

    #elif   PC2_UTX
            _pcs05 = 1; _pcs04 = 1;

    #endif

    #ifdef  PC2_PU
            _pcpu2 = 1;
    #endif

/*===================== The end of Select PC2 function =======================*/

/*=========================== Select PC3 function ============================*/
    #ifdef  PC3_Outout_H
            _pcs07 = 0; _pcs06 = 0; _pcc3 = 0; _pc3 = 1;

    #elif   PC3_Outout_L
            _pcs07 = 0; _pcs06 = 0; _pcc3 = 0; _pc3 = 0;

    #elif   PC3_Input
            _pcs07 = 0; _pcs06 = 0; _pcc3 = 1; _pcpu3 = 0;

    #elif   PC3_Input_PU
            _pcs07 = 0; _pcs06 = 0; _pcc3 = 1; _pcpu3 = 1;

    #elif   PC3_SCK
            _pcs07 = 1; _pcs06 = 1;

    #elif   PC3_SCL
            _pcs07 = 1; _pcs06 = 1;

    #endif

    #ifdef  PC3_PU
            _pcpu3 = 1;
    #endif

/*===================== The end of Select PC3 function =======================*/

/*=========================== Select PC4 function ============================*/
    #ifndef FSUB_LXT_SU_EN

        #ifndef FSUB_LXT_SU_DIS 

            #ifdef  PC4_Outout_H
                    _pcs11 = 0; _pcs10 = 0; _pcc4 = 0; _pc4 = 1;

            #elif   PC4_Outout_L
                    _pcs11 = 0; _pcs10 = 0; _pcc4 = 0; _pc4 = 0;

            #elif   PC4_Input
                    _pcs11 = 0; _pcs10 = 0; _pcc4 = 1; _pcpu4 = 0;

            #elif   PC4_Input_PU
                    _pcs11 = 0; _pcs10 = 0; _pcc4 = 1; _pcpu4 = 1;

            #endif

            #ifdef  PC4_PU
                    _pcpu4 = 1;
            #endif

        #endif

    #endif

/*===================== The end of Select PC4 function =======================*/

/*=========================== Select PC5 function ============================*/
    #ifndef FSUB_LXT_SU_EN

        #ifndef FSUB_LXT_SU_DIS 

            #ifdef  PC5_Outout_H
                    _pcs13 = 0; _pcs12 = 0; _pcc5 = 0; _pc5 = 1;

            #elif   PC5_Outout_L
                    _pcs13 = 0; _pcs12 = 0; _pcc5 = 0; _pc5 = 0;

            #elif   PC5_Input
                    _pcs13 = 0; _pcs12 = 0; _pcc5 = 1; _pcpu5 = 0;

            #elif   PC5_Input_PU
                    _pcs13 = 0; _pcs12 = 0; _pcc5 = 1; _pcpu5 = 1;

            #endif

            #ifdef  PC5_PU
                    _pcpu5 = 1;
            #endif

        #endif

    #endif

/*===================== The end of Select PC5 function =======================*/

/*=========================== Select PC6 function ============================*/
    #ifdef  PC6_Outout_H
            _pcc6 = 0; _pc6 = 1;

    #elif   PC6_Outout_L
            _pcc6 = 0; _pc6 = 0;

    #elif   PC6_Input
            _pcc6 = 1; _pcpu6 = 0;

    #elif   PC6_Input_PU
            _pcc6 = 1; _pcpu6 = 1;

    #elif   PC6_PTP1I
            _ptp1ips = 0;
    #endif

    #ifdef  PC6_PU
            _pcpu6 = 1;
    #endif

/*===================== The end of Select PC6 function =======================*/

/*=========================== Select PC7 function ============================*/
    #ifdef  PC7_Outout_H
            _pcc7 = 0; _pc7 = 1;

    #elif   PC7_Outout_L
            _pcc7 = 0; _pc7 = 0;

    #elif   PC7_Input
            _pcc7 = 1; _pcpu7 = 0;

    #elif   PC7_Input_PU
            _pcc7 = 1; _pcpu7 = 1;

    #endif

    #ifdef  PC7_PU
            _pcpu7 = 1;
    #endif

/*===================== The end of Select PC7 function =======================*/

/*=========================== Select PD0 function ============================*/
    #ifdef  PD0_Outout_H
            _pds01 = 0; _pds00 = 0; _pdc0 = 0; _pd0 = 1;

    #elif   PD0_Outout_L
            _pds01 = 0; _pds00 = 0; _pdc0 = 0; _pd0 = 0;

    #elif   PD0_Input
            _pds01 = 0; _pds00 = 0; _pdc0 = 1; _pdpu0 = 0;

    #elif   PD0_Input_PU
            _pds01 = 0; _pds00 = 0; _pdc0 = 1; _pdpu0 = 1;

    #elif   PD0_PTCK1
            _ptck1ps = 0; _pds01 = 0; _pds00 = 0; _pdc0 = 1;

    #elif   PD0_SCOM0
            _pds01 = 1; _pds00 = 1;

    #endif

    #ifdef  PD0_PU
            _pdpu0 = 1;
    #endif

/*===================== The end of Select PD0 function =======================*/

/*=========================== Select PD1 function ============================*/
    #ifdef  PD1_Outout_H
            _pds03 = 0; _pds02 = 0; _pdc1 = 0; _pd1 = 1;

    #elif   PD1_Outout_L
            _pds03 = 0; _pds02 = 0; _pdc1 = 0; _pd1 = 0;

    #elif   PD1_Input
            _pds03 = 0; _pds02 = 0; _pdc1 = 1; _pdpu1 = 0;

    #elif   PD1_Input_PU
            _pds03 = 0; _pds02 = 0; _pdc1 = 1; _pdpu1 = 1;

    #elif   PD1_PTP1I
            _ptp1ips = 1; _pds03 = 0; _pds02 = 0;

    #elif   PD1_SCOM1
            _pds03 = 1; _pds02 = 1;

    #endif

    #ifdef  PD1_PU
            _pdpu1 = 1;
    #endif

/*===================== The end of Select PD1 function =======================*/

/*=========================== Select PD2 function ============================*/
    #ifdef  PD2_Outout_H
            _pds05 = 0; _pds04 = 0; _pdc2 = 0; _pd2 = 1;

    #elif   PD2_Outout_L
            _pds05 = 0; _pds04 = 0; _pdc2 = 0; _pd2 = 0;

    #elif   PD2_Input
            _pds05 = 0; _pds04 = 0; _pdc2 = 1; _pdpu2 = 0;

    #elif   PD2_Input_PU
            _pds05 = 0; _pds04 = 0; _pdc2 = 1; _pdpu2 = 1;

    #elif   PD2_PTP1
            _pds05 = 1; _pds04 = 0;

    #elif   PD2_SCOM2
            _pds05 = 1; _pds04 = 1;

    #endif

    #ifdef  PD2_PU
            _pdpu2 = 1;
    #endif

/*===================== The end of Select PD2 function =======================*/

/*=========================== Select PD3 function ============================*/
    #ifdef  PD3_Outout_H
            _pds07 = 0; _pds06 = 0; _pdc3 = 0; _pd3 = 1;

    #elif   PD3_Outout_L
            _pds07 = 0; _pds06 = 0; _pdc3 = 0; _pd3 = 0;

    #elif   PD3_Input
            _pds07 = 0; _pds06 = 0; _pdc3 = 1; _pdpu3 = 0;

    #elif   PD3_Input_PU
            _pds07 = 0; _pds06 = 0; _pdc3 = 1; _pdpu3 = 1;

    #elif   PD3_PTP1B
            _pds07 = 1; _pds06 = 0;

    #elif   PD3_SCOM3
            _pds07 = 1; _pds06 = 1;

    #endif

    #ifdef  PD3_PU
            _pdpu3 = 1;
    #endif

/*===================== The end of Select PD3 function =======================*/

/*=========================== Select PD4 function ============================*/
    #ifdef  PD4_Outout_H
            _pdc4 = 0; _pd4 = 1;

    #elif   PD4_Outout_L
            _pdc4 = 0; _pd4 = 0;

    #elif   PD4_Input
            _pdc4 = 1; _pdpu4 = 0;

    #elif   PD4_Input_PU
            _pdc4 = 1; _pdpu4 = 1;

    #endif

    #ifdef  PD4_PU
            _pdpu4 = 1;
    #endif

/*===================== The end of Select PD4 function =======================*/

/*=========================== Select PD5 function ============================*/
    #ifdef  PD5_Outout_H
            _pdc5 = 0; _pd5 = 1;

    #elif   PD5_Outout_L
            _pdc5 = 0; _pd5 = 0;

    #elif   PD5_Input
            _pdc5 = 1; _pdpu5 = 0;

    #elif   PD5_Input_PU
            _pdc5 = 1; _pdpu5 = 1;

    #endif

    #ifdef  PD5_PU
            _pdpu5 = 1;
    #endif

/*===================== The end of Select PD5 function =======================*/

/*===================== Select PA3~PA0 source current ========================*/
    #ifdef  PA3_PA0_Level_0
            _sledc01 = 0; _sledc00 = 0;

    #elif   PA3_PA0_Level_1
            _sledc01 = 0; _sledc00 = 1;

    #elif   PA3_PA0_Level_2
            _sledc01 = 1; _sledc00 = 0;

    #elif   PA3_PA0_Level_3
            _sledc01 = 1; _sledc00 = 1;

    #endif

/*================ The end of Select PA3~PA0 source current ==================*/

/*===================== Select PA7~PA4 source current ========================*/
    #ifdef  PA7_PA4_Level_0
            _sledc03 = 0; _sledc02 = 0;

    #elif   PA7_PA4_Level_1
            _sledc03 = 0; _sledc02 = 1;

    #elif   PA7_PA4_Level_2
            _sledc03 = 1; _sledc02 = 0;

    #elif   PA7_PA4_Level_3
            _sledc03 = 1; _sledc02 = 1;

    #endif

/*================ The end of Select PA7~PA4 source current ==================*/

/*===================== Select PB3~PB0 source current ========================*/
    #ifdef  PB3_PB0_Level_0
            _sledc05 = 0; _sledc04 = 0;

    #elif   PB3_PB0_Level_1
            _sledc05 = 0; _sledc04 = 1;

    #elif   PB3_PB0_Level_2
            _sledc05 = 1; _sledc04 = 0;

    #elif   PB3_PB0_Level_3
            _sledc05 = 1; _sledc04 = 1;

    #endif

/*================ The end of Select PB3~PB0 source current ==================*/

/*===================== Select PB7~PB4 source current ========================*/
    #ifdef  PB7_PB4_Level_0
            _sledc07 = 0; _sledc06 = 0;

    #elif   PB7_PB4_Level_1
            _sledc07 = 0; _sledc06 = 1;

    #elif   PB7_PB4_Level_2
            _sledc07 = 1; _sledc06 = 0;

    #elif   PB7_PB4_Level_3
            _sledc07 = 1; _sledc06 = 1;

    #endif

/*================ The end of Select PB7~PB4 source current ==================*/

/*===================== Select PC3~PC0 source current ========================*/
    #ifdef  PC3_PC0_Level_0
            _sledc11 = 0; _sledc10 = 0;

    #elif   PC3_PC0_Level_1
            _sledc11 = 0; _sledc10 = 1;

    #elif   PC3_PC0_Level_2
            _sledc11 = 1; _sledc10 = 0;

    #elif   PC3_PC0_Level_3
            _sledc11 = 1; _sledc10 = 1;

    #endif

/*================ The end of Select PC3~PC0 source current ==================*/

/*===================== Select PC7~PC4 source current ========================*/
    #ifdef  PC7_PC4_Level_0
            _sledc13 = 0; _sledc12 = 0;

    #elif   PC7_PC4_Level_1
            _sledc13 = 0; _sledc12 = 1;

    #elif   PC7_PC4_Level_2
            _sledc13 = 1; _sledc12 = 0;

    #elif   PC7_PC4_Level_3
            _sledc13 = 1; _sledc12 = 1;

    #endif

/*================ The end of Select PC7~PC4 source current ==================*/

/*===================== Select PD3~PD0 source current ========================*/
    #ifdef  PD3_PD0_Level_0
            _sledc15 = 0; _sledc14 = 0;

    #elif   PD3_PD0_Level_1
            _sledc15 = 0; _sledc14 = 1;

    #elif   PD3_PD0_Level_2
            _sledc15 = 1; _sledc14 = 0;

    #elif   PD3_PD0_Level_3
            _sledc15 = 1; _sledc14 = 1;

    #endif

/*================ The end of Select PD3~PD0 source current ==================*/

/*===================== Select PD5~PD4 source current ========================*/
    #ifdef  PD5_PD4_Level_0
            _sledc17 = 0; _sledc16 = 0;

    #elif   PD5_PD4_Level_1
            _sledc17 = 0; _sledc16 = 1;

    #elif   PD5_PD4_Level_2
            _sledc17 = 1; _sledc16 = 0;

    #elif   PD5_PD4_Level_3
            _sledc17 = 1; _sledc16 = 1;

    #endif

/*================ The end of Select PD5~PD4 source current ==================*/

}
/************************ (C) COPYRIGHT 2019 Holtek Semiconductor Inc ************************END OF FILE****/
