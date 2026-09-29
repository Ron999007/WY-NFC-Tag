/*******************************************************************************
  * @file     HT8_SW_I2C_Master.c
  * @brief    This file provides all the S/W I2C Master firmware functions.
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
#include "HT8_SW_I2C_Master.h"

/*******************************************************************************
  * @brief    S/W I2C Master initialization function.
  * @param    None
  * @retval   None
 *******************************************************************************/
void SW_I2C_Master_Init(void)
{
    SCL_C = 1;
    SDA_C = 1;

    #ifdef  Internal_PU
            SCL_PU = 1;
            SDA_PU = 1;

    #elif   External_PU
            SCL_PU = 0;
            SDA_PU = 0;

    #endif
}


/*******************************************************************************
  * @brief    S/W I2C Master Start function.
  * @param    None
  * @retval   BUSY or IDLE
 *******************************************************************************/
I2C_ACK_Flag SW_I2C_Send_Start(void)
{
    /* Start: check bus status */
    SCL_C = 1;
    SDA_C = 1;
    u8 timeout = 0;
    u8 CNT=0;
    while(CNT < CHECKCNT)
    {
        while(!(SCL && SDA))
        {
            timeout++;
            if(timeout > TIMEOUT)
                return BUSY;
        }
        CNT++;
    }
    /* End: check bus status */

    SCL = 1;
    SCL_C = 0;
    SCL = 1;

    SDA = 1;
    SDA_C = 0;
    SDA = 1;

    GCC_DELAY(t_SU_STO);

    SCL = 1;
    SCL_C = 0;
    SCL = 1;

    GCC_DELAY(t_SU_STO);
    SDA_C = 0;
    SDA = 1;
    GCC_DELAY(t_BUF);

    SDA_LOW();
    GCC_DELAY(t_HD_STA);
    SCL_LOW();

    return IDLE;
}


/*******************************************************************************
  * @brief    S/W I2C Master Stop function.
  * @param    None
  * @retval   BUSY or IDLE
 *******************************************************************************/
I2C_ACK_Flag SW_I2C_Send_Stop(void)
{
    SCL_LOW();

    SDA_LOW();
    SCL_HIGH();

    /* Start: check bus status */
    u8 timeout = 0;
    u8 CNT=0;
    while(CNT < CHECKCNT)
    {
        while(!SCL)
        {
            timeout++;
            if(timeout > TIMEOUT)
                return BUSY;
        }
        CNT++;
    }
    /* End: check bus status */

    GCC_DELAY(t_SU_STO);
    SDA_HIGH();
    GCC_DELAY(t_BUF);

    SCL_C = 1;
    SDA_C = 1;

    return IDLE;
}


/*******************************************************************************
  * @brief    S/W I2C Master transmit 1-byte data and receive acknowledge function.
  * @param    data: the data that will be transmitted.
  * @retval   The acknowledge flag receive from I2C bus.
  *           The acknowledge flag or BUSY can have one of the values of @ref I2C_ACK_Flag
 *******************************************************************************/
I2C_ACK_Flag SW_I2C_Send_Data(u8 data)
{
    u8 temp = 0b10000000;
    u8 timeout = 0;

    SCL_LOW();

    if (data & temp)
        SDA_HIGH();
    else
        SDA_LOW();

    #if (P_RATIO == 0)
        GCC_DELAY(t_LOW);
    #else
        GCC_DELAY(t_LOW_OS);
    #endif

    SCL_HIGH();
    GCC_DELAY(t_HIGH);

    /* Start: check bus status */
    u8 CNT=0;
    while(CNT < CHECKCNT)
    {
        while(!SCL)
        {
            timeout++;
            if(timeout > TIMEOUT)
                return BUSY;
        }
        CNT++;
    }
    /* End: check bus status */

    #if (P_RATIO == 0)
        GCC_DELAY(t_HIGH);
    #else
        GCC_DELAY(t_HIGH_OS);
    #endif

    temp >>= 1; 

    do
    {
        SCL_LOW();

        if (data & temp)
            SDA_HIGH();
        else
            SDA_LOW();

        #if (P_RATIO == 0)
            GCC_DELAY(t_LOW);
        #else
            GCC_DELAY(t_LOW_OS);
        #endif

        SCL_HIGH();
        GCC_DELAY(t_HIGH);

        #if (P_RATIO == 0)
            GCC_DELAY(t_HIGH);
        #else
            GCC_DELAY(t_HIGH_OS);
        #endif

        temp >>= 1; 
    }while(temp != 0);

    GCC_NOP();

    I2C_ACK_Flag ack_status = NACK;

    SCL_LOW();
    GCC_DELAY(t_LOW1);
    SDA_C = 1;
    GCC_DELAY(t_LOW2);

    SCL_HIGH();

    /* Start: clock stretching */
    CNT=0;
    while(CNT < CHECKCNT)
    {
        while(!SCL)
        {
            timeout++;
            if(timeout > TIMEOUT)
                return BUSY;
        }
        CNT++;
    }
    /* End: clock stretching */

    if(!SDA)
    {
        ack_status = ACK;
    }

    GCC_DELAY(t_HIGH1);
    GCC_DELAY(t_HIGH2);

    SCL_LOW();

    return ack_status;
}


/*******************************************************************************
  * @brief    S/W I2C Master transmit Slave address and receive acknowledge flag function.
  * @param    slave_addr: the Slave address that will be transmitted. 
  *           The slave_addr range is 0x00 ~ 0xFF,
  *           but only Bits 7~ 1 is used to define the device slave address.
  * @param    slave_mode: I2C Slave device is transmitter or receiver selection 
  *           slave_mode can have one of the values of @ref I2C_Slave_Mode_TypeDef
  * @retval   The acknowledge flag receive from I2C bus.
  *           The acknowledge flag or BUSYcan have one of the values of @ref I2C_ACK_Flag
 *******************************************************************************/
I2C_ACK_Flag SW_I2C_Send_Addr(u8 slave_addr,u8 slave_mode)
{
    return SW_I2C_Send_Data((slave_addr & 0xfe)|slave_mode);
}


/*******************************************************************************
  * @brief    S/W I2C Master receive 1-byte data and response acknowledge function.
  * @param    tx_ack: Response acknowledge flag or non-acknowledge flag
  *           tx_ack can have one of the values of @ref I2C_ACK_Flag
  * @retval   The data receive from I2C bus or BUSY.
 *******************************************************************************/
u8 SW_I2C_Receive_Data(I2C_ACK_Flag tx_ack)
{
    u8 I2C_data = 0;
    u8 timeout = 0;
    I2C_ACK_Flag ack_flag = tx_ack;
    u8 temp = 0b10000000;

    SCL_LOW();
    SDA_C = 1;

    GCC_DELAY(t_LOW);
    GCC_NOP();

    #if (P_RATIO == 0)
        GCC_DELAY(t_LOW);
    #else
        GCC_DELAY(t_LOW_OS);
    #endif

    SCL_HIGH();

    /* Start: check bus status */
    u8 CNT=0;
    while(CNT < CHECKCNT)
    {
        while(!SCL)
        {
            timeout++;
            if(timeout > TIMEOUT)
                return BUSY;
        }
        CNT++;
    }
    /* End: check bus status */

    if (1 == SDA)
        I2C_data |= temp; 

    #if (P_RATIO == 0)
        GCC_DELAY(t_HIGH);
    #else
        GCC_DELAY(t_HIGH_OS);
    #endif

    temp >>= 1;

    SCL_LOW();

    do
    {
        GCC_DELAY(t_LOW);
        GCC_NOP();

        #if (P_RATIO == 0)
            GCC_DELAY(t_LOW);
        #else
            GCC_DELAY(t_LOW_OS);
        #endif

        SCL_HIGH();
        GCC_NOP();
        GCC_NOP();
        GCC_NOP();

        if (1 == SDA)
            I2C_data |= temp; 

        #if (P_RATIO == 0)
            GCC_DELAY(t_HIGH);
        #else
            GCC_DELAY(t_HIGH_OS);
        #endif

        temp >>= 1;

        SCL_LOW();
    }while(temp != 0);

    if(!ack_flag)
    {
        SDA_LOW();

        #if (t_LOW3 > 2)
            GCC_DELAY((t_LOW3-2));
        #endif
    }
    else
    {
        SDA_HIGH();

        #if (t_LOW3!=0)
            GCC_DELAY(t_LOW3);
        #endif
    }

    SCL_HIGH();

    /* Start: clock stretching */
    CNT=0;
    while(CNT < CHECKCNT)
    {
        while(!SCL)
        {
            timeout++;
            if(timeout > TIMEOUT)
                return BUSY;
        }
        CNT++;
    }
    /* End: clock stretching */

    GCC_DELAY(t_HIGH1);
    GCC_NOP();
    GCC_NOP();
    GCC_DELAY(t_HIGH2);

    SCL_LOW();

    return I2C_data;
}


/*********** (C) COPYRIGHT 2019 Holtek Semiconductor Inc **********END OF FILE*/
