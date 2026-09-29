#ifndef _UART_PRINTF_H_
#define _UART_PRINTF_H_

/* Include your MCU specific header here */

/* Define u16 if it is not defined in your system headers */
#ifndef u16
typedef unsigned short u16;
#endif

/*******************************************************************************
 * @brief    Send a null-terminated string via UART0.
 * @param    str: Pointer to the string to be transmitted
 * @retval   None
 *******************************************************************************/
void UART_PrintStr(const char *str);

/*******************************************************************************
 * @brief    Convert and print a 16-bit signed integer in decimal format.
 * @param    num: 16-bit signed integer to be transmitted
 * @retval   None
 *******************************************************************************/
void UART_PrintDec(int num);

/*******************************************************************************
 * @brief    Convert and print an unsigned integer in Hexadecimal format.
 * @param    num: Unsigned integer to be transmitted
 * @param    digits: Number of hex digits to print (e.g., 2 for 8-bit, 4 for 16-bit)
 * @retval   None
 *******************************************************************************/
void UART_PrintHex(unsigned int num, unsigned char digits);

/*******************************************************************************
 * @brief    Print a carriage return and line feed via UART0.
 * @param    None
 * @retval   None
 *******************************************************************************/
void UART_PrintLine(void);

#endif /* _UART_PRINTF_H_ */