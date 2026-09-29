#ifndef SYS_TICK_H
#define SYS_TICK_H


/* Public API Declarations */
void SysTick_Init(void);
u32 SysTick_GetTicks(void);
void SysTick_DelayMs(u32 ms);
void SysTick_Handler(void);

#endif /* SYS_TICK_H */