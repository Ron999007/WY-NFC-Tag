#ifndef TASK_NFC_PASSTHROUGH_H
#define TASK_NFC_PASSTHROUGH_H

#include "SW_Lib/HT8_Type.h"

/* ====================================================================
 * Application Protocol Configuration
 * ==================================================================== */
#define CMD_IMG_TRANSFER      0x01
#define CMD_FW_UPGRADE        0x02
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

#endif /* TASK_NFC_PASSTHROUGH_H */