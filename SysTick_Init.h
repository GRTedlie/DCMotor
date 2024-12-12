/*Date: 09/21/24
Auther: Griffin Tedlie
Systick and PLL function declarations

Includes functions to delay program using the PLL */

#include <stdint.h>


#ifndef SYSTICK_INIT
#define SYSTICK_INIT

void SysTick_Init(void);
void SysTick_wait (uint32_t delay);
void SysTick_wait10ms (uint32_t delay);
void PLL_Init (void);
void SysTickInterrupt_Init(void);//uint32_t period);
void SysTick_wait1msInterrupts(uint32_t delay);
void SysTick_wait100usInterrupts(uint32_t delay);
#endif
