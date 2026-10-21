#ifndef TASK_NFC_PASSTHROUGH_H
#define TASK_NFC_PASSTHROUGH_H

#include "SW_Lib/HT8_Type.h"

/* ====================================================================
 * Tag Firmware Version (3 Digits)
 * ==================================================================== */
#define TAG_FW_VER_MAJOR      2     /* MAJOR */
#define TAG_FW_VER_MINOR      3     /* MINOR */
#define TAG_FW_VER_PATCH      0     /* PATCH */
#define IMAGE_MAX_NUM_ADDR    0
#define IMAGE_MAX_NUM	 	  3

/* ====================================================================
 * Application Protocol Configuration
 * ==================================================================== */
#define CMD_IMG_TRANSFER      0x01
#define CMD_FW_UPGRADE        0x02
#define CMD_POLL_VOLTAGE      0x03  /* Reader requests current capacitor voltage */
#define CMD_UPDATE_EPD        0x04  /* Reader commands Tag to refresh EPD */
#define CMD_UPDATE_FAIL       0x05  /* Reader aborts update due to timeout */
#define CMD_INIT_EPD          0x06
#define CMD_ACK_MASK          0x80  /* Tag ACK response mask (e.g., 0x81 for Image ACK) */

#define STATUS_PASS           0x01
#define STATUS_FAIL           0x00


#define PROTOCOL_PACKET_SIZE  64
#define PROTOCOL_PAYLOAD_SIZE 59    /* 64 - 1(Cmd) - 2(Idx) - 2(CRC) = 59 Bytes */

/* Application Data Sizes */
#define EPD_TOTAL_BYTES       12480
/* Calculate total payloads needed (Ceiling division) */
#define EPD_TOTAL_PAYLOADS    ((EPD_TOTAL_BYTES + PROTOCOL_PAYLOAD_SIZE - 1) / PROTOCOL_PAYLOAD_SIZE)

/* 
 * @brief Initializes the NFC Pass-Through task and state machine.
 * @param None
 * @retval None
 */
void Task_NFC_PassThrough_Init(void);

/* 
 * @brief Non-blocking background process for handling NFC-to-EPD streaming.
 *        Should be called continuously inside the main while(1) loop.
 * @param None
 * @retval None
 */
void Task_NFC_PassThrough_Process(void);

/* ====================================================================
 * Application ADC Configuration
 * ==================================================================== */
/* Define integer constants for Fixed-Point Math */
#define VREF_MV           3000UL    /* Reference voltage in mV (3.0V) */
#define ADC_MAX_STEP      4096UL    /* 12-bit ADC max step */

/* 
 * Firmware voltage restoration ratio (Inverse of hardware divider)
 * V_in = V_pin * (1000k + 150k) / 150k 
 * V_in = V_pin * 1150 / 150 = V_pin * 23 / 3
 */
#define DIVIDER_MULT      23UL      /* Multiplier MUST be 23 */
#define DIVIDER_DIV       3UL       /* Divisor MUST be 3 */

#endif /* TASK_NFC_PASSTHROUGH_H */