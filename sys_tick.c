#include "cc_generated_files\CodeConfig.h"
#include "sys_tick.h"

/* Global volatile variable to track Time Base ticks (1 tick = 32us) */
static volatile u32 g_timebase_ticks = 0;

/**
 * @brief    Initialize the global tick counter.
 */
void SysTick_Init(void)
{
    g_timebase_ticks = 0;
}

/**
 * @brief    Get the current system uptime in Time Base ticks.
 * @retval   Current tick count.
 */
u32 SysTick_GetTicks(void)
{
    u32 current_ticks;
    
    /* Disable global interrupt briefly to ensure atomic read of 32-bit variable */
    _emi = 0;
    current_ticks = g_timebase_ticks;
    _emi = 1;
    
    return current_ticks;
}

/**
 * @brief    Precise blocking delay using the hardware Time Base interrupt.
 * @param    ms: Number of milliseconds to delay.
 */
void SysTick_DelayMs(u32 ms)
{
    /* Calculate target ticks. (ms * 1000 us) / 32 us per tick */
    u32 target_ticks = (ms * 1000) / 32;
    u32 start_ticks = SysTick_GetTicks();
    
    /* Wait until the target time has elapsed based on hardware interrupts */
    while ((SysTick_GetTicks() - start_ticks) < target_ticks)
    {
        /* Critial: Feed the watchdog to prevent system reset during long delays */
        GCC_CLRWDT(); 
    }
}

/**
 * @brief    The 93us hardware timer interrupt service routine hook.
 */
void SysTick_Handler(void)
{
    g_timebase_ticks++;
    //_pb5 = ~_pb5;
}