/*******************************************************************************
  * @file     HT8_it.c
  * @brief    This file provides all the interrupt firmware functions.
  * @author   Holtek Semiconductor Inc.
  * @version  V1.0.0
  * @date     2024-3-20
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
#include "HT8_it.h"
#include "..\sys_tick.h"

/*******************************************************************************
  * @brief    External interrupt 0 routine..
  * @param    None
  * @retval   None
 *******************************************************************************/
void __attribute((interrupt(0x04))) INT0_ISR(void)
{

    #ifdef  _DEMO
            #ifdef  _EXTI
                    Indicator_pin = ~Indicator_pin;
            #endif
    #endif


    #ifdef  SW_UART_RX_USE_INT0
            SW_UART_RX_Start_Process();
    #endif

    /* user define */

}

/*******************************************************************************
  * @brief    External interrupt 1 routine..
  * @param    None
  * @retval   None
 *******************************************************************************/
void __attribute((interrupt(0x08))) INT1_ISR(void)
{

    #ifdef  _DEMO
            #ifdef  _EXTI
                    Indicator_pin = ~Indicator_pin;
            #endif
    #endif


    #ifdef  SW_UART_RX_USE_INT1
            SW_UART_RX_Start_Process();
    #endif

    /* user define */

}

/*******************************************************************************
  * @brief    Multi-function 2 interrupt(LVD or EEPROM) routine..
  * @param    None
  * @retval   None
 *******************************************************************************/
void __attribute((interrupt(0x10))) LVD_EEPROM_ISR(void)
{
    if (_lvf == 1)
    {
        _lvf = 0;
        #ifdef  _DEMO
                #ifdef  _LVD
                        Indicator_pin_LVD = ~Indicator_pin_LVD;
                #endif
        #endif

        /* user define */
    }

    if (_def == 1)
    {
        _def = 0;
        /* user define */
    }
}

/*******************************************************************************
  * @brief    Multi-function 0 interrupt(STM) routine..
  * @param    None
  * @retval   None
 *******************************************************************************/
void __attribute((interrupt(0x14))) STM_ISR(void)
{
    if (_stmpf == 1)
    {
        _stmpf = 0;
        #ifdef  _DEMO
                #ifdef  _STM
                        #ifdef  STM_CAPTURE_INPUT_MODE
                                g_STM_CCRP_OV_cnt = g_STM_CCRP_OV_cnt + 1;
                        #endif
                #endif
        #endif

        /* user define */
    }

    if (_stmaf == 1)
    {
        _stmaf = 0;
        #ifdef  _DEMO
                #ifdef  _STM
                        #ifdef  STM_TIMER_COUNTER_MODE
                                Indicator_pin = ~Indicator_pin;
                        #endif

                        #ifdef  STM_CAPTURE_INPUT_MODE
                                g_STM_ISR_Value[g_STM_Capture_cnt] = STM_GET_CAPTURE_VALUE();
                                g_STM_Capture_cnt = g_STM_Capture_cnt + 1;

                                if(g_STM_Capture_cnt == 2)
                                {
                                    g_STM_Capture_Finish = 1;
                                    STM_DISABLE();
                                }
                        #endif
                #endif
        #endif


        #ifdef  LCD_USE_STM
                LCD_Scan();
        #endif


        #ifdef  SW_UART_USE_STM
                if(g_SW_UART_Mode == RX_MODE)
                {
                    SW_UART_Receive_Process();
                }
                else if(g_SW_UART_Mode == TX_MODE)
                {
                    SW_UART_Transmit_Process();
                }
        #endif

        /* user define */
    }
}

/*******************************************************************************
  * @brief    Multi-function 1 interrupt(PTM0 or PTM1) routine..
  * @param    None
  * @retval   None
 *******************************************************************************/
void __attribute((interrupt(0x18))) PTM0_PTM1_ISR(void)
{
    if (_ptm0pf == 1)
    {
        _ptm0pf = 0;
        #ifdef  _DEMO
                #ifdef  _PTM
                        #ifdef  PTM0_CAPTURE_INPUT_MODE
                                g_PTM_CCRP_OV_cnt = g_PTM_CCRP_OV_cnt + 1;
                        #endif
                #endif
        #endif

        /* user define */
    }

    if (_ptm0af == 1)
    {
        _ptm0af = 0;
        #ifdef  _DEMO
                #ifdef  _PTM
                        #ifdef  PTM0_TIMER_COUNTER_MODE
                                Indicator_pin = ~Indicator_pin;
                        #endif

                        #ifdef  PTM0_CAPTURE_INPUT_MODE
                                g_PTM_ISR_Value[g_PTM_Capture_cnt] = PTM0_GET_CAPTURE_VALUE();
                                g_PTM_Capture_cnt = g_PTM_Capture_cnt + 1;

                                if(g_PTM_Capture_cnt == 2)
                                {
                                    g_PTM_Capture_Finish = 1;
                                    PTM0_DISABLE();
                                }
                        #endif
                #endif
        #endif


        #ifdef  LCD_USE_PTM0
                LCD_Scan();
        #endif


        #ifdef  SW_UART_USE_PTM0
                if(g_SW_UART_Mode == RX_MODE)
                {
                    SW_UART_Receive_Process();
                }
                else if(g_SW_UART_Mode == TX_MODE)
                {
                    SW_UART_Transmit_Process();
                }
        #endif

        /* user define */
    }

    if (_ptm1pf == 1)
    {
        _ptm1pf = 0;
        #ifdef  _DEMO
                #ifdef  _PTM
                        #ifdef  PTM1_CAPTURE_INPUT_MODE
                                g_PTM_CCRP_OV_cnt = g_PTM_CCRP_OV_cnt + 1;
                        #endif
                #endif
        #endif

        /* user define */
    }

    if (_ptm1af == 1)
    {
        _ptm1af = 0;
        #ifdef  _DEMO
                #ifdef  _PTM
                        #ifdef  PTM1_TIMER_COUNTER_MODE
                                Indicator_pin = ~Indicator_pin;
                        #endif

                        #ifdef  PTM1_CAPTURE_INPUT_MODE
                                g_PTM_ISR_Value[g_PTM_Capture_cnt] = PTM1_GET_CAPTURE_VALUE();
                                g_PTM_Capture_cnt = g_PTM_Capture_cnt + 1;

                                if(g_PTM_Capture_cnt == 2)
                                {
                                    g_PTM_Capture_Finish = 1;
                                    PTM1_DISABLE();
                                }
                        #endif
                #endif
        #endif


        #ifdef  LCD_USE_PTM1
                LCD_Scan();
        #endif


        #ifdef  SW_UART_USE_PTM1
                if(g_SW_UART_Mode == RX_MODE)
                {
                    SW_UART_Receive_Process();
                }
                else if(g_SW_UART_Mode == TX_MODE)
                {
                    SW_UART_Transmit_Process();
                }
        #endif

        /* user define */
    }
}

/*******************************************************************************
  * @brief    A/D converter interrupt routine..
  * @param    None
  * @retval   None
 *******************************************************************************/
void __attribute((interrupt(0x1C))) ADC_ISR(void)
{

    #ifdef  _DEMO
            #ifdef  _ADC
                    g_ADC_ISR_Value = ADC_READ_VALUE();
                    g_ADC_Finish = 1;
            #endif
    #endif

    /* user define */

}

/*******************************************************************************
  * @brief    Time base 0 interrupt routine..
  * @param    None
  * @retval   None
 *******************************************************************************/
void __attribute((interrupt(0x20))) TB0_ISR(void)
{

    #ifdef  _DEMO
            #ifdef  _TIMEBASE
                    Indicator_pin = ~Indicator_pin;
            #endif
    #endif

    /* user define */

}

/*******************************************************************************
  * @brief    Time base 1 interrupt routine..
  * @param    None
  * @retval   None
 *******************************************************************************/
void __attribute((interrupt(0x24))) TB1_ISR(void)
{

    #ifdef  _DEMO
            #ifdef  _TIMEBASE
                    Indicator_pin = ~Indicator_pin;
            #endif
    #endif

    /* user define */
	SysTick_Handler();
}


/*********** (C) COPYRIGHT 2019 Holtek Semiconductor Inc **********END OF FILE*/
