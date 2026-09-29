/*******************************************************************************
  * @file     HT8_SW_UART.h
  * @brief    The header file of the S/W UART library.
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
#ifndef _HT8_SW_UART_H_
#define _HT8_SW_UART_H_

/* Includes-------------------------------------------------------------------*/
#include "HT8_MCU_IP_SEL.h"

/* Exported constants---------------------------------------------------------*/
//  #define TX      _pb1            /*Define TX pin data register*/
//  #define TX_C    _pbc1           /*Define TX pin control register*/
    #define TX      _pb6
    #define TX_C    _pbc6


//  #define RX      _pb0            /*Define RX pin data register*/
//  #define RX_C    _pbc0           /*Define RX pin control register*/
//  #define RX_PU   _pbpu0          /*Define RX pull up control register*/
    #define RX      _pa1
    #define RX_C    _pac1
    #define RX_PU   _papu1
    #define SW_UART_RX_USE_INT1     (1)
    #define RX_INT_ISR_EN()         INT1_ISR_ENABLE()
    #define RX_INT_ISR_DIS()        INT1_ISR_DISABLE()
    #define RX_INT_CLEAR_FLAG()     INT1_CLEAR_ISR_FLAG()


//  #define SW_UART_RX_USE_INT0     (1)     /*Define RX  pin share with INTx*/

//  #define RX_INT_ISR_EN()     INT0_ISR_ENABLE()   /*Enable INTx interrupt*/
//  #define RX_INT_ISR_DIS()    INT0_ISR_DISABLE()  /*Disable INTx interrupt*/

//  #define RX_INT_CLEAR_FLAG() INT0_CLEAR_ISR_FLAG()   /*Clear INTx interrupt flag*/

    #define RX_INTERNAL_PU_EN       (1)     /*Enable RX internal pull up*/
//  #define RX_INTERNAL_PU_DIS      (1)     /*Disable RX internal pull up*/

/*======================= Select SW UART data format =========================*/
    #define SW_UART_ONE_STOP_MODE   (1)     /*One stop bits format*/
//  #define SW_UART_TWO_STOPS_MODE  (1)     /*Two stop bits format*/

    #define SW_UART_EIGHT_BIT_MODE  (1)     /*8-bit data transfer*/
//  #define SW_UART_NINE_BIT_MODE   (1)     /*9-bit data transfer*/
/*================= The end of Select SW UART data format ====================*/

//  #define SW_UART_RX_USE_PTM      (1)     /*Define RX Baudrate timer*/

//  #define SW_UART_TM_EN()     PTM_ENABLE()    /*Enable Baudrate timer*/
//  #define SW_UART_TM_DIS()    PTM_DISABLE()   /*Disable Baudrate timer*/

//  #define SW_UART_TM_VALUE_H  _ptmah  /*Define Baudrate timer CCRA high byte register*/
//  #define SW_UART_TM_VALUE_L  _ptmal  /*Define Baudrate timer CCRA low byte register*/
//  #define SW_UART_TM_VALUE    832     /*Define Baudrate timer CCRA value*/
    #define SW_UART_USE_PTM0      (1)
    #define SW_UART_TM_EN()      PTM0_ENABLE()
    #define SW_UART_TM_DIS()     PTM0_DISABLE()
    #define SW_UART_TM_VALUE_H   _ptm0ah
    #define SW_UART_TM_VALUE_L   _ptm0al
    #define SW_UART_TM_VALUE     832


typedef enum 
{
    TX_MODE = 0,
    RX_MODE = 1
}SW_UART_Mode_TypeDef;


/* Exported functions---------------------------------------------------------*/
void SW_UART_Init(void);                    /*S/W UART initialization function*/
void SW_UART_Transmit(u16 data);            /*S/W UART transmit function*/
void SW_UART_Transmit_Process(void);        /*S/W UART System API*/
void SW_UART_Receive_Process(void);         /*S/W UART System API*/
void SW_UART_RX_Start_Process(void);        /*S/W UART System API*/
void SW_UART_Mode_Set(SW_UART_Mode_TypeDef mode);/*S/W UART mode set function*/

extern volatile SW_UART_Mode_TypeDef g_SW_UART_Mode;
extern volatile ErrorStatus g_SW_UART_RX_end_Status;
extern vu8  g_SW_UART_TX_STOP_Bit_cnt;
extern vu8  g_SW_UART_RX_STOP_Bit_cnt;
extern vu8  g_SW_UART_TX_Bit_cnt;
extern vu8  g_SW_UART_RX_Bit_cnt;
extern vu16 g_SW_UART_RX_buf;
extern vu16 g_SW_UART_txr;
extern vu16 g_SW_UART_rxr;
extern volatile bit g_SW_UART_TX_start_flag;
extern volatile bit g_SW_UART_RX_start_flag;
extern volatile bit g_SW_UART_TX_end_flag;
extern volatile bit g_SW_UART_RX_end_flag;

#endif

/*********** (C) COPYRIGHT 2019 Holtek Semiconductor Inc **********END OF FILE*/
