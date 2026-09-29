/*******************************************************************************
  * @file     HT8_USIM.c
  * @brief    This file provides all the USIM firmware functions.
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
#include "HT8_USIM.h"

volatile vu8  g_USIM_SIM_Tx_Buf;
volatile vu8  g_USIM_SIM_Rx_Buf;
volatile vu16 g_USIM_UART_ISR_Value[2];
volatile vu8  g_USIM_UART_err_Flag;


/*******************************************************************************
  * @brief    USIM SIM initialization function.
  * @param    None
  * @retval   None
 *******************************************************************************/
void USIM_SIM_Init(void)
{
    _umd = 0;                                       /*USIM UART mode is not selected*/

    #ifdef  USIM_I2C_Slave
            _sim2 = 1; _sim1 = 1; _sim0 = 0;        /*Select USIM I2C slave mode*/
            _sima = USIM_I2C_DEVICEADDR;            /*Set USIM I2C slave address*/

            #ifdef  USIM_I2C_DEBOUNCE_DISABLE
                    /* Set USIM I2C No debounce time */
                    _simdeb1 = 0; _simdeb0 = 0;

            #elif   USIM_I2C_DEBOUNCE_2_FSYS
                    /* Set USIM I2C Debounce time 2 Fsys */
                    _simdeb1 = 0; _simdeb0 = 1;

            #elif   USIM_I2C_DEBOUNCE_4_FSYS
                    /* Set USIM I2C Debounce time 4 Fsys */
                    _simdeb1 = 1; _simdeb0 = 0;

            #endif

    #elif   USIM_SPI_Master

            /* Select USIM SPI master mode and clock */
            #ifdef  USIM_SPI_Master_FSYS_DIV4
                    /* USIM SPI master mode, SPI clock is fSYS /4 */
                    _sim2 = 0; _sim1 = 0; _sim0 = 0;

            #elif   USIM_SPI_Master_FSYS_DIV16
                    /* USIM SPI master mode, SPI clock is fSYS /16 */
                    _sim2 = 0; _sim1 = 0; _sim0 = 1;

            #elif   USIM_SPI_Master_FSYS_DIV64
                    /* USIM SPI master mode, SPI clock is fSYS /64 */
                    _sim2 = 0; _sim1 = 1; _sim0 = 0;

            #elif   USIM_SPI_Master_FSUB
                    /* USIM SPI master mode, SPI clock is fSUB */
                    _sim2 = 0; _sim1 = 1; _sim0 = 1;

            #elif   USIM_SPI_Master_FPTM0
                    /* USIM SPI master mode, SPI clock is PTM0PINT/2 */
                    _sim2 = 1; _sim1 = 0; _sim0 = 0;

            #endif

            /* USIM SPI SCSB pin control */
            #ifdef  USIM_SPI_CS_ON
                    _csen = 1;                      /*USIM SPI SCSB pin enable*/

            #elif   USIM_SPI_CS_OFF
                    _csen = 0;                      /*USIM SPI SCSB pin disable*/

            #endif

            /* Select USIM SPI SCK clock active edge type */
            #ifdef  USIM_SPI_SCK_HIGH_RISING_EDGE
                    /* USIMn SCK is high base level and
                       data capture at SCK rising edge */
                    _ckpolb = 0; _ckeg = 0;

            #elif   USIM_SPI_SCK_HIGH_FALLING_EDGE
                    /* USIMn SCK is high base level and
                       data capture at SCK falling edge */
                    _ckpolb = 0; _ckeg = 1;

            #elif   USIM_SPI_SCK_LOW_FALLING_EDGE
                    /* USIMn SCK is low base level and
                       data capture at SCK falling edge */
                    _ckpolb = 1; _ckeg = 0;

            #elif   USIM_SPI_SCK_LOW_RISING_EDGE
                    /* USIMn SCK is low base level and
                       data capture at SCK rising edge */
                    _ckpolb = 1; _ckeg = 1;

            #endif

            /* Select USIM SPI data shift order */
            #ifdef  USIM_SPI_LSB_FIRST
                    _mls = 0;                       /*USIM SPI LSB first*/

            #elif   USIM_SPI_MSB_FIRST
                    _mls = 1;                       /*USIM SPI MSB first*/

            #endif

    #elif   USIM_SPI_Slave
            _sim2 = 1; _sim1 = 0; _sim0 = 1;        /*Select USIM SPI slave mode*/

            /* USIM SPI SCSB pin control */
            #ifdef  USIM_SPI_CS_ON
                    _csen = 1;                      /*USIM SPI SCSB pin enable*/

            #elif   USIM_SPI_CS_OFF
                    _csen = 0;                      /*USIM SPI SCSB pin disable*/

            #endif

            /* Select USIM SPI SCK clock active edge type */
            #ifdef  USIM_SPI_SCK_HIGH_RISING_EDGE
                    /* USIMn SCK is high base level and
                       data capture at SCK rising edge */
                    _ckpolb = 0; _ckeg = 0;

            #elif   USIM_SPI_SCK_HIGH_FALLING_EDGE
                    /* USIMn SCK is high base level and
                       data capture at SCK falling edge */
                    _ckpolb = 0; _ckeg = 1;

            #elif   USIM_SPI_SCK_LOW_FALLING_EDGE
                    /* USIMn SCK is low base level and
                       data capture at SCK falling edge */
                    _ckpolb = 1; _ckeg = 0;

            #elif   USIM_SPI_SCK_LOW_RISING_EDGE
                    /* USIMn SCK is low base level and
                       data capture at SCK rising edge */
                    _ckpolb = 1; _ckeg = 1;

            #endif

            /* Select USIM SPI data shift order */
            #ifdef  USIM_SPI_LSB_FIRST
                    _mls = 0;                       /*USIM SPI LSB first*/

            #elif   USIM_SPI_MSB_FIRST
                    _mls = 1;                       /*USIM SPI MSB first*/

            #endif

    #endif
}


/*******************************************************************************
  * @brief    USIM I2C Time-out update function.
  * @param    timeout: Time-out value
  *           the timeout value range is 0 ~ 63.
  *           timeout time= (timeout+1) * Tsub * 32.
  * @retval   None
 *******************************************************************************/
void USIM_I2C_Timeout_Update(u8 timeout)
{
    _simtoc &= 0xc0;
    timeout &= 0x3f;
    _simtoc |= timeout;
}


/*******************************************************************************
  * @brief    USIM SPI peripheral Transmits a Data and read data from simd.
  * @param    TX_data: Data Byte to be transmitted
  * @retval   RX_data: read data from simd
 *******************************************************************************/
u8 USIM_SPI_MasterSendData(u8 TX_data)
{
    u8 RX_data = 0;
    do
    {
        USIM_SPI_WRITE_COLLISION_FLAG = 0;
        _simd = TX_data;                /*Write data to SIMD*/

        GCC_CLRWDT();
        GCC_DELAY(20);

    }while(USIM_SPI_WRITE_COLLISION_FLAG == 1);/*Check SPI write collision*/

    /* Check USIM SPI data transfer completed? */
    while(USIM_SPI_TRX_FLAG == 0)
    {
        GCC_CLRWDT();
    }

    USIM_SPI_TRX_FLAG = 0;              /*Clear TRF*/
    RX_data = _simd;                    /*Read data from SIMD*/
    return(RX_data);
}


/*******************************************************************************
  * @brief    USIM Interruption routine
  * @param    None
  * @retval   None
 *******************************************************************************/
void __attribute((interrupt(0x0c))) USIM_ISR(void)
{
    #ifdef  USIM_I2C_Slave

            /* Not I2C timeout */
            if(!_simtof)
            {
                /* HAAS = 1: Address match trigger interrupt */
                if(_haas == 1)
                {
                    /* SRW = 1: Slave in transfer mode */
                    if(_srw == 1)
                    {
                        _htx = 1;

                        #ifdef  _DEMO
                                /* In DEMO, the transmit data is the receive data */
                                g_USIM_SIM_Tx_Buf = g_USIM_SIM_Rx_Buf;
                        #endif

                        /* Write data to SIMD to release SCL line */
                        _simd = g_USIM_SIM_Tx_Buf;
                    }
                    /* SRW = 0: Slave in receive mode */
                    else
                    {
                        _htx = 0;
                        _txak = 0;

                        /* Dummy read from SIMnD to release SCL line */
                        g_USIM_SIM_Rx_Buf = _simd;
                    }
                }
                /* HAAS = 0: Data trigger interrupt */
                else
                {
                    /* HTX = 1: Slave in write state; */
                    if(_htx == 1)
                    {
                        /* RXAKn = 1: Master stop receiving
                           next byte,master releases scl bus */
                        if(_rxak == 1)
                        {
                            _htx = 0;
                            _txak = 0;

                            /* Dummy read from SIMD to release SCL line */
                            g_USIM_SIM_Rx_Buf = _simd;
                        }
                        /* RXAK = 0: Master wants to receive next byte */
                        else
                        {

                            #ifdef  _DEMO
                                    /* In DEMO,the transmit data is the receive data */
                                    g_USIM_SIM_Tx_Buf = g_USIM_SIM_Rx_Buf;
                            #endif

                            /* Send data, User can program here */
                            _simd = g_USIM_SIM_Tx_Buf;
                        }
                    }
                    /* HTX = 0: Slave in read state */
                    else
                    {
                        /* Read data, User can program here  */
                        g_USIM_SIM_Rx_Buf = _simd;
                    }
                }
            }
            /* USIM I2C communication timeout */
            else
            {
                _simtof = 0;
                _simtoen = 1;
                /* User define,such as set a I2C timeout flag */

            }

    #elif   USIM_SPI_Slave

            /* Check USIMn SPI data transfer completed? */
            while(USIM_SPI_TRX_FLAG == 0)
            {
                GCC_CLRWDT();
            }

            /* USIM SPI incomplete condition is not occurred */
            if(!_simicf)
            {
                g_USIM_SIM_Rx_Buf = _simd;/*Read data, User can program here */
            }
            /* USIM SPI incomplete condition is occurred */
            else
            {
                _simicf = 0;
                /* User define,such as set a SPI incomplete condition flag */
            }
            USIM_SPI_TRX_FLAG = 0;          /*Clear TRF*/

            do
            {
                USIM_SPI_WRITE_COLLISION_FLAG = 0;

                #ifdef  _DEMO
                        /* In DEMO, the transmit data is the receive data */
                        g_USIM_SIM_Tx_Buf = g_USIM_SIM_Rx_Buf;
                #endif

                /* Write data to SIMnD, the data will be
                   transmit next interrupt, User can program here*/
                _simd = g_USIM_SIM_Tx_Buf;

                GCC_CLRWDT();

            }while(USIM_SPI_WRITE_COLLISION_FLAG == 1);/*Check SPI write collision*/

    #elif   USIM_UART
            g_USIM_UART_ISR_Value[0] = 0;
            g_USIM_UART_ISR_Value[1] = 0;
            g_USIM_UART_err_Flag = 0;

            #ifdef  _DEMO
                    g_USIM_UART_RX_FLAG = 1;
            #endif

            /* Check USIM UART Parity error flag */
            #ifdef  USIM_UART_EVENPR_MODE
                    if(_uperr)
                    {
                        /* Even parity error, user can set error flag in here */
                        g_USIM_UART_err_Flag |= 0x80;
                    }
            #endif
                        /* The end of Check USIM UART Parity error flag */

            /* Check USIM UART Parity error flag */
            #ifdef  USIM_UART_ODDPR_MODE
                    if(_uperr)
                    {
                        /* Odd parity error,user can set error flag in here */
                        g_USIM_UART_err_Flag |= 0x80;
                    }
            #endif
            /* The end of Check USIM UART Parity error flag */

            /* Check USIM UART Noise error flag */
            #ifdef  USIM_UART_NF_MODE
                    if(_unf)
                    {
                        /* Noise error,user can set error flag in here */
                        g_USIM_UART_err_Flag |= 0x40;
                    }
            #endif
            /* The end of Check USIM UART Noise error flag */

            /* Check USIM UART Framing error flag */
            #ifdef  USIM_UART_FERR_MODE
                    if(_uferr)
                    {
                        /* Framing error,user can set error flag in here */
                        g_USIM_UART_err_Flag |= 0x20;
                    }
            #endif
            /* The end of Check USIM UART Framing error flag */

            /* Check USIM UART Overrun error flag */
            #ifdef  USIM_UART_OERR_MODE
                    if(_uoerr)
                    {
                        /* Overrun error,user can set error flag in here */
                        g_USIM_UART_err_Flag |= 0x10;
                    }
            #endif
            /* The end of Check USIM UART Overrun error flag */

            #if defined(USIM_UART_EVENPR_MODE) || defined(USIM_UART_ODDPR_MODE)\
                 || defined(USIM_UART_NF_MODE) || defined(USIM_UART_FERR_MODE)\
                 || defined(USIM_UART_OERR_MODE)
                    if (g_USIM_UART_err_Flag & 0xf0)
                    {
                        /* Read UUSR and UTXR_RXR register to clear error flag */
                        _acc = _uusr;
                        _acc = _utxr_rxr;

                        /* Clear the first receive data buffer */
                        g_USIM_UART_ISR_Value[0] = 0;
                        /* Clear the second receive data buffer */
                        g_USIM_UART_ISR_Value[1] = 0;

                        return;
                    }
            #endif

            /* USIM UART Receive data success */
            if(_urxif)
            {
                #ifdef  USIM_UART_NINE_BIT_MODE
                        #if defined(USIM_UART_EVENPR_MODE) ||\
                         defined(USIM_UART_ODDPR_MODE)
                                /* First Byte, MSB is parity bit */
                                g_USIM_UART_ISR_Value[0] = _utxr_rxr;

                        #elif   USIM_UART_PARITY_DISABLE
                                if(_urx8 == 1)
                                {
                                    _acc = _uusr;
                                    /* First Byte, MSB = 1 is data bit */
                                    g_USIM_UART_ISR_Value[0] = _utxr_rxr + 256;
                                }
                                else
                                {
                                    _acc = _uusr;
                                    /* First Byte, MSB = 0 is data bit */
                                    g_USIM_UART_ISR_Value[0] = _utxr_rxr;
                                }
                        #endif

                        if(_urxif)
                        {
                            #if defined(USIM_UART_EVENPR_MODE) ||\
                             defined(USIM_UART_ODDPR_MODE)
                                    /* Second Byte, MSB is parity bit */
                                    g_USIM_UART_ISR_Value[1] = _utxr_rxr;

                            #elif   USIM_UART_PARITY_DISABLE
                                    if(_urx8 == 1)
                                    {
                                        _acc = _uusr;
                                        /* Second Byte, MSB = 1 is data bit */
                                        g_USIM_UART_ISR_Value[1] = _utxr_rxr + 256;
                                    }
                                    else
                                    {
                                        _acc = _uusr;
                                        /* Second Byte, MSB = 0 is data bit */
                                        g_USIM_UART_ISR_Value[1] = _utxr_rxr;
                                    }
                            #endif
                        }
                #elif   USIM_UART_EIGHT_BIT_MODE
                        _acc = _uusr;
                        g_USIM_UART_ISR_Value[0] = _utxr_rxr;       /*First Byte*/

                        if(_urxif)
                        {
                            _acc = _uusr;
                            g_USIM_UART_ISR_Value[1] = _utxr_rxr;   /*Second Byte*/
                        }
                #endif
            }
            /* The end of USIM UART Receive data success */

    #endif

}

/*******************************************************************************
  * @brief    USIM UART initialization function.
  * @param    BaudRate: Raud rate value
  *           the BaudRate value range is 0 ~ 255.
  * @retval   None
 *******************************************************************************/
/*
PS:If Fsys = 16MHz, BaudRate input values reference table.
   -------------------------------------------------------------------
   | Baud Rate values | 4800 | 9600 | 19200 | 38400 | 57600 |115200|
   -------------------------------------------------------------------
   | High speed Mode  | 0xcf | 0x67 |  0x33 |  0x19 |  0x10 | 0x08 |
   | Error            | 0.16%| 0.16%| 0.16% | 0.16% |  2.1% |-3.5% |
   -------------------------------------------------------------------
   | Low speed Mode   | 0x33 | 0x19 | 0x0c  |  ---- |  ---- |
   | Error            | 0.16%| 0.16%| 0.16% |  ---- |  ---- |
   -------------------------------------------------------------------
PS:If Fsys = 12MHz, BaudRate input values reference table.
   -------------------------------------------------------------------
   | Baud Rate values | 4800 | 9600 | 19200 | 38400 | 57600 |115200|
   -------------------------------------------------------------------
   | High speed Mode  | 0x9b | 0x4d |  0x26 |  0x13 |  0x0c | ---- |
   | Error            | 0.16%| 0.16%| 0.16% | -2.3% | 0.16% | ---- |
   -------------------------------------------------------------------
   | Low speed Mode   | 0x26 | 0x13 | 0x09  |  0x04 |  ---- | ---- |
   | Error            | 0.16%|-2.3% |-2.3%  | -2.3% |  ---- | ---- |
   -------------------------------------------------------------------
PS:If Fsys = 8MHz, BaudRate input values reference table.
   -------------------------------------------------------------------
   | Baud Rate values | 4800 | 9600 | 19200 | 38400 | 57600 |
   -------------------------------------------------------------------
   | High speed Mode  | 0x67 | 0x33 |  0x19 |  0x0c |  0x08 |
   | Error            | 0.16%| 0.16%| 0.16% | 0.16% | -3.5% |
   -------------------------------------------------------------------
   | Low speed Mode   | 0x19 | 0x0c |  ---- |  ---- |  ---- |
   | Error            | 0.16%| 0.16%|
   -------------------------------------------------------------------
*/
void USIM_UART_Init(u8 BaudRate)
{
    _umd = 1;                   /*USIM UART mode is selected*/
/*==================== USIM UART operating mode control ======================*/
    #ifdef  USIM_UART_NORMAL_MODE
            _uswm = 0;

    #elif   USIM_UART_SINGLE_WIRE_MODE
            _uswm = 1;

    #endif
/*=============== The end of USIM UART operating mode control ================*/

/*=================== USIM UART Parity function control ======================*/
    #ifdef  USIM_UART_EVENPR_MODE
            /* USIM UART Parity function enable, Parity type is Even parity */
            _upren = 1; _uprt = 0;

    #elif   USIM_UART_ODDPR_MODE
            /* USIM UART Parity function enable, Parity type is Odd parity */
            _upren = 1; _uprt = 1;

    #elif   USIM_UART_PARITY_DISABLE
            /* USIM UART Parity function disable */
            _upren = 0;

    #endif
/*============== The end of USIM UART Parity function control ================*/

/*============= Number of USIM UART data transfer bits control ===============*/
    #ifdef  USIM_UART_NINE_BIT_MODE
            _ubno = 1;          /*USIM UART select 9-bit data transfer*/

    #elif   USIM_UART_EIGHT_BIT_MODE
            _ubno = 0;          /*USIM UART select 8-bit data transfer*/

    #endif

/*======= The end of  Number of USIM UART data transfer bits control =========*/

/*=================== USIM UART Baud rate speed control ======================*/
    #ifdef  USIM_UART_HS_BR_MODE
            _ubrgh = 1;         /*USIM UART select High speed baud rate*/

    #elif   USIM_UART_LS_BR_MODE
            _ubrgh = 0;         /*USIM UART select Low speed baud rate*/

    #endif

/*============== The end of USIM UART Baud rate speed control ================*/

/*================ TX Number of USIM UART stop bits control ==================*/
    #ifdef  USIM_UART_TWO_STOPS_MODE
            _ustops = 1;        /*USIM UART select Two stop bits format*/

    #elif   USIM_UART_ONE_STOP_MODE
            _ustops = 0;        /*USIM UART select One stop bit format*/

    #endif

/*=========== The end of TX Number of USIM UART stop bits control ============*/

    _ubrg = BaudRate;           /*USIM UART Baud Rate values config*/

}


/*******************************************************************************
  * @brief    USIM UART transmit function.
  * @param    data: Transmit data
  *           the data value range is 0 ~ 511.
  * @retval   None
 *******************************************************************************/
void USIM_UART_Transmit(u16 data)
{
    if(_uswm)
    {
        _utxen = 1;
        _urxen = 0;     /*if set single wire mode, first set to transmit mode*/
    }

    _utx8 = 0;          /*Initialization*/
    
    /* Waitting USIM UART transmitter free */
    while(!_utxif)
    {
        _nop();
    }
    /* The end of waitting USIM UART transmitter free */

    /* Write data to USIM UART transmitter */
    #ifdef  USIM_UART_NINE_BIT_MODE
            #if defined(USIM_UART_EVENPR_MODE) || defined(USIM_UART_ODDPR_MODE)
                    _utxr_rxr = data;   /*MSB is the parity bit*/

            #elif   USIM_UART_PARITY_DISABLE
                    if( data > 255)
                    {
                        _utx8 = 1;      /*MSB is the data bit*/
                    }
                    _utxr_rxr = data & 0x00ff;

            #endif

    #elif   USIM_UART_EIGHT_BIT_MODE
            _utxr_rxr = data & 0x00ff;

    #endif
    /* The end of write data to USIM UART transmitter */

    /* Waitting USIM UART transmit data finished */
    while(!_utidle)
    {
        _nop();
    }
    /* The end of waitting USIM UART transmit data finished */

    if(_uswm)
    {
        /* if set single wire mode and transmit finished, set to receive mode */
        _utxen = 0;
        _urxen = 1;
    }
}



/*********** (C) COPYRIGHT 2019 Holtek Semiconductor Inc **********END OF FILE*/
