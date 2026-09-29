/**
 * @file    drv_nfc_tag.h
 * @brief   Hardware Abstraction Layer (HAL) for NFC Tag driver.
 *          Target IC: Holtek BC45B4211
 */

#ifndef _DRV_NFC_TAG_H_
#define _DRV_NFC_TAG_H_

#include "SW_Lib/HT8_Type.h"

/* NFC Tag I2C Device Address (7-bit address is 0x55) */
#define NFC_TAG_I2C_ADDR    (0x55 << 1)

/**
 * @brief  Initialize the NFC tag driver.
 * @param  None
 * @retval None
 */
void NFC_Tag_Init(void);

/**
 * @brief  Read a specific register from the NFC Tag.
 * @param  memAddr: Memory block address (e.g., 0xFE for config).
 * @param  regAddr: Register address within the block.
 * @param  pReadVal: Pointer to store the retrieved data.
 * @retval u8: 0 for SUCCESS, 1 for I2C ERROR (NACK/Timeout).
 */
u8 NFC_Tag_ReadRegister(u8 memAddr, u8 regAddr, u8 *pReadVal);

/**
 * @brief  Write data to a specific register in the NFC Tag with a mask.
 * @param  memAddr: Memory block address.
 * @param  regAddr: Register address within the block.
 * @param  mask: Bit mask for the write operation.
 * @param  val: Data value to write.
 * @retval u8: 0 for SUCCESS, 1 for I2C ERROR.
 */
u8 NFC_Tag_WriteRegister(u8 memAddr, u8 regAddr, u8 mask, u8 val);

/**
 * @brief  Read a 16-byte memory block from the NFC Tag.
 * @param  memAddr: Memory block address to read from.
 * @param  pBuffer: Pointer to a 16-byte array to store data.
 * @retval u8: 0 for SUCCESS, 1 for I2C ERROR.
 */
u8 NFC_Tag_ReadMemoryBlock(u8 memAddr, u8 *pBuffer);

/**
 * @brief  Write a 16-byte memory block to the NFC Tag.
 * @param  memAddr: Memory block address to write to.
 * @param  pBuffer: Pointer to the 16-byte data array.
 * @retval u8: 0 for SUCCESS, 1 for I2C ERROR.
 */
u8 NFC_Tag_WriteMemoryBlock(u8 memAddr, u8 *pBuffer);

#endif /* _DRV_NFC_TAG_H_ */