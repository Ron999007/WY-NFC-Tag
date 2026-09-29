/**
 * @file    drv_nfc_tag.c
 * @brief   Hardware Abstraction Layer (HAL) implementation for NFC Tag.
 *          Target IC: Holtek BC45B4211
 */

#include "drv_nfc_tag.h"
#include "SW_Lib/HT8_SW_I2C_Master.h"

/*
 * @brief  Initialize the NFC tag driver.
 * @note   Relies on the system's SW_I2C_Master_Init() being called prior.
 */
void NFC_Tag_Init(void)
{
    /* Ensure the I2C bus is released */
    SW_I2C_Send_Stop();
}

/*
 * @brief  Read a specific register from the NFC Tag.
 * @param  memAddr: Memory block address.
 * @param  regAddr: Register address within the block.
 * @param  pReadVal: Pointer to store the retrieved data.
 * @retval u8: 0 for SUCCESS, 1 for ERROR.
 */
u8 NFC_Tag_ReadRegister(u8 memAddr, u8 regAddr, u8 *pReadVal)
{
    if (SW_I2C_Send_Start() == BUSY) return 1;

    if (SW_I2C_Send_Addr(NFC_TAG_I2C_ADDR, TX_Mode) == NACK) goto I2C_FAIL;
    if (SW_I2C_Send_Data(memAddr) == NACK) goto I2C_FAIL;
    if (SW_I2C_Send_Data(regAddr) == NACK) goto I2C_FAIL;

    SW_I2C_Send_Stop();
    
    if (SW_I2C_Send_Start() == BUSY) return 1;

    if (SW_I2C_Send_Addr(NFC_TAG_I2C_ADDR, RX_Mode) == NACK) goto I2C_FAIL;

    *pReadVal = SW_I2C_Receive_Data(NACK);

    SW_I2C_Send_Stop();
    return 0;

I2C_FAIL:
    SW_I2C_Send_Stop();
    return 1;
}

/*
 * @brief  Write data to a specific register in the NFC Tag with a mask.
 * @param  memAddr: Memory block address.
 * @param  regAddr: Register address within the block.
 * @param  mask: Bit mask for the write operation.
 * @param  val: Data value to write.
 * @retval u8: 0 for SUCCESS, 1 for ERROR.
 */
u8 NFC_Tag_WriteRegister(u8 memAddr, u8 regAddr, u8 mask, u8 val)
{
    if (SW_I2C_Send_Start() == BUSY) return 1;

    if (SW_I2C_Send_Addr(NFC_TAG_I2C_ADDR, TX_Mode) == NACK) goto I2C_FAIL;
    if (SW_I2C_Send_Data(memAddr) == NACK) goto I2C_FAIL;
    if (SW_I2C_Send_Data(regAddr) == NACK) goto I2C_FAIL;
    if (SW_I2C_Send_Data(mask) == NACK) goto I2C_FAIL;
    if (SW_I2C_Send_Data(val) == NACK) goto I2C_FAIL;

    SW_I2C_Send_Stop();
    return 0;

I2C_FAIL:
    SW_I2C_Send_Stop();
    return 1;
}

/*
 * @brief  Read a 16-byte memory block from the NFC Tag.
 * @param  memAddr: Memory block address to read from.
 * @param  pBuffer: Pointer to a 16-byte array to store data.
 * @retval u8: 0 for SUCCESS, 1 for ERROR.
 */
u8 NFC_Tag_ReadMemoryBlock(u8 memAddr, u8 *pBuffer)
{
    u8 i;

    if (SW_I2C_Send_Start() == BUSY) return 1;

    if (SW_I2C_Send_Addr(NFC_TAG_I2C_ADDR, TX_Mode) == NACK) goto I2C_FAIL;
    if (SW_I2C_Send_Data(memAddr) == NACK) goto I2C_FAIL;
    
    SW_I2C_Send_Stop();
    
    if (SW_I2C_Send_Start() == BUSY) return 1;
    if (SW_I2C_Send_Addr(NFC_TAG_I2C_ADDR, RX_Mode) == NACK) goto I2C_FAIL;

    /* Read 15 bytes with ACK */
    for (i = 0; i < 15; i++)
    {
        *pBuffer = SW_I2C_Receive_Data(ACK);
        pBuffer++;
    }
    /* Read the last byte with NACK */
    *pBuffer = SW_I2C_Receive_Data(NACK);

    SW_I2C_Send_Stop();
    return 0;

I2C_FAIL:
    SW_I2C_Send_Stop();
    return 1;
}

/*
 * @brief  Write a 16-byte memory block to the NFC Tag.
 * @param  memAddr: Memory block address to write to.
 * @param  pBuffer: Pointer to the 16-byte data array.
 * @retval u8: 0 for SUCCESS, 1 for ERROR.
 */
u8 NFC_Tag_WriteMemoryBlock(u8 memAddr, u8 *pBuffer)
{
    u8 i;

    if (SW_I2C_Send_Start() == BUSY) return 1;

    if (SW_I2C_Send_Addr(NFC_TAG_I2C_ADDR, TX_Mode) == NACK) goto I2C_FAIL;
    if (SW_I2C_Send_Data(memAddr) == NACK) goto I2C_FAIL;

    /* Write 16 bytes payload */
    for (i = 0; i < 16; i++)
    {
        if (SW_I2C_Send_Data(*pBuffer) == NACK) goto I2C_FAIL;
        pBuffer++;
    }

    SW_I2C_Send_Stop();
    return 0;

I2C_FAIL:
    SW_I2C_Send_Stop();
    return 1;
}