/*******************************************************************************
  * @file     HT8_DEMO.c
  * @brief    This file provides all the DEMO firmware functions.
  * @author   Holtek Semiconductor Inc.
  * @version  V1.0.0
  * @date     2023-2-7
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
#include "HT8_DEMO.h"

vu16 g_ADC_ISR_Value;               /*AD conversion value (Interrupt)*/
vu8  g_ADC_Finish;                  /*AD conversion complete flag*/
u16  g_ConversionValue;             /*AD conversion value*/

u8   g_EEPROM_DATA;                 /*EEPROM Byte Write/Read data*/
vu8  g_EEPROM_WR_Finish;            /*EEPEOM Wirte and read complete flag*/


vu8  g_USIM_UART_RX_FLAG;           /*USIM UART receive success flag*/


vu8  g_SW_UART_RX_Data;
vu8  g_SW_UART_RX_Status;

vu8  g_SW_I2C_complete_flag;
vu8  g_SW_I2C_RX_Data;

vu8  g_PTM_Capture_Finish;          /*PTM capture complete flag*/
vu16 g_PTM_ISR_Value[2];            /*PTM capture value(ISR)*/
vu8  g_PTM_Capture_cnt;             /*PTM capture count*/
vu8  g_PTM_CCRP_OV_cnt;             /*PTM CCRP overflow count*/

vu8  g_STM_Capture_Finish;          /*STM capture complete flag*/
vu16 g_STM_ISR_Value[2];            /*STM capture value(ISR)*/
vu8  g_STM_Capture_cnt;             /*STM capture count*/
vu8  g_STM_CCRP_OV_cnt;             /*STM CCRP overflow count*/

vu8  g_SW_SPI_Tx_Buf;
vu8  g_SW_SPI_Rx_Buf;


/*******************************************************************************
  * @brief    DEMO initialization function.
  * @param    None
  * @retval   None
 *******************************************************************************/
void DEMO_Init(void)
{
    #ifdef  _ADC
            g_ADC_ISR_Value = 0;
            g_ConversionValue =  0;
            g_ADC_Finish = 0;
    #endif

    #ifdef  _EEPROM
            g_EEPROM_WR_Finish = 0;
    #endif

    #ifdef  _STM
            g_STM_Capture_Finish = 0;
            g_STM_ISR_Value[0] = 0;
            g_STM_ISR_Value[1] = 0;
            g_STM_Capture_cnt=0;
            g_STM_CCRP_OV_cnt=0;
    #endif

    #ifdef  _PTM
            g_PTM_Capture_Finish = 0;
            g_PTM_ISR_Value[0] = 0;
            g_PTM_ISR_Value[1] = 0;
            g_PTM_Capture_cnt=0;
            g_PTM_CCRP_OV_cnt=0;
    #endif


    #ifdef  _USIM
            g_USIM_SIM_Tx_Buf = 0;
            g_USIM_SIM_Rx_Buf = 0;
            g_USIM_UART_RX_FLAG = 0;

    #endif


    #ifdef  _SW_I2C_Master
            g_SW_I2C_complete_flag = 0;
    #endif

    #ifdef  _SW_SPI_Master
            g_SW_SPI_Tx_Buf = 0;
            g_SW_SPI_Rx_Buf = 0;
    #endif

}

/*******************************************************************************
  * @brief    DEMO setting function.
  * @param    None
  * @retval   None
 *******************************************************************************/
void DEMO_Setting(void)
{
    #ifdef  _ADC
        if (_ade)
        {
            /* For ADC_InterruptMode_Demo, start the first A/D conversion */
            ADC_START();
        }
    #endif

    #ifdef  _LCD
            #ifdef  HW_LCD_TYPE

                    /* Look up table for first number */
                    SEG[0] = Trans_Segment[123/100] & 0x0f;
                    SEG[1] = Trans_Segment[123/100] >> 4;

                    /* Look up table for second number */
                    SEG[2] = Trans_Segment[123%100/10] & 0x0f;
                    SEG[3] = Trans_Segment[123%100/10] >> 4;

                    /* Look up table for third number */
                    SEG[4] = Trans_Segment[123%10] & 0x0f;
                    SEG[5] = Trans_Segment[123%10] >> 4;

                    /* Do not display */
                    SEG[6] = 0;
                    SEG[7] = 0;

            #elif   SW_LCD_TYPE

                    /* Look up table for first number */
                    g_u8SegBuf[0] = Trans_Segment[123/100];

                    /* Look up table for second number */
                    #if (LCD_RAM_Total_Byte > 1)
                        g_u8SegBuf[1] = Trans_Segment[123%100/10];
                    #endif

                    /* Look up table for third number */
                    #if (LCD_RAM_Total_Byte > 2)
                        g_u8SegBuf[2] = Trans_Segment[123%10];
                    #endif

                    /* Do not display */
                    #if (LCD_RAM_Total_Byte > 3)
                        g_u8SegBuf[3] = 0;
                    #endif
            #endif
    #endif
}

/*******************************************************************************
  * @brief    ADC Interrupt Mode Demo function.
  * @param    None
  * @retval   None
 *******************************************************************************/
void ADC_InterruptMode_Demo(void)
{
    #ifdef  _ADC
            if (1 == g_ADC_Finish)
            {
                /* The g_ADC_ISR_Value is get in HT8_it.c ADC interrupt */
                g_ConversionValue = g_ADC_ISR_Value;
                
                g_ADC_Finish = 0;
                
                GCC_DELAY(4000);
                /* Start the next A/D conversion */
                ADC_START();
            }
    #endif
}

/*******************************************************************************
  * @brief    ADC Polling Mode Demo function.
  * @param    None
  * @retval   None
 *******************************************************************************/
void ADC_PollingMode_Demo(void)
{
    #ifdef  _ADC
            g_ConversionValue = ADC_GetValue();     /*Get AD converter value*/
            
            GCC_DELAY(4000);
    #endif
}


/*******************************************************************************
  * @brief    External INT Polling Mode Demo function.
  * @param    None
  * @retval   None
 *******************************************************************************/
void EINT_PollingMode_Demo(void)
{
    #ifdef  _EXTI
            if (1 == INT0_GET_ISR_FLAG())
            {
                Indicator_pin = ~Indicator_pin;
                INT0_CLEAR_ISR_FLAG();
            }

            if (1 == INT1_GET_ISR_FLAG())
            {
                Indicator_pin = ~Indicator_pin;
                INT1_CLEAR_ISR_FLAG();
            }

            Trigger_pin = ~Trigger_pin;
            GCC_DELAY(1000);
    #endif
}

/*******************************************************************************
  * @brief    External INT Interrupt Mode Demo function.
  * @param    None
  * @retval   None
 *******************************************************************************/
void EINT_InterruptMode_Demo(void)
{
    #ifdef  _EXTI
            Trigger_pin = ~Trigger_pin;
            GCC_DELAY(1000);
    #endif
}


/*******************************************************************************
  * @brief    EEPROM Write Read Demo function.
  * @param    None
  * @retval   None
 *******************************************************************************/
void EEPROM_Write_Read_Demo(void)
{
    #ifdef  _EEPROM
            if (0 == g_EEPROM_WR_Finish)
            {
                u8 i;
                
                /* Write 0x55 to EEPROM,  EEPROM address is 0x10 */
                EEPROM_Write_Byte(0x55,0x10);
                
                g_EEPROM_DATA = 0;                      /*EEPROM Data init*/
                
                /* Read EEPROM data to EEPROM_DATA, EEPROM address is 0x10 */
                g_EEPROM_DATA = EEPROM_Read_Byte(0x10);
                
                
                /* Write EEPROM Page 0 */
                    
                g_EEPROM_WR_Finish =1;
            }
    #endif
}

/*******************************************************************************
  * @brief    System Clock Demo function.
  * @param    None
  * @retval   None
 *******************************************************************************/
void SYS_Clock_Demo(void)
{
    /* fsys = f_Indicator_pin *80  */
    #ifdef  _SYS_Clock
            Indicator_pin = 1;
            GCC_DELAY(9);
        
            Indicator_pin = 0;
            GCC_DELAY(2);
    #endif
}

/*******************************************************************************
  * @brief    LVR Demo function.
  * @param    None
  * @retval   None
 *******************************************************************************/
void LVR_Demo(void)
{
    #ifdef  _LVR
            Indicator_pin_LVR = 0;
    #endif
}

/*******************************************************************************
  * @brief    LVD Polling Mode Demo function.
  * @param    None
  * @retval   None
 *******************************************************************************/
void LVD_PollingMode_Demo(void)
{
    #ifdef  _LVD
            if (1 == _lvdo)
            {
                _lvdo = 0;

                /* Detect low voltage, Indicator_pin output high */
                Indicator_pin_LVD  = 1;
            }
            else
            {
                /* Do not detect low voltage, Indicator_pin output low */
                Indicator_pin_LVD  = 0;
            }
    #endif
}

/*******************************************************************************
  * @brief    WDT Halt Mode Timeout Demo function.
  * @param    None
  * @retval   None
 *******************************************************************************/
void WDT_Halt_TO_Demo(void)
{
    #ifdef  _WDT
            /* WDT counter overflow reset, Indicator_pin output toggle */
            Indicator_pin = ~Indicator_pin;

            /* Halt mode,wait WDT overflow */
            EnterHaltMode(HALT_IDLE0);
    #endif
}

/*******************************************************************************
  * @brief    TimeBase Polling Mode Demo function.
  * @param    None
  * @retval   None
 *******************************************************************************/
void TIMEBASE_PollingMode_Demo(void)
{
    #ifdef  _TIMEBASE
            if (1 == TB0_GET_ISR_FLAG())
            {
                /* Clear TB0 counter overflow flag */
                TB0_CLEAR_ISR_FLAG();

                /* TB0 counter overflow reset, Indicator_pin output toggle */
                Indicator_pin = ~Indicator_pin;
            }

            if (1 == TB1_GET_ISR_FLAG())
            {
                /* Clear TB1 counter overflow flag */
                TB1_CLEAR_ISR_FLAG();

                /* TB1 counter overflow reset, Indicator_pin output toggle */
                Indicator_pin = ~Indicator_pin;
            }

    #endif
}

/*******************************************************************************
  * @brief    STM Timer/Counter Polling Mode Demo function.
  * @param    None
  * @retval   None
 *******************************************************************************/
void STM_Timer_Counter_PollingMode_Demo(void)
{
    #ifdef  _STM
            #ifdef  STM_TIMER_COUNTER_MODE
                    if (1 == STM_GET_CCRA_ISR_FLAG())       /*Polling CCRA flag*/
                    {
                        STM_CLEAR_CCRA_ISR_FLAG();          /*Clear CCRA flag*/
                        Indicator_pin = ~Indicator_pin;
                    }
            #endif

    #endif
}

/*******************************************************************************
  * @brief    STM Capture Input Interrupt Mode Demo function.
  * @param    None
  * @retval   None
 *******************************************************************************/
void STM_Capture_Input_InterruptMode_Demo(void)
{
    #ifdef  _STM
            #ifdef  STM_CAPTURE_INPUT_MODE
                    if (g_STM_Capture_Finish)
                    {
                        u16 STM_Capture_Value[2]; 
                    /* Read Capture Value which is get in HT8_it.c STM interrupt */
                        STM_Capture_Value[0]=g_STM_ISR_Value[0];
                        STM_Capture_Value[1]=g_STM_ISR_Value[1];
                        
                    /* Count difference between two adjacent trigger edges
                    10-bit STM=1024 * g_STM_CCRP_OV_cnt + STM_Capture_Value[1] - STM_Capture_Value[0]
                    16-bit STM= 65536 * g_STM_CCRP_OV_cnt + STM_Capture_Value[1] - STM_Capture_Value[0]*/
                    }
                    else
                    {
                        u8 i;
                        /* Create two high pulse to trigger capture */
                        for( i=0; i<4; i++)
                        {
                            Trigger_pin = ~Trigger_pin;
                            GCC_DELAY(2000);
                        }
                    }
            #endif

    #endif
}

/*******************************************************************************
  * @brief    STM Single Pulse Output Mode Demo function.
  * @param    None
  * @retval   None
 *******************************************************************************/
void STM_Single_Pulse_Output_Mode_Demo(void)
{
    #ifdef  _STM
            #ifdef  STM_SINGLE_PULSE_OUTPUT_MODE
                    if (0 == _ston)
                    {
                        GCC_DELAY(2000);
                        STM_ENABLE();           /*Trigger OUTPUT Single Pulse*/
                    }
            #endif

    #endif
}

/*******************************************************************************
  * @brief    PTM Timer/Counter Polling Mode Demo function.
  * @param    None
  * @retval   None
 *******************************************************************************/
void PTM_Timer_Counter_PollingMode_Demo(void)
{
    #ifdef  _PTM
            #ifdef  PTM0_TIMER_COUNTER_MODE
                    if (1 == PTM0_GET_CCRA_ISR_FLAG())      /*Polling CCRA flag*/
                    {
                        PTM0_CLEAR_CCRA_ISR_FLAG();         /*Clear CCRA flag*/
                        Indicator_pin = ~Indicator_pin;
                    }
            #endif

            #ifdef  PTM1_TIMER_COUNTER_MODE
                    if (1 == PTM1_GET_CCRA_ISR_FLAG())      /*Polling CCRA flag*/
                    {
                        PTM1_CLEAR_CCRA_ISR_FLAG();         /*Clear CCRA flag*/
                        Indicator_pin = ~Indicator_pin;
                    }
            #endif

    #endif
}

/*******************************************************************************
  * @brief    PTM Capture Input Interrupt Mode Demo function.
  * @param    None
  * @retval   None
 *******************************************************************************/
void PTM_Capture_Input_InterruptMode_Demo(void)
{
    #ifdef  _PTM
            #ifdef  PTM0_CAPTURE_INPUT_MODE
                    if (g_PTM_Capture_Finish)
                    {
                        u16 PTM_Capture_Value[2]; 
                    /* Read Capture Value which is get in HT8_it.c PTM0 interrupt */
                        PTM_Capture_Value[0]=g_PTM_ISR_Value[0];
                        PTM_Capture_Value[1]=g_PTM_ISR_Value[1];
                        
                    /* Count difference between two adjacent trigger edges
                    10-bit PTM=1024 * g_PTM_CCRP_OV_cnt + PTM_Capture_Value[1] - PTM_Capture_Value[0]
                    16-bit PTM= 65536 * g_PTM_CCRP_OV_cnt + PTM_Capture_Value[1] - PTM_Capture_Value[0]*/
                    }
                    else
                    {
                        u8 i;
                        /* Create two high pulse to trigger capture */
                        for( i=0; i<4; i++)
                        {
                            Trigger_pin = ~Trigger_pin;
                            GCC_DELAY(2000);
                        }
                    }
            #endif

            #ifdef  PTM1_CAPTURE_INPUT_MODE
                    if (g_PTM_Capture_Finish)
                    {
                        u16 PTM_Capture_Value[2]; 
                    /* Read Capture Value which is get in HT8_it.c PTM1 interrupt */
                        PTM_Capture_Value[0]=g_PTM_ISR_Value[0];
                        PTM_Capture_Value[1]=g_PTM_ISR_Value[1];
                        
                    /* Count difference between two adjacent trigger edges
                    10-bit PTM=1024 * g_PTM_CCRP_OV_cnt + PTM_Capture_Value[1] - PTM_Capture_Value[0]
                    16-bit PTM= 65536 * g_PTM_CCRP_OV_cnt + PTM_Capture_Value[1] - PTM_Capture_Value[0]*/
                    }
                    else
                    {
                        u8 i;
                        /* Create two high pulse to trigger capture */
                        for( i=0; i<4; i++)
                        {
                            Trigger_pin = ~Trigger_pin;
                            GCC_DELAY(2000);
                        }
                    }
            #endif

    #endif
}

/*******************************************************************************
  * @brief    PTM Single Pulse Output Mode Demo function.
  * @param    None
  * @retval   None
 *******************************************************************************/
void PTM_Single_Pulse_Output_Mode_Demo(void)
{
    #ifdef  _PTM
            #ifdef  PTM0_SINGLE_PULSE_OUTPUT_MODE
                    if (0 == _pt0on)
                    {
                        GCC_DELAY(2000);
                        PTM0_ENABLE();          /*Trigger OUTPUT Single Pulse*/
                    }
            #endif

            #ifdef  PTM1_SINGLE_PULSE_OUTPUT_MODE
                    if (0 == _pt1on)
                    {
                        GCC_DELAY(2000);
                        PTM1_ENABLE();          /*Trigger OUTPUT Single Pulse*/
                    }
            #endif

    #endif
}


/*******************************************************************************
  * @brief    S/W UART Receive Transmit Demo function.
  * @param    None
  * @retval   None
 *******************************************************************************/
void SW_UART_Receive_Transmit_Demo(void)
{
    #ifdef  _SW_UART
            SW_UART_Mode_Set(RX_MODE);  /*Set SW UART to receive mode*/
            while(!g_SW_UART_RX_end_flag);  /*Wait for receiving to complete*/
            g_SW_UART_RX_end_flag = 0;  /*Reset receive end flag*/
            g_SW_UART_RX_Status = g_SW_UART_RX_end_Status;  /*Read receive status*/
            g_SW_UART_RX_Data = g_SW_UART_rxr;  /*Read received data*/
            
            SW_UART_Mode_Set(TX_MODE);  /*Set SW UART to sending mode*/
            SW_UART_Transmit(g_SW_UART_RX_Data);/*Send data*/
            while(!g_SW_UART_TX_end_flag);  /*Wait for sending to complete*/
    #endif
}

/*******************************************************************************
  * @brief    USIM UART Receive Transmit Demo function.
  * @param    None
  * @retval   None
 *******************************************************************************/
void USIM_UART_Receive_Transmit_Demo(void)
{
    #ifdef  _USIM
            if (g_USIM_UART_RX_FLAG)        /*Check receive finished?*/
            {
                g_USIM_UART_RX_FLAG = 0;
                
                /* Send receive data */
                #ifdef  USIM_UART_FIFO_4B
                        USIM_UART_Transmit(g_USIM_UART_ISR_Value[0]);
                        USIM_UART_Transmit(g_USIM_UART_ISR_Value[1]);
                        USIM_UART_Transmit(g_USIM_UART_ISR_Value[2]);
                        USIM_UART_Transmit(g_USIM_UART_ISR_Value[3]);
                    
                #elif   USIM_UART_FIFO_1B_M
                        USIM_UART_Transmit(g_USIM_UART_ISR_Value[0]);
                        
                #elif   USIM_UART_FIFO_2B_M
                        USIM_UART_Transmit(g_USIM_UART_ISR_Value[0]);
                        USIM_UART_Transmit(g_USIM_UART_ISR_Value[1]);
                    
                #elif   USIM_UART_FIFO_3B_M
                        USIM_UART_Transmit(g_USIM_UART_ISR_Value[0]);
                        USIM_UART_Transmit(g_USIM_UART_ISR_Value[1]);
                        USIM_UART_Transmit(g_USIM_UART_ISR_Value[2]);
                    
                #else
                        USIM_UART_Transmit(g_USIM_UART_ISR_Value[0]);
                #endif
            }

    #endif
}

/*******************************************************************************
  * @brief    USIM SPI Master Polling Mode Demo function.
  * @param    None
  * @retval   None
 *******************************************************************************/
void USIM_SPI_Master_PollingMode_Demo(void)
{
    #ifdef  _USIM
            /* USIM SPI transmits 1-byte data and read data from simd */
            USIM_SPI_CS_ENABLE();
            g_USIM_SIM_Rx_Buf = USIM_SPI_MasterSendData(g_USIM_SIM_Tx_Buf);

            /* Transmit data increase, it will send 0 to 0xff  in system loop */
            g_USIM_SIM_Tx_Buf++;

            USIM_SPI_CS_DISABLE();
            GCC_DELAY(1000);


    #endif
}


/*******************************************************************************
  * @brief    SW I2C Master Demo function.
  * @param    None
  * @retval   None
 *******************************************************************************/
void SW_I2C_Master_Demo(void)
{
    #ifdef  _SW_I2C_Master
        if (g_SW_I2C_complete_flag == 0)
        {
            /* Master addressed Slave, if Slave response ACK,
                Master transmit one byte data and STOP */
            if(BUSY == SW_I2C_Send_Start()) /*Master transmit the Start signal*/
                return;
            else
            {
                /* Master transmit the Slave address and set Slave as the receiver */
                if(NACK == SW_I2C_Send_Addr(SLAVE_ADDRESS,RX_Mode))
                {
                    SW_I2C_Send_Stop(); /*Master transmit the Stop signal*/
                    return;
                }
                else
                {
                    GCC_DELAY(10);
                    SW_I2C_Send_Data(0x55); /*Master transmit 1-byte data(0x55)*/
                }
            }
            SW_I2C_Send_Stop(); /*Master transmit the Stop signal*/


            /* Master addressed Slave, if Slave response ACK,
                Master receive 1-byte data and then tansmits STOP */
            if(BUSY == SW_I2C_Send_Start()) /*Master transmit the Start signal*/
                return;
            else
            {
                /* Master transmit the Slave address and set Slave as the sender */
                if(NACK == SW_I2C_Send_Addr(SLAVE_ADDRESS,TX_Mode))
                {
                    SW_I2C_Send_Stop(); /*Master transmit the Stop signal*/
                    return;
                }
                else
                {
                    GCC_DELAY(10);
                /* Master receive 1-byte data and return NACK, 
                    and the receive data is stored to I2C_RX_Data.*/
                    g_SW_I2C_RX_Data = SW_I2C_Receive_Data(NACK);
                }
            }
            SW_I2C_Send_Stop(); /*Master transmit the Stop signal*/

            g_SW_I2C_complete_flag = 1;
        }
    #endif
}


/*******************************************************************************
  * @brief    SW SPI Master Demo function.
  * @param    None
  * @retval   None
 *******************************************************************************/
void SW_SPI_Master_Demo(void)
{
    #ifdef  _SW_SPI_Master


            /* write 1-byte data to SDO and read 1-byte data from SDI simultaneously */
            SW_SCSB_ENABLE();
            g_SW_SPI_Rx_Buf = SW_SPI_Master_Send_Data(g_SW_SPI_Tx_Buf);

            /* Transmit data increase, it will send 0 to 0xff  in system loop */
            g_SW_SPI_Tx_Buf++;

            SW_SCSB_DISABLE();

            GCC_DELAY(1000);


    #endif
}

/*********** (C) COPYRIGHT 2019 Holtek Semiconductor Inc **********END OF FILE*/
