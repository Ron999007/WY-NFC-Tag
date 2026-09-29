/*******************************************************************************
  * @file     HT8_SW_SPI_Master.c
  * @brief    This file provides all the S/W SPI Master firmware functions.
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

/* Includes-------------------------------------------------------------------*/
#include "HT8_SW_SPI_Master.h"

/*******************************************************************************
  * @brief    S/W SPI Master initialization function.
  * @param    None
  * @retval   None
 *******************************************************************************/
void SW_SPI_Master_Init(void)
{
    SCSB_C = 0;
    SCSB = 1;

    SCK_C = 0;

    #if defined(SW_SPI_SCK_HIGH_RISING_EDGE) | defined(SW_SPI_SCK_HIGH_FALLING_EDGE)

        SCK = 1;

    #elif   defined(SW_SPI_SCK_LOW_FALLING_EDGE) | defined(SW_SPI_SCK_LOW_RISING_EDGE)

        SCK = 0;

    #endif

    SDO_C = 0;
    SDO = 1;

    SDI_C = 1;

}


/*******************************************************************************
  * @brief    S/W SPI Master transmit 1-byte data and receive 1-byte data function.
  * @param    TX_Data: the data that will be transmitted.
  * @retval   The data which is received.
 *******************************************************************************/
u8 SW_SPI_Master_Send_Data(u8 TX_Data)
{
    u8 i;
    u8 Rx_Data =0;

    #if defined(SW_SPI_SCK_HIGH_RISING_EDGE) | defined(SW_SPI_SCK_HIGH_FALLING_EDGE)

        SCK = 1;

    #elif defined(SW_SPI_SCK_LOW_FALLING_EDGE) | defined(SW_SPI_SCK_LOW_RISING_EDGE)

        SCK = 0;

    #endif

    GCC_DELAY(t_DELAY);

    for (i = 0; i < 8; i ++)
    {
        #if defined(SW_SPI_SCK_LOW_FALLING_EDGE)

            SCK = 1;

        #elif defined(SW_SPI_SCK_HIGH_RISING_EDGE)

            SCK = 0;

        #endif

        #ifdef SW_SPI_MSB_FIRST

            if (TX_Data & 0x80)

                SDO = 1;

            else

                SDO = 0;

        #elif SW_SPI_LSB_FIRST

            if (TX_Data & 0x01)

                SDO = 1;

            else

                SDO = 0;

        #endif

        #if defined(SW_SPI_SCK_HIGH_FALLING_EDGE)

            SCK = 1;

        #elif defined(SW_SPI_SCK_LOW_RISING_EDGE)

            SCK = 0;

        #endif

        #ifdef SW_SPI_MSB_FIRST

            TX_Data = TX_Data << 1;

        #elif SW_SPI_LSB_FIRST

            TX_Data = TX_Data >> 1;

        #endif

        #if defined(SW_SPI_SCK_LOW_RISING_EDGE)

            #if (t_SU1 != 0)

                GCC_DELAY(t_SU1);

            #endif

            SCK = 1;

        #endif

        #if defined(SW_SPI_SCK_HIGH_FALLING_EDGE)

            #if (t_SU1 != 0)

                GCC_DELAY(t_SU1);

            #endif

            SCK = 0;

        #endif

        #if defined(SW_SPI_SCK_LOW_FALLING_EDGE) | defined(SW_SPI_SCK_HIGH_RISING_EDGE)

            #if (t_HD2 != 0)

                GCC_DELAY(t_HD2);

            #endif

        #endif

        #if defined(SW_SPI_SCK_HIGH_RISING_EDGE)

            SCK = 1;

        #elif defined(SW_SPI_SCK_LOW_FALLING_EDGE)

            SCK = 0;

        #endif

        if (1 == SDI)
        {
            #ifdef SW_SPI_MSB_FIRST

                Rx_Data |= (0x80 >> i);

            #elif SW_SPI_LSB_FIRST

                Rx_Data |= (0x01 << i);

            #endif
        }

        #if defined(SW_SPI_SCK_LOW_RISING_EDGE)

            #if (t_HD1 != 0)

                GCC_DELAY(t_HD1);

            #endif

        #endif

        #if defined(SW_SPI_SCK_HIGH_FALLING_EDGE)

            SCK = 0;

            #if (t_HD1 != 0)

                GCC_DELAY(t_HD1);

            #endif

        #endif

        #if defined(SW_SPI_SCK_LOW_FALLING_EDGE) | defined(SW_SPI_SCK_HIGH_RISING_EDGE)

            #if (t_SU2 != 0)

                GCC_DELAY(t_SU2);

            #endif

        #endif

    }

    #if defined(SW_SPI_SCK_HIGH_RISING_EDGE) | defined(SW_SPI_SCK_HIGH_FALLING_EDGE)

        GCC_DELAY(t_SU1);
        SCK = 1;

    #elif defined(SW_SPI_SCK_LOW_FALLING_EDGE) | defined(SW_SPI_SCK_LOW_RISING_EDGE)

        GCC_DELAY(t_SU1);
        SCK = 0;

    #endif

    return Rx_Data;

}




/*********** (C) COPYRIGHT 2019 Holtek Semiconductor Inc **********END OF FILE*/
