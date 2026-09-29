/*******************************************************************************
  * @file     HT8_SW_UART.c
  * @brief    This file provides all the S/W UART firmware functions.
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
#include "HT8_SW_UART.h"

volatile SW_UART_Mode_TypeDef g_SW_UART_Mode;
volatile ErrorStatus g_SW_UART_RX_end_Status;

vu8  g_SW_UART_TX_STOP_Bit_cnt;
vu8  g_SW_UART_RX_STOP_Bit_cnt;
vu8  g_SW_UART_TX_Bit_cnt;
vu8  g_SW_UART_RX_Bit_cnt;
vu16 g_SW_UART_RX_buf;
vu16 g_SW_UART_txr;
vu16 g_SW_UART_rxr;

volatile bit g_SW_UART_TX_start_flag;
volatile bit g_SW_UART_RX_start_flag;
volatile bit g_SW_UART_TX_end_flag;
volatile bit g_SW_UART_RX_end_flag;

/*******************************************************************************
  * @brief    S/W UART initialization function.
  * @param    None
  * @retval   None
 *******************************************************************************/
void SW_UART_Init(void)
{
    g_SW_UART_TX_start_flag = 0;
    g_SW_UART_TX_end_flag = 1;
    g_SW_UART_RX_start_flag = 0;
    g_SW_UART_RX_end_flag = 0;

    RX_C = 1;

    #ifdef  RX_INTERNAL_PU_EN
            RX_PU = 1;

    #elif   RX_INTERNAL_PU_DIS
            RX_PU = 0;

    #endif

    TX_C = 0; 
    TX = 1;
}


/*******************************************************************************
  * @brief    S/W UART TX/RX mode setting function.
  * @param    mode: RX_MODE or TX_MODE.
  * @retval   None
 *******************************************************************************/
void SW_UART_Mode_Set(SW_UART_Mode_TypeDef mode)
{
    if(mode == RX_MODE)
    {
        RX_INT_ISR_EN();
        g_SW_UART_Mode = mode;
    }
    else if(mode == TX_MODE)
    {
        RX_INT_ISR_DIS();
        g_SW_UART_Mode = mode;
    }
}


/*******************************************************************************
  * @brief    S/W UART transmit function.
  * @param    data: Transmit data
  *           the data value range is 0 ~ 511.
  * @retval   None
 *******************************************************************************/
void SW_UART_Transmit(u16 data)
{
    /* Waitting SW UART transmit data finished */
    while(!g_SW_UART_TX_end_flag)
    {
        _nop();
    }
    /* The end of waitting SW UART transmit data finished */

    g_SW_UART_TX_end_flag = 0;
    g_SW_UART_txr = data;           /*Write data to UART transmitter */
    SW_UART_TM_EN();                /*Enable TX Baudrate timer*/
}


/*******************************************************************************
  * @brief    S/W UART Receive start bit process function.
  * @param    None
  * @retval   None
 *******************************************************************************/
void SW_UART_RX_Start_Process(void)
{
    SW_UART_TM_VALUE_L = (SW_UART_TM_VALUE >> 1) & 0x00ff;
    SW_UART_TM_VALUE_H = (SW_UART_TM_VALUE >> 1) >> 8;

    SW_UART_TM_DIS();
    SW_UART_TM_EN();
}


/*******************************************************************************
  * @brief    S/W UART transmit process function.
  * @param    None
  * @retval   None
 *******************************************************************************/
void SW_UART_Transmit_Process(void)
{
    if (!g_SW_UART_TX_start_flag)
    {
        /*========================= Transmit the start bit ===========================*/
        TX = 0;
        g_SW_UART_TX_start_flag = 1;

        #ifdef  SW_UART_NINE_BIT_MODE 
                g_SW_UART_TX_Bit_cnt = 9;
        #elif   SW_UART_EIGHT_BIT_MODE
                g_SW_UART_TX_Bit_cnt = 8;
        #endif

        #ifdef  SW_UART_TWO_STOPS_MODE
                g_SW_UART_TX_STOP_Bit_cnt = 2;
        #elif   SW_UART_ONE_STOP_MODE
                g_SW_UART_TX_STOP_Bit_cnt = 1;
        #endif
    }
    else
    {
        /*========================= Transmit the data bit ============================*/
        if (g_SW_UART_TX_Bit_cnt > 0) 
        {
            if(g_SW_UART_txr & 0x01)
            {
                TX = 1;
            }
            else
            {
                TX = 0;
            }
            g_SW_UART_txr >>= 1;
            g_SW_UART_TX_Bit_cnt--;
        }
        else
        {
            /*========================= Transmit the stop bit ============================*/
            TX = 1;
            if(--g_SW_UART_TX_STOP_Bit_cnt == 0)
            {
                g_SW_UART_TX_start_flag = 0;
                g_SW_UART_TX_end_flag = 1;
                SW_UART_TM_DIS();
            }
        }
    }
}


/*******************************************************************************
  * @brief    S/W UART receive process function.
  * @param    None
  * @retval   None
 *******************************************************************************/
void SW_UART_Receive_Process(void)
{
    if (g_SW_UART_RX_start_flag == 0)
    {
        /*========================= Receive the start bit ============================*/
        if (RX == 0)
        {

            SW_UART_TM_VALUE_L = SW_UART_TM_VALUE & 0x00ff;
            SW_UART_TM_VALUE_H = SW_UART_TM_VALUE >> 8;

            g_SW_UART_RX_start_flag = 1;
            g_SW_UART_RX_buf = 0;

            #ifdef  SW_UART_NINE_BIT_MODE 
                    g_SW_UART_RX_Bit_cnt = 9;
            #elif   SW_UART_EIGHT_BIT_MODE
                    g_SW_UART_RX_Bit_cnt = 8;
            #endif

            #ifdef  SW_UART_TWO_STOPS_MODE
                    g_SW_UART_RX_STOP_Bit_cnt = 2;
            #elif   SW_UART_ONE_STOP_MODE
                    g_SW_UART_RX_STOP_Bit_cnt = 1;
            #endif

            RX_INT_CLEAR_FLAG();
            RX_INT_ISR_DIS();
        }
        else
        {
            g_SW_UART_RX_start_flag = 0;
        }
    }
    else
    {
        /*========================== Receive the data bit ============================*/
        if (g_SW_UART_RX_Bit_cnt > 0)
        {
            #ifdef  SW_UART_NINE_BIT_MODE 
                    if (g_SW_UART_RX_Bit_cnt > 1)
                    {
                        g_SW_UART_RX_buf >>= 1;
                        if (RX == 1)
                        {
                            g_SW_UART_RX_buf |= 0x80;
                        }
                        else
                        {
                            g_SW_UART_RX_buf &= 0x7f;
                        }
                    }
                    else
                    {
                        if (RX == 1)
                        {
                            g_SW_UART_RX_buf |= 0x100;
                        }
                        else
                        {
                            g_SW_UART_RX_buf &= 0xff;
                        }
                    }
                    g_SW_UART_RX_Bit_cnt--;

            #elif   SW_UART_EIGHT_BIT_MODE
                    if (g_SW_UART_RX_Bit_cnt != 0)
                    {
                        g_SW_UART_RX_buf  >>= 1;
                        if (RX == 1)
                        {
                            g_SW_UART_RX_buf |= 0x80;
                        }
                        else
                        {
                            g_SW_UART_RX_buf &= 0x7f;
                        }
                    }
                    g_SW_UART_RX_Bit_cnt--;
            #endif
        }
        else
        {
            /*========================== Receive the stop bit ============================*/
            if (RX == 1)
            {
                if (--g_SW_UART_RX_STOP_Bit_cnt == 0)
                {
                    g_SW_UART_RX_end_flag = 1;              /*Receive data finished*/
                    g_SW_UART_RX_start_flag = 0;
                    SW_UART_TM_DIS();                           /*Disable RX baudrate timer*/

                    g_SW_UART_rxr = g_SW_UART_RX_buf;       /*Read the receive data */
                    /* user define */

                    RX_INT_CLEAR_FLAG();

                    /* Enable external interrupt to detect the next start bit falling edge */
                    RX_INT_ISR_EN();

                    g_SW_UART_RX_end_Status = SUCCESS;
                }
            }
            else
            {
                g_SW_UART_RX_end_Status = ERROR;
            }
        }
    }
}


/*********** (C) COPYRIGHT 2019 Holtek Semiconductor Inc **********END OF FILE*/
