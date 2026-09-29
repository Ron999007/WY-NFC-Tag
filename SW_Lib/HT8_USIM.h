/*******************************************************************************
  * @file     HT8_USIM.h
  * @brief    The header file of the USIM library.
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
#ifndef _HT8_USIM_H_
#define _HT8_USIM_H_

/* Includes-------------------------------------------------------------------*/
#include "HT8_MCU_IP_SEL.h"

/* Exported constants---------------------------------------------------------*/
#define USIM_SIM_ENABLE()       (_simen = 1)    /*USIM SIM function enable*/
#define USIM_SIM_DISABLE()      (_simen = 0)    /*USIM SIM function disable*/
#define USIM_SPI_CS_ENABLE()    (_csen = 1)     /*USIM SPI SCSB function enable*/
#define USIM_SPI_CS_DISABLE()   (_csen = 0)     /*USIM SPI SCSB function disable*/
#define USIM_UART_ENABLE()      (_uren = 1)     /*USIM UART function enable*/
#define USIM_UART_DISABLE()     (_uren = 0)     /*USIM UART function disable*/

/* USIM UART transmitter enable */
#define USIM_UART_TX_ENABLE()       (_utxen = 1)
/* USIM UART transmitter disable */
#define USIM_UART_TX_DISABLE()      (_utxen = 0)

/* USIM UART receiver enable  */
#define USIM_UART_RX_ENABLE()       (_urxen = 1)
/* USIM UART receiver disable */
#define USIM_UART_RX_DISABLE()      (_urxen = 0)

#define USIM_ISR_ENABLE()       (_usime = 1)    /*USIM  interrupt enable*/
#define USIM_ISR_DISABLE()      (_usime = 0)    /*USIM  interrupt disable*/
#define USIM_SET_ISR_FLAG()     (_usimf = 1)    /*Set USIM interrupt flag*/
#define USIM_CLEAR_ISR_FLAG()   (_usimf = 0)    /*Clear USIM interrupt flag*/

/* USIM UART receiver interrupt enable */
#define USIM_UART_RIE_ENABLE()      (_urie = 1)
/* USIM UART receiver interrupt disable */
#define USIM_UART_RIE_DISABLE()     (_urie = 0)

/* USIM UART transmitter idle interrupt enable */
#define USIM_UART_TIIE_ENABLE()     (_utiie = 1)
/* USIM UART transmitter idle interrupt disable */
#define USIM_UART_TIIE_DISABLE()    (_utiie = 0)

/* USIM UART transmitter empty interrupt enable */
#define USIM_UART_TEIE_ENABLE()     (_uteie = 1)
/* USIM UART transmitter empty interrupt disable */
#define USIM_UART_TEIE_DISABLE()    (_uteie = 0)

/* USIM UART Address detect function enable */
#define USIM_UART_Addr_Det_ENABLE()     (_uadden = 1)
/* USIM UART Address detect function disable */
#define USIM_UART_Addr_Det_DISABLE()    (_uadden = 0)

/* URX pin wake-up USIM UART function enable  */
#define USIM_UART_RX_Wake_ENABLE()      (_uwake = 1)
/* URX pin wake-up USIM UART function disable */
#define USIM_UART_RX_Wake_DISABLE()     (_uwake = 0)

/* USIM UART Transmit break character function enable  */
#define USIM_UART_TXBRK_ENABLE()        (_utxbrk = 1)
/* USIM UART Transmit break character function disable */
#define USIM_UART_TXBRK_DISABLE()       (_utxbrk = 0)

/* Set USIM UART single wire transmit mode */
#define USIM_UART_SINGLE_WIRE_TX()      {_urxen = 0; _utxen = 1;}
/* Set USIM UART single wire receive mode */
#define USIM_UART_SINGLE_WIRE_RX()      {_urxen = 1; _utxen = 0;}

/* USIM UART Single Wire Mode enable */
#define USIM_UART_SWM_ENABLE()      (_uswm = 1)
/* USIM UART Single Wire Mode disable */
#define USIM_UART_SWM_DISABLE()     (_uswm = 0)


/*======================= Select USIMn operating mode ========================*/
//  #define USIM_I2C_Slave      (1)         /*Set USIM as I2C slave mode*/
    #define USIM_SPI_Master     (1)         /*Set USIM as SPI master mode*/
//  #define USIM_SPI_Slave      (1)         /*Set USIM as SPI slave mode*/
//  #define USIM_UART           (1)         /*Set USIM as UART mode*/

/*================= The end of Select USIMn operating mode ===================*/

/********************** USIMn I2C funtion configuration ***********************/

//  #define USIM_I2C_DEVICEADDR     0x72        /*USIM I2C Slave address*/


/* USIM I2C time-out function enable */
#define USIM_I2CTO_ENABLE()     (_simtoen = 1)
/* USIM I2C time-out function disable */
#define USIM_I2CTO_DISABLE()    (_simtoen = 0)


/*===================== Select USIMn I2C debounce time =======================*/
//  #define USIM_I2C_DEBOUNCE_DISABLE   (1)     /*USIM I2C no debounce*/
//  #define USIM_I2C_DEBOUNCE_2_FSYS    (1)     /*USIM I2C debounce 2 Fsys*/
//  #define USIM_I2C_DEBOUNCE_4_FSYS    (1)     /*USIM I2C debounce 4 Fsys*/

/*=============== The end of Select USIMn I2C debounce time ==================*/

/********************** USIMn SPI funtion configuration ***********************/

/* USIMn SPI write collision flag */
#define USIM_SPI_WRITE_COLLISION_FLAG       _wcol


/* USIMn SPI Transmit/Receive complete flag */
#define USIM_SPI_TRX_FLAG                   _trf


/*================= Select USIMn SPI master mode and clock ===================*/
/* USIM SPI master mode, SPI clock is fSYS /4 */
    #define USIM_SPI_Master_FSYS_DIV4       (1)
/* USIM SPI master mode, SPI clock is fSYS /16 */
//  #define USIM_SPI_Master_FSYS_DIV16      (1)
/* USIM SPI master mode, SPI clock is fSYS /64 */
//  #define USIM_SPI_Master_FSYS_DIV64      (1)
/* USIM SPI master mode, SPI clock is fSUB */
//  #define USIM_SPI_Master_FSUB            (1)
/* USIM SPI master mode, SPI clock is PTM0PINT/2 */
//  #define USIM_SPI_Master_FPTM0           (1)

/*=========== The end of Select USIMn SPI master mode and clock ==============*/

/*======================= USIMn SPI SCSB pin control =========================*/
//  #define USIM_SPI_CS_ON          (1)         /*USIM SPI SCSB pin enable*/
//  #define USIM_SPI_CS_OFF         (1)         /*USIM SPI SCSB pin disable*/
/*=================== The ed of USIM SPI SCSB pi cotrol ======================*/


/*=============== Select USIMn SPI SCK clock active edge type ================*/
/* USIM SCK is high base level and data capture at SCK rising edge */
//  #define USIM_SPI_SCK_HIGH_RISING_EDGE       (1)
/* USIM SCK is high base level and data capture at SCK falling edge */
//  #define USIM_SPI_SCK_HIGH_FALLING_EDGE      (1)
/* USIM SCK is low base level and data capture at SCK falling edge */
//  #define USIM_SPI_SCK_LOW_FALLING_EDGE       (1)
/* USIM SCK is low base level and data capture at SCK rising edge */
    #define USIM_SPI_SCK_LOW_RISING_EDGE        (1)

/*========= The end of Select USIMn SPI SCK clock active edge type ===========*/

/*=================== Select USIMn SPI data shift order ======================*/
//  #define USIM_SPI_LSB_FIRST      (1)         /*USIM SPI LSB first*/
    #define USIM_SPI_MSB_FIRST      (1)         /*USIM SPI MSB first*/

/*============== The end of Select USIMn SPI data shift order ================*/

/*==================== Select USIMn_UART operating mode ======================*/
/* USIM UART select non single wire mode */
//  #define USIM_UART_NORMAL_MODE       (1)
/* USIM UART select single wire mode */
//  #define USIM_UART_SINGLE_WIRE_MODE  (1)

/*=============== The end of Select USIMn_UART operating mode ================*/

/*=================== Select USIMn_UART Baud rate speed ======================*/
/* USIM UART select high speed baud rate */
//  #define USIM_UART_HS_BR_MODE    (1)
/* USIM UART select low speed baud rate */
//  #define USIM_UART_LS_BR_MODE    (1)

/*============== The end of Select USIMn_UART Baud rate speed ================*/

/*=================== Select USIMn_UART error detection ======================*/
//  #define USIM_UART_EVENPR_MODE       (1) /*USIM UART Even parity Mode*/
//  #define USIM_UART_ODDPR_MODE        (1) /*USIM UART Odd parity Mode*/
//  #define USIM_UART_PARITY_DISABLE    (1) /*USIM UART Parity function disable*/
//  #define USIM_UART_NF_MODE           (1) /*USIM UART Noise Mode*/
//  #define USIM_UART_FERR_MODE         (1) /*USIM UART Framing error Mode*/
//  #define USIM_UART_OERR_MODE         (1) /*USIM UART Overrun error Mode*/

/*============== The end of Select USIMn_UART error detection ================*/

/*===================== Select USIMn_UART data format ========================*/
/* USIM UART two stop bits format is used */
//  #define USIM_UART_TWO_STOPS_MODE    (1)
/* USIM UART one stop bits format is used */
//  #define USIM_UART_ONE_STOP_MODE     (1)
/* USIM UART 9-bit data transfer */
//  #define USIM_UART_NINE_BIT_MODE     (1)
/* USIM UART 8-bit data transfer */
//  #define USIM_UART_EIGHT_BIT_MODE    (1)

/*================ The end of Select USIMn_UART data format ==================*/

/* Exported functions---------------------------------------------------------*/
void USIM_UART_Init(u8 BaudRate);
void USIM_UART_Transmit(u16 data);
void USIM_SIM_Init(void);
void USIM_I2C_Timeout_Update(u8 timeout);
u8 USIM_SPI_MasterSendData(u8 TX_data);

extern volatile vu8 g_USIM_SIM_Tx_Buf;
extern volatile vu8 g_USIM_SIM_Rx_Buf;
extern volatile vu16 g_USIM_UART_ISR_Value[2];
extern volatile vu8  g_USIM_UART_err_Flag;


#endif

/*********** (C) COPYRIGHT 2019 Holtek Semiconductor Inc **********END OF FILE*/
