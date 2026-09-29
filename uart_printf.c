#include "cc_generated_files\CodeConfig.h"

/******************************************************************************
 * @brief    Send a null-terminated string via UART.
 * @param    str: Pointer to the string to be transmitted
 * @retval   None
 *******************************************************************************/
void UART_PrintStr(const char *str) 
{
    while (*str) 
    {
        SW_UART_Transmit((u16)(*str++));
    }
}

/*******************************************************************************
 * @brief    Convert and print a 16-bit signed integer in decimal format.
 * @param    num: 16-bit signed integer to be transmitted
 * @retval   None
 *******************************************************************************/
void UART_PrintDec(int num) 
{
    char buf[6]; /* Max length for 16-bit int is -32768 (6 chars) */
    int i = 0;
    int isNegative = 0;

    if (num == 0) 
    {
        SW_UART_Transmit((u16)'0');
        return;
    }

    /* Handle negative numbers */
    if (num < 0) 
    {
        isNegative = 1;
        num = -num;
    }

    /* Convert integer to ASCII characters in reverse order */
    while (num > 0) 
    {
        buf[i++] = (num % 10) + '0';
        num /= 10;
    }

    /* Append negative sign if necessary */
    if (isNegative) 
    {
        buf[i++] = '-';
    }

    /* Transmit characters in the correct order */
    while (i > 0) 
    {
        SW_UART_Transmit((u16)buf[--i]);
    }
}

/*******************************************************************************
 * @brief    Convert and print an unsigned integer in Hexadecimal format.
 * @param    num: Unsigned integer to be transmitted
 * @param    digits: Number of hex digits to print (e.g., 2 for 8-bit, 4 for 16-bit)
 * @retval   None
 *******************************************************************************/
void UART_PrintHex(unsigned int num, unsigned char digits) 
{
    char buf[4];
    unsigned char i = 0;
    unsigned char rem;

    /* Convert integer to Hex characters */
    for (i = 0; i < digits; i++) 
    {
        rem = num % 16;
        if (rem < 10) 
        {
            buf[i] = rem + '0';
        } 
        else 
        {
            buf[i] = rem - 10 + 'A';
        }
        num /= 16;
    }

    /* Transmit characters in reverse order (MSB first) */
    while (digits > 0) 
    {
        SW_UART_Transmit((u16)buf[--digits]);
    }
}

/*******************************************************************************
 * @brief    Print a carriage return and line feed via UART.
 * @param    None
 * @retval   None
 *******************************************************************************/
void UART_PrintLine(void) 
{
    SW_UART_Transmit((u16)'\r');
    SW_UART_Transmit((u16)'\n');
}