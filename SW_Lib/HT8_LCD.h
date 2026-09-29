/*******************************************************************************
  * @file     HT8_LCD.h
  * @brief    The header file of the LCD library.
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
#ifndef _HT8_LCD_H_
#define _HT8_LCD_H_

/* Includes-------------------------------------------------------------------*/
#include "HT8_MCU_IP_SEL.h"

/* Exported constants---------------------------------------------------------*/
//  #define LCD_USE_STM0    (1)
//  #define COM_NUM         8
//  #define SEG_NUM         4

/* COM mapping setting */
//  #define COM0_BIAS       PF0_COM
//  #define COM0_VDD        PF0_Out_H
//  #define COM0_VSS        PF0_Out_L


/* SEG mapping setting */
//  #define SEG0            _pb0

#define LCD_ENABLE()        (_scomen = 1)
#define LCD_DISABLE()       (_scomen = 0)
#define SW_LCD_TYPE         (1)

/*========================= Select LCD bias current ==========================*/
//  #define I_BIAS_25       (1)     /*IBIAS = 25£gA@(VDD=5V)*/
//  #define I_BIAS_50       (1)     /*IBIAS = 50£gA@(VDD=5V)*/
//  #define I_BIAS_100      (1)     /*IBIAS = 100£gA@(VDD=5V)*/
//  #define I_BIAS_200      (1)     /*IBIAS = 200£gA@(VDD=5V)*/
/*=================== The end of Select LCD bias current =====================*/

/*=========================== Select Display type ============================*/
//  #define DOT_MATRIX_DISPLAY  (1)
//  #define SEVEN_SEG_DISPLAY   (1)
/*===================== The end of Select Display type =======================*/

#if (SEG_NUM % 2 == 0) 
    #define SEG_NUM_DIV2    (SEG_NUM/2)

#elif   (SEG_NUM % 2 != 0) 
    #define SEG_NUM_DIV2    (SEG_NUM/2+1)
#endif

#if (SEG_NUM % 8 == 0)
    #define SEG_NUM_DIV8    (SEG_NUM/8)

#elif   (SEG_NUM % 8 != 0)
    #define SEG_NUM_DIV8    (SEG_NUM/8+1)
#endif

#if (COM_NUM % 4 == 0)
    #define COM_NUM_DIV4    (COM_NUM/4)

#elif   (COM_NUM % 4 != 0)
    #define COM_NUM_DIV4    (COM_NUM/4+1)
#endif

#define COM_SEG_DIV8        (COM_NUM*SEG_NUM_DIV8)
#define COM_DIV4_SEG_DIV2   (COM_NUM_DIV4*SEG_NUM_DIV2)

#if (COM_NUM == 1 ) || (COM_NUM == 2 )

    #define LCD_RAM_Total_Byte      COM_SEG_DIV8
    #define Scan_RAM_Total_Byte     COM_SEG_DIV8

#elif   (COM_NUM == 3 ) || (COM_NUM == 4 )

    #define LCD_RAM_Total_Byte      SEG_NUM_DIV2
    #define Scan_RAM_Total_Byte     SEG_NUM_DIV2

#elif   ( COM_NUM  >  4 )
    #define LCD_RAM_Total_Byte      COM_DIV4_SEG_DIV2
    #define Scan_RAM_Total_Byte     SEG_NUM_DIV2
#endif

#if (COM_NUM == 1)

    #define COM0_USED       (1)

#elif   (COM_NUM == 2)

    #define COM0_USED       (1)
    #define COM1_USED       (1)

#elif   (COM_NUM == 3)

    #define COM0_USED       (1)
    #define COM1_USED       (1)
    #define COM2_USED       (1)

#elif   (COM_NUM == 4)

    #define COM0_USED       (1)
    #define COM1_USED       (1)
    #define COM2_USED       (1)
    #define COM3_USED       (1)

#endif


#if (SEG_NUM == 1)

    #define SEG0_USED       (1)

#elif   (SEG_NUM == 2)

    #define SEG0_USED       (1)
    #define SEG1_USED       (1)

#elif   (SEG_NUM == 3)

    #define SEG0_USED       (1)
    #define SEG1_USED       (1)
    #define SEG2_USED       (1)

#elif   (SEG_NUM == 4)

    #define SEG0_USED       (1)
    #define SEG1_USED       (1)
    #define SEG2_USED       (1)
    #define SEG3_USED       (1)

#elif   (SEG_NUM == 5)

    #define SEG0_USED       (1)
    #define SEG1_USED       (1)
    #define SEG2_USED       (1)
    #define SEG3_USED       (1)
    #define SEG4_USED       (1)

#elif   (SEG_NUM == 6)

    #define SEG0_USED       (1)
    #define SEG1_USED       (1)
    #define SEG2_USED       (1)
    #define SEG3_USED       (1)
    #define SEG4_USED       (1)
    #define SEG5_USED       (1)

#elif   (SEG_NUM == 7)

    #define SEG0_USED       (1)
    #define SEG1_USED       (1)
    #define SEG2_USED       (1)
    #define SEG3_USED       (1)
    #define SEG4_USED       (1)
    #define SEG5_USED       (1)
    #define SEG6_USED       (1)

#elif   (SEG_NUM == 8)

    #define SEG0_USED       (1)
    #define SEG1_USED       (1)
    #define SEG2_USED       (1)
    #define SEG3_USED       (1)
    #define SEG4_USED       (1)
    #define SEG5_USED       (1)
    #define SEG6_USED       (1)
    #define SEG7_USED       (1)

#elif   (SEG_NUM == 9)

    #define SEG0_USED       (1)
    #define SEG1_USED       (1)
    #define SEG2_USED       (1)
    #define SEG3_USED       (1)
    #define SEG4_USED       (1)
    #define SEG5_USED       (1)
    #define SEG6_USED       (1)
    #define SEG7_USED       (1)
    #define SEG8_USED       (1)

#elif   (SEG_NUM == 10)

    #define SEG0_USED       (1)
    #define SEG1_USED       (1)
    #define SEG2_USED       (1)
    #define SEG3_USED       (1)
    #define SEG4_USED       (1)
    #define SEG5_USED       (1)
    #define SEG6_USED       (1)
    #define SEG7_USED       (1)
    #define SEG8_USED       (1)
    #define SEG9_USED       (1)

#elif   (SEG_NUM == 11)

    #define SEG0_USED       (1)
    #define SEG1_USED       (1)
    #define SEG2_USED       (1)
    #define SEG3_USED       (1)
    #define SEG4_USED       (1)
    #define SEG5_USED       (1)
    #define SEG6_USED       (1)
    #define SEG7_USED       (1)
    #define SEG8_USED       (1)
    #define SEG9_USED       (1)
    #define SEG10_USED      (1)

#elif   (SEG_NUM == 12)

    #define SEG0_USED       (1)
    #define SEG1_USED       (1)
    #define SEG2_USED       (1)
    #define SEG3_USED       (1)
    #define SEG4_USED       (1)
    #define SEG5_USED       (1)
    #define SEG6_USED       (1)
    #define SEG7_USED       (1)
    #define SEG8_USED       (1)
    #define SEG9_USED       (1)
    #define SEG10_USED      (1)
    #define SEG11_USED      (1)

#elif   (SEG_NUM == 13)

    #define SEG0_USED       (1)
    #define SEG1_USED       (1)
    #define SEG2_USED       (1)
    #define SEG3_USED       (1)
    #define SEG4_USED       (1)
    #define SEG5_USED       (1)
    #define SEG6_USED       (1)
    #define SEG7_USED       (1)
    #define SEG8_USED       (1)
    #define SEG9_USED       (1)
    #define SEG10_USED      (1)
    #define SEG11_USED      (1)
    #define SEG12_USED      (1)

#elif   (SEG_NUM == 14)

    #define SEG0_USED       (1)
    #define SEG1_USED       (1)
    #define SEG2_USED       (1)
    #define SEG3_USED       (1)
    #define SEG4_USED       (1)
    #define SEG5_USED       (1)
    #define SEG6_USED       (1)
    #define SEG7_USED       (1)
    #define SEG8_USED       (1)
    #define SEG9_USED       (1)
    #define SEG10_USED      (1)
    #define SEG11_USED      (1)
    #define SEG12_USED      (1)
    #define SEG13_USED      (1)

#elif   (SEG_NUM == 15)

    #define SEG0_USED       (1)
    #define SEG1_USED       (1)
    #define SEG2_USED       (1)
    #define SEG3_USED       (1)
    #define SEG4_USED       (1)
    #define SEG5_USED       (1)
    #define SEG6_USED       (1)
    #define SEG7_USED       (1)
    #define SEG8_USED       (1)
    #define SEG9_USED       (1)
    #define SEG10_USED      (1)
    #define SEG11_USED      (1)
    #define SEG12_USED      (1)
    #define SEG13_USED      (1)
    #define SEG14_USED      (1)

#elif   (SEG_NUM == 16)

    #define SEG0_USED       (1)
    #define SEG1_USED       (1)
    #define SEG2_USED       (1)
    #define SEG3_USED       (1)
    #define SEG4_USED       (1)
    #define SEG5_USED       (1)
    #define SEG6_USED       (1)
    #define SEG7_USED       (1)
    #define SEG8_USED       (1)
    #define SEG9_USED       (1)
    #define SEG10_USED      (1)
    #define SEG11_USED      (1)
    #define SEG12_USED      (1)
    #define SEG13_USED      (1)
    #define SEG14_USED      (1)
    #define SEG15_USED      (1)

#elif   (SEG_NUM == 17)

    #define SEG0_USED       (1)
    #define SEG1_USED       (1)
    #define SEG2_USED       (1)
    #define SEG3_USED       (1)
    #define SEG4_USED       (1)
    #define SEG5_USED       (1)
    #define SEG6_USED       (1)
    #define SEG7_USED       (1)
    #define SEG8_USED       (1)
    #define SEG9_USED       (1)
    #define SEG10_USED      (1)
    #define SEG11_USED      (1)
    #define SEG12_USED      (1)
    #define SEG13_USED      (1)
    #define SEG14_USED      (1)
    #define SEG15_USED      (1)
    #define SEG16_USED      (1)

#elif   (SEG_NUM == 18)

    #define SEG0_USED       (1)
    #define SEG1_USED       (1)
    #define SEG2_USED       (1)
    #define SEG3_USED       (1)
    #define SEG4_USED       (1)
    #define SEG5_USED       (1)
    #define SEG6_USED       (1)
    #define SEG7_USED       (1)
    #define SEG8_USED       (1)
    #define SEG9_USED       (1)
    #define SEG10_USED      (1)
    #define SEG11_USED      (1)
    #define SEG12_USED      (1)
    #define SEG13_USED      (1)
    #define SEG14_USED      (1)
    #define SEG15_USED      (1)
    #define SEG16_USED      (1)
    #define SEG17_USED      (1)

#elif   (SEG_NUM == 19)

    #define SEG0_USED       (1)
    #define SEG1_USED       (1)
    #define SEG2_USED       (1)
    #define SEG3_USED       (1)
    #define SEG4_USED       (1)
    #define SEG5_USED       (1)
    #define SEG6_USED       (1)
    #define SEG7_USED       (1)
    #define SEG8_USED       (1)
    #define SEG9_USED       (1)
    #define SEG10_USED      (1)
    #define SEG11_USED      (1)
    #define SEG12_USED      (1)
    #define SEG13_USED      (1)
    #define SEG14_USED      (1)
    #define SEG15_USED      (1)
    #define SEG16_USED      (1)
    #define SEG17_USED      (1)
    #define SEG18_USED      (1)

#elif   (SEG_NUM == 20)

    #define SEG0_USED       (1)
    #define SEG1_USED       (1)
    #define SEG2_USED       (1)
    #define SEG3_USED       (1)
    #define SEG4_USED       (1)
    #define SEG5_USED       (1)
    #define SEG6_USED       (1)
    #define SEG7_USED       (1)
    #define SEG8_USED       (1)
    #define SEG9_USED       (1)
    #define SEG10_USED      (1)
    #define SEG11_USED      (1)
    #define SEG12_USED      (1)
    #define SEG13_USED      (1)
    #define SEG14_USED      (1)
    #define SEG15_USED      (1)
    #define SEG16_USED      (1)
    #define SEG17_USED      (1)
    #define SEG18_USED      (1)
    #define SEG19_USED      (1)

#elif   (SEG_NUM == 21)

    #define SEG0_USED       (1)
    #define SEG1_USED       (1)
    #define SEG2_USED       (1)
    #define SEG3_USED       (1)
    #define SEG4_USED       (1)
    #define SEG5_USED       (1)
    #define SEG6_USED       (1)
    #define SEG7_USED       (1)
    #define SEG8_USED       (1)
    #define SEG9_USED       (1)
    #define SEG10_USED      (1)
    #define SEG11_USED      (1)
    #define SEG12_USED      (1)
    #define SEG13_USED      (1)
    #define SEG14_USED      (1)
    #define SEG15_USED      (1)
    #define SEG16_USED      (1)
    #define SEG17_USED      (1)
    #define SEG18_USED      (1)
    #define SEG19_USED      (1)
    #define SEG20_USED      (1)

#elif   (SEG_NUM == 22)

    #define SEG0_USED       (1)
    #define SEG1_USED       (1)
    #define SEG2_USED       (1)
    #define SEG3_USED       (1)
    #define SEG4_USED       (1)
    #define SEG5_USED       (1)
    #define SEG6_USED       (1)
    #define SEG7_USED       (1)
    #define SEG8_USED       (1)
    #define SEG9_USED       (1)
    #define SEG10_USED      (1)
    #define SEG11_USED      (1)
    #define SEG12_USED      (1)
    #define SEG13_USED      (1)
    #define SEG14_USED      (1)
    #define SEG15_USED      (1)
    #define SEG16_USED      (1)
    #define SEG17_USED      (1)
    #define SEG18_USED      (1)
    #define SEG19_USED      (1)
    #define SEG20_USED      (1)
    #define SEG21_USED      (1)

#elif   (SEG_NUM == 23)

    #define SEG0_USED       (1)
    #define SEG1_USED       (1)
    #define SEG2_USED       (1)
    #define SEG3_USED       (1)
    #define SEG4_USED       (1)
    #define SEG5_USED       (1)
    #define SEG6_USED       (1)
    #define SEG7_USED       (1)
    #define SEG8_USED       (1)
    #define SEG9_USED       (1)
    #define SEG10_USED      (1)
    #define SEG11_USED      (1)
    #define SEG12_USED      (1)
    #define SEG13_USED      (1)
    #define SEG14_USED      (1)
    #define SEG15_USED      (1)
    #define SEG16_USED      (1)
    #define SEG17_USED      (1)
    #define SEG18_USED      (1)
    #define SEG19_USED      (1)
    #define SEG20_USED      (1)
    #define SEG21_USED      (1)
    #define SEG22_USED      (1)

#elif   (SEG_NUM == 24)

    #define SEG0_USED       (1)
    #define SEG1_USED       (1)
    #define SEG2_USED       (1)
    #define SEG3_USED       (1)
    #define SEG4_USED       (1)
    #define SEG5_USED       (1)
    #define SEG6_USED       (1)
    #define SEG7_USED       (1)
    #define SEG8_USED       (1)
    #define SEG9_USED       (1)
    #define SEG10_USED      (1)
    #define SEG11_USED      (1)
    #define SEG12_USED      (1)
    #define SEG13_USED      (1)
    #define SEG14_USED      (1)
    #define SEG15_USED      (1)
    #define SEG16_USED      (1)
    #define SEG17_USED      (1)
    #define SEG18_USED      (1)
    #define SEG19_USED      (1)
    #define SEG20_USED      (1)
    #define SEG21_USED      (1)
    #define SEG22_USED      (1)
    #define SEG23_USED      (1)

#elif   (SEG_NUM == 25)

    #define SEG0_USED       (1)
    #define SEG1_USED       (1)
    #define SEG2_USED       (1)
    #define SEG3_USED       (1)
    #define SEG4_USED       (1)
    #define SEG5_USED       (1)
    #define SEG6_USED       (1)
    #define SEG7_USED       (1)
    #define SEG8_USED       (1)
    #define SEG9_USED       (1)
    #define SEG10_USED      (1)
    #define SEG11_USED      (1)
    #define SEG12_USED      (1)
    #define SEG13_USED      (1)
    #define SEG14_USED      (1)
    #define SEG15_USED      (1)
    #define SEG16_USED      (1)
    #define SEG17_USED      (1)
    #define SEG18_USED      (1)
    #define SEG19_USED      (1)
    #define SEG20_USED      (1)
    #define SEG21_USED      (1)
    #define SEG22_USED      (1)
    #define SEG23_USED      (1)
    #define SEG24_USED      (1)

#elif   (SEG_NUM == 26)

    #define SEG0_USED       (1)
    #define SEG1_USED       (1)
    #define SEG2_USED       (1)
    #define SEG3_USED       (1)
    #define SEG4_USED       (1)
    #define SEG5_USED       (1)
    #define SEG6_USED       (1)
    #define SEG7_USED       (1)
    #define SEG8_USED       (1)
    #define SEG9_USED       (1)
    #define SEG10_USED      (1)
    #define SEG11_USED      (1)
    #define SEG12_USED      (1)
    #define SEG13_USED      (1)
    #define SEG14_USED      (1)
    #define SEG15_USED      (1)
    #define SEG16_USED      (1)
    #define SEG17_USED      (1)
    #define SEG18_USED      (1)
    #define SEG19_USED      (1)
    #define SEG20_USED      (1)
    #define SEG21_USED      (1)
    #define SEG22_USED      (1)
    #define SEG23_USED      (1)
    #define SEG24_USED      (1)
    #define SEG25_USED      (1)

#endif


typedef struct
{
    unsigned char bit0 : 1;
    unsigned char bit1 : 1;
    unsigned char bit2 : 1;
    unsigned char bit3 : 1;
    unsigned char bit4 : 1;
    unsigned char bit5 : 1;
    unsigned char bit6 : 1;
    unsigned char bit7 : 1;
} _8bit;


typedef union
{
    _8bit bits;
    unsigned char byte;
}_byte8;


/* Exported functions---------------------------------------------------------*/
void LCD_Init(void);
void LCD_COM_SEG_Init(void);
void CLR_LCD_RAM(void);
void LCD_COM_Scan(void);
void LCD_SEG_Scan(void);
void LCD_Update_Display(void);
void LCD_Update_RAM(u8 buffer_Num,u8 data_Num);
void Update_LCD_Scan_count(void);
extern volatile u8 g_u8ScanCNT;
extern volatile _byte8 g_u8DspRam[Scan_RAM_Total_Byte];
extern volatile  u8 g_u8SegBuf[LCD_RAM_Total_Byte]; 
extern const unsigned char Trans_Segment[]; /*Display 0-9*/

#define LCD_Scan()  {LCD_COM_Scan();LCD_SEG_Scan();Update_LCD_Scan_count();\
                     LCD_Update_Display();}

#endif

/*********** (C) COPYRIGHT 2019 Holtek Semiconductor Inc **********END OF FILE*/
