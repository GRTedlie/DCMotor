/*Date: 09/21/24
Auther: Griffin Tedlie
Systick memory mapped registers
Includes functions to delay program using the PLL */

#ifndef SYS_TIMER
#define SYS_TIMER

#include <stdint.h>

/*Systick timer constants below*/
/*SysTick timer exists on ALL Cortex M uCs, a simple counter that can be used to create time delays and generate periodic interrupts*/
/*Without activating the phase-lock-loop (PLL) the TM4C123 launchPad runs at 16 MHz, with PLL activated it runs at 80MHz*/
#define NVIC_ST_CTRL_R (*((volatile uint32_t *)0xE000E010U))
#define NVIC_ST_RELOAD_R (*((volatile uint32_t *)0xE000E014U))
#define NVIC_ST_CURRENT_R (*((volatile uint32_t *)0xE000E018U))

/*RCC and RCC2 constants below*/
/*Run mode clock configuration*/
#define SYSCTL_RCC_R (*((volatile uint32_t *)0x400FE060U))
#define SYSCTL_RIS_R (*((volatile uint32_t *)0x400FE050U))
#define SYSCTL_RCC2_R (*((volatile uint32_t *)0x400FE070U))

/*System Handler Priority 3, this register configures the priority level, 0 to 7 of the SysTick
exception and PendSV handlers. This register is byte accessible. 
Top 3 bits priorty for SysTick interrupts.*/
#define NVIC_SYS_PRI3_R (*((volatile uint32_t *)0xE000ED20U))



#endif
