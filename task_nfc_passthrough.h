#ifndef TASK_NFC_PASSTHROUGH_H
#define TASK_NFC_PASSTHROUGH_H

#include "SW_Lib/HT8_Type.h"

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