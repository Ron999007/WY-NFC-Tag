/*******************************************************************************
  * @file     HT8_SW_I2C_Master.h
  * @brief    The header file of the S/W I2C Master library.
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
#ifndef _HT8_SW_I2C_Master_H_
#define _HT8_SW_I2C_Master_H_

/* Includes-------------------------------------------------------------------*/
#include "HT8_MCU_IP_SEL.h"

/* Exported constants---------------------------------------------------------*/
/* Bits 7~ 1 of the SLAVE_ADDRESS define the device slave address */
//  #define SLAVE_ADDRESS   0x2a

//  #define SCL     _pb0
//  #define SCL_C   _pbc0
//  #define SCL_PU  _pbpu0

//  #define SDA     _pb1
//  #define SDA_C   _pbc1
//  #define SDA_PU  _pbpu1

//  #define FSYS    8000000
//  #define FSCL    50000
//  #define DIV_COEFF       100

#define TIMEOUT     20/*Bus timeout*/
#define CHECKCNT    2

#define SLAVE_ADDRESS   0XAA            //SLAVE_ADDRESS range is 0x00 ~ 0xFF

#define SCL             _pb4
#define SCL_C           _pbc4
#define SCL_PU          _pbpu4

#define SDA             _pb2
#define SDA_C           _pbc2
#define SDA_PU          _pbpu2

#define FSYS            8000000
#define FSCL            90000

#define t_LOW       1
#define t_HIGH      1

    #define Internal_PU     (1)
//  #define External_PU     (1)


#if (FSYS == 8000000)

    #define t_HD_STA        10
    #define t_SU_STA        10
    #define t_SU_STO        10
    #define t_BUF           4

    #if (FSCL == 90000)
            #define P_RATIO     0
            #define OFFSET1     0
            #define OFFSET2     0
            #define t_HIGH1     4
            #define t_HIGH2     4
            #define t_LOW1      4
            #define t_LOW2      4
            #define t_LOW3      0

    #elif   (FSCL == 50000)
            #define P_RATIO     1
            #define OFFSET1     (-1)
            #define OFFSET2     (-1)
            #define t_HIGH1     7
            #define t_HIGH2     9
            #define t_LOW1      9
            #define t_LOW2      9
            #define t_LOW3      8

    #elif   (FSCL == 25000)
            #define P_RATIO     3
            #define OFFSET1     (-3)
            #define OFFSET2     (-3)
            #define t_HIGH1     ((2 + t_HIGH) * P_RATIO + OFFSET1 + 1)
            #define t_HIGH2     ((10 + t_HIGH) * P_RATIO + OFFSET1)
            #define t_LOW1      ((2 + t_LOW) * P_RATIO + OFFSET2 + 1)
            #define t_LOW2      ((10 + t_LOW) * P_RATIO + OFFSET2)
            #define t_LOW3      27

    #elif   (FSCL == 10000)
            #define P_RATIO     8
            #define OFFSET1     2
            #define OFFSET2     2
            #define t_HIGH1     ((2 + t_HIGH) * P_RATIO + OFFSET1 - 19)
            #define t_HIGH2     ((10 + t_HIGH) * P_RATIO + OFFSET1)
            #define t_LOW1      ((2 + t_LOW) * P_RATIO + OFFSET2 - 19)
            #define t_LOW2      ((10 + t_LOW) * P_RATIO + OFFSET2)
            #define t_LOW3      87

    #endif

#elif   (FSYS == 12000000)

        #define t_HD_STA        15
        #define t_SU_STA        15
        #define t_SU_STO        15
        #define t_BUF           14

        #if (FSCL == 100000)
                #define P_RATIO     1
                #define OFFSET1     (-6)
                #define OFFSET2      (-6)
                #define t_HIGH1     ((12 + t_HIGH) * P_RATIO + OFFSET1)
                #define t_HIGH2     ((10 + t_HIGH) * P_RATIO + OFFSET1)
                #define t_LOW1      ((12 + t_LOW) * P_RATIO + OFFSET2)
                #define t_LOW2      ((10 + t_LOW) * P_RATIO + OFFSET2)
                #define t_LOW3      2

        #elif   (FSCL == 50000)
                #define P_RATIO     2
                #define OFFSET1      (-2)
                #define OFFSET2     (-2)
                #define t_HIGH1     ((3 + t_HIGH) * P_RATIO + OFFSET1)
                #define t_HIGH2     ((10 + t_HIGH) * P_RATIO + OFFSET1)
                #define t_LOW1      ((4 + t_LOW) * P_RATIO + OFFSET2)
                #define t_LOW2      ((10 + t_LOW) * P_RATIO + OFFSET2)
                #define t_LOW3      18

        #elif   (FSCL == 25000)
                #define P_RATIO     5
                #define OFFSET1      (-5)
                #define OFFSET2      (-5)
                #define t_HIGH1     ((t_HIGH) * P_RATIO + OFFSET1 + 7)
                #define t_HIGH2     ((10 + t_HIGH) * P_RATIO + OFFSET1)
                #define t_LOW1      ((t_LOW) * P_RATIO + OFFSET2 + 7) 
                #define t_LOW2      ((10 + t_LOW) * P_RATIO + OFFSET2)
                #define t_LOW3      47

        #elif   (FSCL == 10000)
                #define P_RATIO     13
                #define OFFSET1      (-3)
                #define OFFSET2      (-3)
                #define t_HIGH1     ((t_HIGH) * P_RATIO + OFFSET1 - 3)
                #define t_HIGH2     ((10 + t_HIGH) * P_RATIO + OFFSET1)
                #define t_LOW1      ((t_LOW) * P_RATIO + OFFSET2 - 3)
                #define t_LOW2      ((10 + t_LOW) * P_RATIO + OFFSET2)
                #define t_LOW3      137

        #endif

#elif   (FSYS == 16000000)

        #define t_HD_STA        20
        #define t_SU_STA        20
        #define t_SU_STO        20
        #define t_BUF           25

        #if (FSCL == 100000)
                #define P_RATIO     1
                #define OFFSET1     (-1)
                #define OFFSET2      (-1)
                #define t_HIGH1     ((7 + t_HIGH) * P_RATIO + OFFSET1)
                #define t_HIGH2     ((10 + t_HIGH) * P_RATIO + OFFSET1)
                #define t_LOW1      ((7 + t_LOW) * P_RATIO + OFFSET2)
                #define t_LOW2      ((10 + t_LOW) * P_RATIO + OFFSET2)
                #define t_LOW3      7

        #elif   (FSCL == 50000)
                #define P_RATIO     3
                #define OFFSET1      (-3)
                #define OFFSET2     (-3)
                #define t_HIGH1     ((3 + t_HIGH) * P_RATIO + OFFSET1)
                #define t_HIGH2     ((10 + t_HIGH) * P_RATIO + OFFSET1)
                #define t_LOW1      ((2 + t_LOW) * P_RATIO + OFFSET2)
                #define t_LOW2      ((10 + t_LOW) * P_RATIO + OFFSET2)
                #define t_LOW3      25

        #elif   (FSCL == 25000)
                #define P_RATIO     6
                #define OFFSET1     4
                #define OFFSET2     4
                #define t_HIGH1     ((2 + t_HIGH) * P_RATIO + OFFSET1 - 15)
                #define t_HIGH2     ((10 + t_HIGH) * P_RATIO + OFFSET1)
                #define t_LOW1      ((2 + t_LOW) * P_RATIO + OFFSET2 - 15)
                #define t_LOW2      ((10 + t_LOW) * P_RATIO + OFFSET2)
                #define t_LOW3      64

        #elif   (FSCL == 10000)
                #define P_RATIO     17
                #define OFFSET1     3
                #define OFFSET2     3
                #define t_HIGH1     ((2 + t_HIGH) * P_RATIO + OFFSET1 - 47)
                #define t_HIGH2     ((10 + t_HIGH) * P_RATIO + OFFSET1)
                #define t_LOW1      ((2 + t_LOW) * P_RATIO + OFFSET2 - 47)
                #define t_LOW2      ((10 + t_LOW) * P_RATIO + OFFSET2)
                #define t_LOW3      187

#endif

#elif   ((FSYS != 8000000) && (FSYS != 12000000) && (FSYS != 16000000))
        #if (DIV_COEFF == 100)
                #define t_HD_STA    20
                #define t_SU_STA    20
                #define t_SU_STO    20
                #define t_BUF       25
                #define P_RATIO     1
                #define OFFSET1     -8
                #define OFFSET2     -9
                #define t_HIGH1     4
                #define t_HIGH2     5
                #define t_LOW1      5
                #define t_LOW2      5
                #define t_LOW3      0

        #elif   (DIV_COEFF == 200)
                #define t_HD_STA    20
                #define t_SU_STA    20
                #define t_SU_STO    20
                #define t_BUF       25
                #define P_RATIO     1
                #define OFFSET1     4
                #define OFFSET2     4
                #define t_HIGH1     11
                #define t_HIGH2     11
                #define t_LOW1      11
                #define t_LOW2      11
                #define t_LOW3      12

        #endif

#endif

#define t_LOW_OS    ((10+t_LOW) * P_RATIO+OFFSET1)
#define t_HIGH_OS   ((10+t_HIGH) * P_RATIO+OFFSET2)

#define SCL_HIGH()  (SCL_C = 1)
#define SCL_LOW()   {SCL_C = 0; SCL = 0;}

#define SDA_HIGH()  (SDA_C = 1)
#define SDA_LOW()   {SDA_C = 0; SDA = 0;}

typedef enum 
{
    RX_Mode = 0x01,
    TX_Mode = 0x00
}I2C_Slave_Mode_TypeDef;


/* Exported functions---------------------------------------------------------*/
void SW_I2C_Master_Init(void);
I2C_ACK_Flag SW_I2C_Send_Start(void);
I2C_ACK_Flag SW_I2C_Send_Stop(void);
I2C_ACK_Flag SW_I2C_Send_Data(u8 data);
I2C_ACK_Flag SW_I2C_Send_Addr(u8 slave_addr,u8 slave_mode);
u8 SW_I2C_Receive_Data(I2C_ACK_Flag tx_ack);

#endif

/*********** (C) COPYRIGHT 2019 Holtek Semiconductor Inc **********END OF FILE*/
