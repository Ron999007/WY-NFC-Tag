/*******************************************************************************
  * @file     HT8_EEPROM.c
  * @brief    This file provides all the EEPROM firmware functions.
  * @author   Holtek Semiconductor Inc.
  * @version  V1.0.0
  * @date     2024-6-17
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
#include "HT8_EEPROM.h"

/*******************************************************************************
  * @brief    EEPROM write byte function.
  * @param    Data: The data you want to write to EEPROM.
  *           It can be 0x00 ~ 0xff.
  * @param    adr: Specifies EEPROM address.
  *           It can be 0x00 ~ 0xff.
  * @retval   None
 *******************************************************************************/
void EEPROM_Write_Byte(u8 Data,u8 adr)
{
    u8 TempEMI;

    TempEMI = _emi;

    _mp2h = 1;
    _mp2l = 0x40;
    _iar2 &= 0x0f;

    _eea = adr;                 /*Config EEPROM address*/
    _eed = Data;                /*Write data*/

    _emi = 0;                   /*Disable global interrupt*/

    _iar2 |= 0x08;              /*Enable write operations*/
    _iar2 |= 0x04;              /*Start write cycle*/

    _emi = TempEMI;             /*Resume global interrupt setting*/

    while(_iar2 & 0x04);        /*Check for write cycle end*/

    _iar2 = 0;
    _mp2h = 0;
    _mp2l = 0;
    _eea = 0;

    return;
}


/*******************************************************************************
  * @brief    EEPROM read byte function.
  * @param    adr: Specifies EEPROM address that you want to read.
  *           It can be 0x00 ~ 0xff.
  * @retval   EEPROM data.
 *******************************************************************************/
u8 EEPROM_Read_Byte(u8 adr)
{
    u8 EP_Read_Data;

    _mp2h = 1;
    _mp2l = 0x40;
    _iar2 &= 0x0f;

    _eea = adr;                 /*Config EEPROM address*/

    _iar2 |= 0x02;              /*Enable read operations*/
    _iar2 |= 0x01;              /*Start read cycle*/

    while(_iar2 & 0x01);        /*Check for read cycle end*/

    _iar2 = 0;
    _mp2h = 0;
    _mp2l = 0;
    _eea = 0;

    EP_Read_Data =_eed;         /*Read data*/
    return EP_Read_Data; 
}

/************************ (C) COPYRIGHT 2020 Holtek Semiconductor Inc ************************END OF FILE****/
