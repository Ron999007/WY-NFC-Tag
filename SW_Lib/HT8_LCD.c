/*******************************************************************************
  * @file     HT8_LCD.c
  * @brief    This file provides all the LCD firmware functions.
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
#include "HT8_LCD.h"

volatile u8 g_u8ScanCNT;
volatile _byte8 g_u8DspRam[Scan_RAM_Total_Byte];
volatile  u8 g_u8SegBuf[LCD_RAM_Total_Byte]; 

/* It needs to be modified according to the 
   actual situation for SEVEN_SEG_DISPLAY */
const unsigned char Trans_Segment[]=\
{0xf5,0x60,0xb6,0xf2,0x63,0xd3,0xd7,0x70,0xf7,0xf3};    /*Display 0-9*/

/*******************************************************************************
  * @brief    LCD initialization function.
  * @param    None
  * @retval   None
 *******************************************************************************/
void LCD_Init(void)
{
/*========================= Select LCD bias current ==========================*/

    #ifdef  I_BIAS_25
        _isel1 = 0; _isel0 = 0;     /*IBIAS = 25£gA@(VDD=5V)*/

    #elif   I_BIAS_50
        _isel1 = 0; _isel0 = 1;     /*IBIAS = 50£gA@(VDD=5V)*/

    #elif   I_BIAS_100
        _isel1 = 1; _isel0 = 0;     /*IBIAS = 100£gA@(VDD=5V)*/

    #elif   I_BIAS_200
        _isel1 = 1; _isel0 = 1;     /*IBIAS = 200£gA@(VDD=5V)*/

    #endif

/*=================== The end of Select LCD bias current =====================*/

    CLR_LCD_RAM();

    LCD_COM_SEG_Init();

}


/*******************************************************************************
  * @brief    Clear LCD RAM function.
  * @param    None
  * @retval   None
 *******************************************************************************/
void CLR_LCD_RAM(void)
{
    u8 i;

    for (i = 0; i < LCD_RAM_Total_Byte; i++)
    {
        g_u8SegBuf[i] = 0x00;
    }
}


/*******************************************************************************
  * @brief    LCD COM and SEG status initialization function.
  * @param    None
  * @retval   None
 *******************************************************************************/
void LCD_COM_SEG_Init(void)
{
    /* Initial COM status */
    #ifdef  COM0_USED
        COM0_BIAS;
    #endif

    #ifdef  COM1_USED
        COM1_BIAS;
    #endif

    #ifdef  COM2_USED
        COM2_BIAS;
    #endif

    #ifdef  COM3_USED
        COM3_BIAS;
    #endif


    /* Initial SEG status */
    #ifdef  SEG0_USED
        SEG0 = 1;
    #endif

    #ifdef  SEG1_USED
        SEG1 = 1;
    #endif

    #ifdef  SEG2_USED
        SEG2 = 1;
    #endif

    #ifdef  SEG3_USED
        SEG3 = 1;
    #endif

    #ifdef  SEG4_USED
        SEG4 = 1;
    #endif

    #ifdef  SEG5_USED
        SEG5 = 1;
    #endif

    #ifdef  SEG6_USED
        SEG6 = 1;
    #endif

    #ifdef  SEG7_USED
        SEG7 = 1;
    #endif

    #ifdef  SEG8_USED
        SEG8 = 1;
    #endif

    #ifdef  SEG9_USED
        SEG9 = 1;
    #endif

    #ifdef  SEG10_USED
        SEG10 = 1;
    #endif

    #ifdef  SEG11_USED
        SEG11 = 1;
    #endif

    #ifdef  SEG12_USED
        SEG12 = 1;
    #endif

    #ifdef  SEG13_USED
        SEG13 = 1;
    #endif

    #ifdef  SEG14_USED
        SEG14 = 1;
    #endif

    #ifdef  SEG15_USED
        SEG15 = 1;
    #endif

    #ifdef  SEG16_USED
        SEG16 = 1;
    #endif

    #ifdef  SEG17_USED
        SEG17 = 1;
    #endif

    #ifdef  SEG18_USED
        SEG18 = 1;
    #endif

    #ifdef  SEG19_USED
        SEG19 = 1;
    #endif

    #ifdef  SEG20_USED
        SEG20 = 1;
    #endif

    #ifdef  SEG21_USED
        SEG21 = 1;
    #endif

    #ifdef  SEG22_USED
        SEG22 = 1;
    #endif

    #ifdef  SEG23_USED
        SEG23 = 1;
    #endif

    #ifdef  SEG24_USED
        SEG24 = 1;
    #endif

    #ifdef  SEG25_USED
        SEG25 = 1;
    #endif


}


/*******************************************************************************
  * @brief    LCD COM Scan function.
  * @param    None
  * @retval   None
 *******************************************************************************/
void LCD_COM_Scan(void)
{
    switch(g_u8ScanCNT)
    {
        #if (COM_NUM == 1)

            case 0  : COM0_VDD; break;              //COM0 scan: VDD
            case 1  : COM0_VSS; break;              //COM0 scan: VSS

        #elif   (COM_NUM == 2)

            case 0  : COM1_BIAS;COM0_VDD;   break;      //COM0 scan: VDD
            case 1  : COM0_VSS; break;              //COM0 scan: VSS
            case 2  : COM0_BIAS;COM1_VDD;   break;      //COM1 scan: VDD
            case 3  : COM1_VSS; break;              //COM1 scan: VSS

        #elif   (COM_NUM == 3)

            case 0  : COM2_BIAS;COM0_VDD;   break;      //COM0 scan: VDD
            case 1  : COM0_VSS; break;              //COM0 scan: VSS
            case 2  : COM0_BIAS;COM1_VDD;   break;      //COM1 scan: VDD
            case 3  : COM1_VSS; break;              //COM1 scan: VSS
            case 4  : COM1_BIAS;COM2_VDD;   break;      //COM2 scan: VDD
            case 5  : COM2_VSS; break;              //COM2 scan: VSS

        #elif   (COM_NUM == 4)

            case 0  : COM3_BIAS;COM0_VDD;   break;      //COM0 scan: VDD
            case 1  : COM0_VSS; break;              //COM0 scan: VSS
            case 2  : COM0_BIAS;COM1_VDD;   break;      //COM1 scan: VDD
            case 3  : COM1_VSS; break;              //COM1 scan: VSS
            case 4  : COM1_BIAS;COM2_VDD;   break;      //COM2 scan: VDD
            case 5  : COM2_VSS; break;              //COM2 scan: VSS
            case 6  : COM2_BIAS;COM3_VDD;   break;      //COM3 scan: VDD
            case 7  : COM3_VSS; break;              //COM3 scan: VSS

        #endif

    }
}


/*******************************************************************************
  * @brief    LCD SEG Scan function.
  * @param    None
  * @retval   None
 *******************************************************************************/
void LCD_SEG_Scan(void)
{
    #if (COM_NUM <= 2)
    {
        if (!(g_u8ScanCNT % 2))
        {
            #ifdef  SEG0_USED
                if(g_u8DspRam[0].bits.bit0) SEG0 = 0;   else SEG0 = 1;
            #endif

            #ifdef  SEG1_USED
                if(g_u8DspRam[0].bits.bit1) SEG1 = 0;   else SEG1 = 1;
            #endif

            #ifdef  SEG2_USED
                if(g_u8DspRam[0].bits.bit2) SEG2 = 0;   else SEG2 = 1;
            #endif

            #ifdef  SEG3_USED
                if(g_u8DspRam[0].bits.bit3) SEG3 = 0;   else SEG3 = 1;
            #endif

            #ifdef  SEG4_USED
                if(g_u8DspRam[0].bits.bit4) SEG4 = 0;   else SEG4 = 1;
            #endif

            #ifdef  SEG5_USED
                if(g_u8DspRam[0].bits.bit5) SEG5 = 0;   else SEG5 = 1;
            #endif

            #ifdef  SEG6_USED
                if(g_u8DspRam[0].bits.bit6) SEG6 = 0;   else SEG6 = 1;
            #endif

            #ifdef  SEG7_USED
                if(g_u8DspRam[0].bits.bit7) SEG7 = 0;   else SEG7 = 1;
            #endif

            #ifdef  SEG8_USED
                if(g_u8DspRam[1].bits.bit0) SEG8 = 0;   else SEG8 = 1;
            #endif

            #ifdef  SEG9_USED
                if(g_u8DspRam[1].bits.bit1) SEG9 = 0;   else SEG9 = 1;
            #endif

            #ifdef  SEG10_USED
                if(g_u8DspRam[1].bits.bit2) SEG10 = 0;  else SEG10 = 1;
            #endif

            #ifdef  SEG11_USED
                if(g_u8DspRam[1].bits.bit3) SEG11 = 0;  else SEG11 = 1;
            #endif

            #ifdef  SEG12_USED
                if(g_u8DspRam[1].bits.bit4) SEG12 = 0;  else SEG12 = 1;
            #endif

            #ifdef  SEG13_USED
                if(g_u8DspRam[1].bits.bit5) SEG13 = 0;  else SEG13 = 1;
            #endif

            #ifdef  SEG14_USED
                if(g_u8DspRam[1].bits.bit6) SEG14 = 0;  else SEG14 = 1;
            #endif

            #ifdef  SEG15_USED
                if(g_u8DspRam[1].bits.bit7) SEG15 = 0;  else SEG15 = 1;
            #endif

            #ifdef  SEG16_USED
                if(g_u8DspRam[2].bits.bit0) SEG16 = 0;  else SEG16 = 1;
            #endif

            #ifdef  SEG17_USED
                if(g_u8DspRam[2].bits.bit1) SEG17 = 0;  else SEG17 = 1;
            #endif

            #ifdef  SEG18_USED
                if(g_u8DspRam[2].bits.bit2) SEG18 = 0;  else SEG18 = 1;
            #endif

            #ifdef  SEG19_USED
                if(g_u8DspRam[2].bits.bit3) SEG19 = 0;  else SEG19 = 1;
            #endif

            #ifdef  SEG20_USED
                if(g_u8DspRam[2].bits.bit4) SEG20 = 0;  else SEG20 = 1;
            #endif

            #ifdef  SEG21_USED
                if(g_u8DspRam[2].bits.bit5) SEG21 = 0;  else SEG21 = 1;
            #endif

            #ifdef  SEG22_USED
                if(g_u8DspRam[2].bits.bit6) SEG22 = 0;  else SEG22 = 1;
            #endif

            #ifdef  SEG23_USED
                if(g_u8DspRam[2].bits.bit7) SEG23 = 0;  else SEG23 = 1;
            #endif

            #ifdef  SEG24_USED
                if(g_u8DspRam[3].bits.bit0) SEG24 = 0;  else SEG24 = 1;
            #endif

            #ifdef  SEG25_USED
                if(g_u8DspRam[3].bits.bit1) SEG25 = 0;  else SEG25 = 1;
            #endif


        }
        else
        {
            #ifdef  SEG0_USED
                if(g_u8DspRam[0].bits.bit0) SEG0 = 1;   else SEG0 = 0;
            #endif

            #ifdef  SEG1_USED
                if(g_u8DspRam[0].bits.bit1) SEG1 = 1;   else SEG1 = 0;
            #endif

            #ifdef  SEG2_USED
                if(g_u8DspRam[0].bits.bit2) SEG2 = 1;   else SEG2 = 0;
            #endif

            #ifdef  SEG3_USED
                if(g_u8DspRam[0].bits.bit3) SEG3 = 1;   else SEG3 = 0;
            #endif

            #ifdef  SEG4_USED
                if(g_u8DspRam[0].bits.bit4) SEG4 = 1;   else SEG4 = 0;
            #endif

            #ifdef  SEG5_USED
                if(g_u8DspRam[0].bits.bit5) SEG5 = 1;   else SEG5 = 0;
            #endif

            #ifdef  SEG6_USED
                if(g_u8DspRam[0].bits.bit6) SEG6 = 1;   else SEG6 = 0;
            #endif

            #ifdef  SEG7_USED
                if(g_u8DspRam[0].bits.bit7) SEG7 = 1;   else SEG7 = 0;
            #endif

            #ifdef  SEG8_USED
                if(g_u8DspRam[1].bits.bit0) SEG8 = 1;   else SEG8 = 0;
            #endif

            #ifdef  SEG9_USED
                if(g_u8DspRam[1].bits.bit1) SEG9 = 1;   else SEG9 = 0;
            #endif

            #ifdef  SEG10_USED
                if(g_u8DspRam[1].bits.bit2) SEG10 = 1;  else SEG10 = 0;
            #endif

            #ifdef  SEG11_USED
                if(g_u8DspRam[1].bits.bit3) SEG11 = 1;  else SEG11 = 0;
            #endif

            #ifdef  SEG12_USED
                if(g_u8DspRam[1].bits.bit4) SEG12 = 1;  else SEG12 = 0;
            #endif

            #ifdef  SEG13_USED
                if(g_u8DspRam[1].bits.bit5) SEG13 = 1;  else SEG13 = 0;
            #endif

            #ifdef  SEG14_USED
                if(g_u8DspRam[1].bits.bit6) SEG14 = 1;  else SEG14 = 0;
            #endif

            #ifdef  SEG15_USED
                if(g_u8DspRam[1].bits.bit7) SEG15 = 1;  else SEG15 = 0;
            #endif

            #ifdef  SEG16_USED
                if(g_u8DspRam[2].bits.bit0) SEG16 = 1;  else SEG16 = 0;
            #endif

            #ifdef  SEG17_USED
                if(g_u8DspRam[2].bits.bit1) SEG17 = 1;  else SEG17 = 0;
            #endif

            #ifdef  SEG18_USED
                if(g_u8DspRam[2].bits.bit2) SEG18 = 1;  else SEG18 = 0;
            #endif

            #ifdef  SEG19_USED
                if(g_u8DspRam[2].bits.bit3) SEG19 = 1;  else SEG19 = 0;
            #endif

            #ifdef  SEG20_USED
                if(g_u8DspRam[2].bits.bit4) SEG20 = 1;  else SEG20 = 0;
            #endif

            #ifdef  SEG21_USED
                if(g_u8DspRam[2].bits.bit5) SEG21 = 1;  else SEG21 = 0;
            #endif

            #ifdef  SEG22_USED
                if(g_u8DspRam[2].bits.bit6) SEG22 = 1;  else SEG22 = 0;
            #endif

            #ifdef  SEG23_USED
                if(g_u8DspRam[2].bits.bit7) SEG23 = 1;  else SEG23 = 0;
            #endif

            #ifdef  SEG24_USED
                if(g_u8DspRam[3].bits.bit0) SEG24 = 1;  else SEG24 = 0;
            #endif

            #ifdef  SEG25_USED
                if(g_u8DspRam[3].bits.bit1) SEG25 = 1;  else SEG25 = 0;
            #endif


        }
        #if (COM_NUM == 2)

            if (g_u8ScanCNT % 2)
            {
                unsigned char i;

                for(i = 0; i < COM_SEG_DIV8 / 2; i++)
                    g_u8DspRam[i].byte = g_u8DspRam[i + COM_SEG_DIV8 / 2].byte;
            }
        #endif
    }
    #endif


    #if (COM_NUM > 2 )
    {
        if (!(g_u8ScanCNT % 2))
        {
            #ifdef  SEG0_USED
                if(g_u8DspRam[0].bits.bit0) SEG0 = 0;   else SEG0 = 1;
            #endif

            #ifdef  SEG1_USED
                if(g_u8DspRam[0].bits.bit4) SEG1 = 0;   else SEG1 = 1;
            #endif

            #ifdef  SEG2_USED
                if(g_u8DspRam[1].bits.bit0) SEG2 = 0;   else SEG2 = 1;
            #endif

            #ifdef  SEG3_USED
                if(g_u8DspRam[1].bits.bit4) SEG3 = 0;   else SEG3 = 1;
            #endif

            #ifdef  SEG4_USED
                if(g_u8DspRam[2].bits.bit0) SEG4 = 0;   else SEG4 = 1;
            #endif

            #ifdef  SEG5_USED
                if(g_u8DspRam[2].bits.bit4) SEG5 = 0;   else SEG5 = 1;
            #endif

            #ifdef  SEG6_USED
                if(g_u8DspRam[3].bits.bit0) SEG6 = 0;   else SEG6 = 1;
            #endif

            #ifdef  SEG7_USED
                if(g_u8DspRam[3].bits.bit4) SEG7 = 0;   else SEG7 = 1;
            #endif

            #ifdef  SEG8_USED
                if(g_u8DspRam[4].bits.bit0) SEG8 = 0;   else SEG8 = 1;
            #endif

            #ifdef  SEG9_USED
                if(g_u8DspRam[4].bits.bit4) SEG9 = 0;   else SEG9 = 1;
            #endif

            #ifdef  SEG10_USED
                if(g_u8DspRam[5].bits.bit0) SEG10 = 0;  else SEG10 = 1;
            #endif

            #ifdef  SEG11_USED
                if(g_u8DspRam[5].bits.bit4) SEG11 = 0;  else SEG11 = 1;
            #endif

            #ifdef  SEG12_USED
                if(g_u8DspRam[6].bits.bit0) SEG12 = 0;  else SEG12 = 1;
            #endif

            #ifdef  SEG13_USED
                if(g_u8DspRam[6].bits.bit4) SEG13 = 0;  else SEG13 = 1;
            #endif

            #ifdef  SEG14_USED
                if(g_u8DspRam[7].bits.bit0) SEG14 = 0;  else SEG14 = 1;
            #endif

            #ifdef  SEG15_USED
                if(g_u8DspRam[7].bits.bit4) SEG15 = 0;  else SEG15 = 1;
            #endif

            #ifdef  SEG16_USED
                if(g_u8DspRam[8].bits.bit0) SEG16 = 0;  else SEG16 = 1;
            #endif

            #ifdef  SEG17_USED
                if(g_u8DspRam[8].bits.bit4) SEG17 = 0;  else SEG17 = 1;
            #endif

            #ifdef  SEG18_USED
                if(g_u8DspRam[9].bits.bit0) SEG18 = 0;  else SEG18 = 1;
            #endif

            #ifdef  SEG19_USED
                if(g_u8DspRam[9].bits.bit4) SEG19 = 0;  else SEG19 = 1;
            #endif

            #ifdef  SEG20_USED
                if(g_u8DspRam[10].bits.bit0)SEG20 = 0;  else SEG20 = 1;
            #endif

            #ifdef  SEG21_USED
                if(g_u8DspRam[10].bits.bit4)SEG21 = 0;  else SEG21 = 1;
            #endif

            #ifdef  SEG22_USED
                if(g_u8DspRam[11].bits.bit0)SEG22 = 0;  else SEG22 = 1;
            #endif

            #ifdef  SEG23_USED
                if(g_u8DspRam[11].bits.bit4)SEG23 = 0;  else SEG23 = 1;
            #endif

            #ifdef  SEG24_USED
                if(g_u8DspRam[12].bits.bit0)SEG24 = 0;  else SEG24 = 1;
            #endif

            #ifdef  SEG25_USED
                if(g_u8DspRam[12].bits.bit4)SEG25 = 0;  else SEG25 = 1;
            #endif


        }
        else
        {
            #ifdef  SEG0_USED
                if(g_u8DspRam[0].bits.bit0) SEG0 = 1;   else SEG0 = 0;
            #endif

            #ifdef  SEG1_USED
                if(g_u8DspRam[0].bits.bit4) SEG1 = 1;   else SEG1 = 0;
            #endif

            #ifdef  SEG2_USED
                if(g_u8DspRam[1].bits.bit0) SEG2 = 1;   else SEG2 = 0;
            #endif

            #ifdef  SEG3_USED
                if(g_u8DspRam[1].bits.bit4) SEG3 = 1;   else SEG3 = 0;
            #endif

            #ifdef  SEG4_USED
                if(g_u8DspRam[2].bits.bit0) SEG4 = 1;   else SEG4 = 0;
            #endif

            #ifdef  SEG5_USED
                if(g_u8DspRam[2].bits.bit4) SEG5 = 1;   else SEG5 = 0;
            #endif

            #ifdef  SEG6_USED
                if(g_u8DspRam[3].bits.bit0) SEG6 = 1;   else SEG6 = 0;
            #endif

            #ifdef  SEG7_USED
                if(g_u8DspRam[3].bits.bit4) SEG7 = 1;   else SEG7 = 0;
            #endif

            #ifdef  SEG8_USED
                if(g_u8DspRam[4].bits.bit0) SEG8 = 1;   else SEG8 = 0;
            #endif

            #ifdef  SEG9_USED
                if(g_u8DspRam[4].bits.bit4) SEG9 = 1;   else SEG9 = 0;
            #endif

            #ifdef  SEG10_USED
                if(g_u8DspRam[5].bits.bit0) SEG10 = 1;  else SEG10 = 0;
            #endif

            #ifdef  SEG11_USED
                if(g_u8DspRam[5].bits.bit4) SEG11 = 1;  else SEG11 = 0;
            #endif

            #ifdef  SEG12_USED
                if(g_u8DspRam[6].bits.bit0) SEG12 = 1;  else SEG12 = 0;
            #endif

            #ifdef  SEG13_USED
                if(g_u8DspRam[6].bits.bit4) SEG13 = 1;  else SEG13 = 0;
            #endif

            #ifdef  SEG14_USED
                if(g_u8DspRam[7].bits.bit0) SEG14 = 1;  else SEG14 = 0;
            #endif

            #ifdef  SEG15_USED
                if(g_u8DspRam[7].bits.bit4) SEG15 = 1;  else SEG15 = 0;
            #endif

            #ifdef  SEG16_USED
                if(g_u8DspRam[8].bits.bit0) SEG16 = 1;  else SEG16 = 0;
            #endif

            #ifdef  SEG17_USED
                if(g_u8DspRam[8].bits.bit4) SEG17 = 1;  else SEG17 = 0;
            #endif

            #ifdef  SEG18_USED
                if(g_u8DspRam[9].bits.bit0) SEG18 = 1;  else SEG18 = 0;
            #endif

            #ifdef  SEG19_USED
                if(g_u8DspRam[9].bits.bit4) SEG19 = 1;  else SEG19 = 0;
            #endif

            #ifdef  SEG20_USED
                if(g_u8DspRam[10].bits.bit0)SEG20 = 1;  else SEG20 = 0;
            #endif

            #ifdef  SEG21_USED
                if(g_u8DspRam[10].bits.bit4)SEG21 = 1;  else SEG21 = 0;
            #endif

            #ifdef  SEG22_USED
                if(g_u8DspRam[11].bits.bit0)SEG22 = 1;  else SEG22 = 0;
            #endif

            #ifdef  SEG23_USED
                if(g_u8DspRam[11].bits.bit4)SEG23 = 1;  else SEG23 = 0;
            #endif

            #ifdef  SEG24_USED
                if(g_u8DspRam[12].bits.bit0)SEG24 = 1;  else SEG24 = 0;
            #endif

            #ifdef  SEG25_USED
                if(g_u8DspRam[12].bits.bit4)SEG25 = 1;  else SEG25 = 0;
            #endif


        }

        if (g_u8ScanCNT % 2)
        {
            unsigned char i;

            for(i = 0; i < SEG_NUM_DIV2; i++)
                g_u8DspRam[i].byte >>= 1;
        }
    }
    #endif
}


/*******************************************************************************
  * @brief    LCD Update Display function.
  * @param    None
  * @retval   None
 *******************************************************************************/
void LCD_Update_Display(void)
{
    unsigned char i;

    #if (COM_NUM <= 2)
        if (g_u8ScanCNT == 0)
        {
            for(i = 0; i < COM_SEG_DIV8; i++)
                g_u8DspRam[i].byte=g_u8SegBuf[i];
        }
    #endif

    #if (COM_NUM > 2)
        if (g_u8ScanCNT == 0)
        {
            for(i = 0; i < SEG_NUM_DIV2; i++)
                g_u8DspRam[i].byte = g_u8SegBuf[i];
        }
    #endif

    #if (COM_NUM >= 5)
        else if(g_u8ScanCNT == 8)
        {
            unsigned char j=0;

            for(i = SEG_NUM_DIV2; i < SEG_NUM_DIV2 * 2; i++)
                g_u8DspRam[j++].byte = g_u8SegBuf[i];
        }
    #endif

    #if (COM_NUM >= 9)
        else if(g_u8ScanCNT == 16)
        {
            unsigned char j=0;

            for(i = SEG_NUM_DIV2 * 2; i < SEG_NUM_DIV2 * 3; i++)
                g_u8DspRam[j++].byte = g_u8SegBuf[i];
        }
    #endif

    #if (COM_NUM >= 13)
        else if(g_u8ScanCNT == 24)
        {
            unsigned char j=0;

            for(i = SEG_NUM_DIV2 * 3; i < SEG_NUM_DIV2 * 4; i++)
                g_u8DspRam[j++].byte = g_u8SegBuf[i];
        }
    #endif
}


/*******************************************************************************
  * @brief    LCD Update RAM function.
  * @param    buffer_Num: the buffer that will be wirte. 
  *           buffer_Num range is 0 ~ LCD_RAM_Total_Byte.
  * @param    data_Num: the data that will be wirte. 
  *           The data_Num range is 0x00 ~ 0xFF for DOT_MATRIX_DISPLAY.
  * @retval   None
 *******************************************************************************/
void LCD_Update_RAM(u8 buffer_Num,u8 data_Num)
{
    #ifdef  SEVEN_SEG_DISPLAY
    {
        g_u8SegBuf[buffer_Num] = Trans_Segment[data_Num];
    }

    #elif   DOT_MATRIX_DISPLAY 
    {
        g_u8SegBuf[buffer_Num] = data_Num;
    }
    #endif
}


/*******************************************************************************
  * @brief    Update LCD  Scan count function.
  * @param    None
  * @retval   None
 *******************************************************************************/
void Update_LCD_Scan_count(void)
{
    g_u8ScanCNT++;

    if (g_u8ScanCNT > (COM_NUM * 2 - 1))
    {
        g_u8ScanCNT = 0;
    }
}


/*********** (C) COPYRIGHT 2019 Holtek Semiconductor Inc **********END OF FILE*/
