/*******************************************************************************
  * @file     HT8_SW_SPI_Master.h
  * @brief    The header file of the S/W SPI Master library.
  * @author   Holtek Semiconductor Inc.
  * @version  V1.0.0
  * @date     2023-8-16
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
#ifndef _HT8_SW_SPI_Master_H_
#define _HT8_SW_SPI_Master_H_

/* Includes-------------------------------------------------------------------*/
#include "HT8_MCU_IP_SEL.h"

/* Exported constants---------------------------------------------------------*/

/*=============== Select S/W SPI SCK clock active edge type ==================*/
/* S/W SPI SCK is high base level and data capture at SCK rising edge */
//  #define SW_SPI_SCK_HIGH_RISING_EDGE     (1)

/* S/W SPI SCK is high base level and data capture at SCK falling edge */
//  #define SW_SPI_SCK_HIGH_FALLING_EDGE    (1)

/* S/W SPI SCK is low base level and data capture at SCK falling edge */
//  #define SW_SPI_SCK_LOW_FALLING_EDGE     (1)

/* S/W SPI SCK is low base level and data capture at SCK rising edge */
    #define SW_SPI_SCK_LOW_RISING_EDGE      (1)
/*========== The end of Select S/W SPI SCK clock active edge type ============*/

/*===================== Select SW SPI data shift order =======================*/
//  #define SW_SPI_LSB_FIRST        (1)     /*LSB first*/
    #define SW_SPI_MSB_FIRST        (1)     /*MSB first*/
/*=============== The end of Select SW SPI data shift order ==================*/

//  #define SCSB    _pb0
//  #define SCSB_C  _pbc0

//  #define SCK     _pb1
//  #define SCK_C   _pbc1

//  #define SDO     _pb2
//  #define SDO_C   _pbc2

//  #define SDI     _pb3
//  #define SDI_C   _pbc3

//  #define FSYS    8000000
//  #define FSCK    100000
//  #define DIV_COEFF       100

	#define SCSB     _pc0
	#define SCSB_C   _pcc0
	#define SCK     _pc3
	#define SCK_C   _pcc3
	#define SDO     _pc2
	#define SDO_C   _pcc2
	#define SDI     _pb7
	#define SDI_C   _pbc7
	#define FSYS    8000000
	#define FSCK    50000
    #define SW_SCSB_ENABLE()       (SCSB = 0)
    #define SW_SCSB_DISABLE()      (SCSB = 1)


#if (FSYS == 2000000)

    #define t_DELAY             20

    #if (FSCK == 25000)

            #define t_HD1       0
            #define t_SU1       5

            #define t_HD2       3
            #define t_SU2       1

    #elif   (FSCK == 10000)

            #define t_HD1       13
            #define t_SU1       21

            #define t_HD2       19
            #define t_SU2       15

    #endif

#elif   (FSYS == 4000000)

        #define t_DELAY             40

        #if (FSCK == 50000)

                #define t_HD1       0
                #define t_SU1       4

                #define t_HD2       3
                #define t_SU2       0

        #elif   (FSCK == 25000)

                #define t_HD1       9
                #define t_SU1       15

                #define t_HD2       14
                #define t_SU2       10

        #elif   (FSCK == 10000)

                #define t_HD1       39
                #define t_SU1       46

                #define t_HD2       45
                #define t_SU2       39

        #endif

#elif   (FSYS == 8000000)

        #define t_DELAY             80

        #if (FSCK == 100000)

                #define t_HD1       0
                #define t_SU1       5

                #define t_HD2       3
                #define t_SU2       1

        #elif   (FSCK == 50000)

                #define t_HD1       9
                #define t_SU1       15

                #define t_HD2       13
                #define t_SU2       10

        #elif   (FSCK == 25000)

                #define t_HD1       29
                #define t_SU1       35

                #define t_HD2       34
                #define t_SU2       29

        #elif   (FSCK == 10000)

                #define t_HD1       85
                #define t_SU1       100

                #define t_HD2       96
                #define t_SU2       89

        #endif

#elif   (FSYS == 12000000)

        #define t_DELAY             100

        #if (FSCK == 100000)

                #define t_HD1       4
                #define t_SU1       10

                #define t_HD2       8
                #define t_SU2       6

        #elif   (FSCK == 50000)

                #define t_HD1       20
                #define t_SU1       24

                #define t_HD2       24
                #define t_SU2       20

        #elif   (FSCK == 25000)

                #define t_HD1       50
                #define t_SU1       54

                #define t_HD2       54
                #define t_SU2       50

        #elif   (FSCK == 10000)

                #define t_HD1       135
                #define t_SU1       149

                #define t_HD2       149
                #define t_SU2       135

        #endif

#elif   (FSYS == 16000000)

        #define t_DELAY             120

        #if (FSCK == 200000)

                #define t_HD1       0
                #define t_SU1       4

                #define t_HD2       3
                #define t_SU2       1

        #elif   (FSCK == 100000)

                #define t_HD1       9
                #define t_SU1       16

                #define t_HD2       13
                #define t_SU2       10

        #elif   (FSCK == 50000)

                #define t_HD1       30
                #define t_SU1       34

                #define t_HD2       34
                #define t_SU2       29

        #elif   (FSCK == 25000)

                #define t_HD1       69
                #define t_SU1       75

                #define t_HD2       75
                #define t_SU2       69

        #elif   (FSCK == 10000)

                #define t_HD1       185
                #define t_SU1       200

                #define t_HD2       200
                #define t_SU2       185

        #endif

#elif   ((FSYS != 2000000) && (FSYS != 4000000) && (FSYS != 8000000)&& (FSYS != 12000000)&& (FSYS != 16000000))

        #define t_DELAY             10

        #if (DIV_COEFF == 100)

                #define t_HD1       1
                #define t_SU1       8

                #define t_HD2       6
                #define t_SU2       3

        #elif   (DIV_COEFF == 200)

                #define t_HD1       14
                #define t_SU1       20

                #define t_HD2       19
                #define t_SU2       15

        #endif

#endif


/* Exported functions---------------------------------------------------------*/
void SW_SPI_Master_Init(void);
u8 SW_SPI_Master_Send_Data(u8 TX_Data);

#endif

/*********** (C) COPYRIGHT 2019 Holtek Semiconductor Inc **********END OF FILE*/
