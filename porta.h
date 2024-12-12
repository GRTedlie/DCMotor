/*Date: 09/26/24
Author: Griffin Tedlie
Defining preprocessor macro definitions for port A
Including UART0*/

#include "gpio_offsets.h"       //IMPORTANT!!

#ifndef PORT_A_DEFINE
#define PORT_A_DEFINE

#define RCGCGPIO (*((volatile uint32_t *)0x400FE608U))          //GPIO clock gating register

#define GPIOABASE 0x40004000U      //(*((volatile uint32_t *)0x40004000U))  

#define GPIOAAMSEL (*((volatile uint32_t *)(GPIOABASE + GPIOAMSEL)))
#define GPIOAPCTL (* ((volatile uint32_t *) (GPIOABASE + GPIOPCTL)))
#define GPIOADIR (*((volatile uint32_t *)(GPIOABASE + GPIODIR)))
#define GPIOAAFSEL (*((volatile uint32_t *)(GPIOABASE + GPIOAFSEL)))
#define GPIOADEN (*((volatile uint32_t *)(GPIOABASE + GPIODEN)))
#define GPIOADATA (*((volatile uint32_t *)(GPIOABASE + GPIODATAMASK)))

//UART Specific below -- UART0 -- PA0 is U0RX -- PA1 is U0TX
#define RCGCUART (*((volatile uint32_t *)0x400FE618U))

#define UART0BASE 0x4000C000U                                             //(*((volatile uint32_t *)0x4000C000))
#define UART0CTL (*((volatile uint32_t *)(UART0BASE + UARTCTL)))        //UART0 Control Register
#define UART0IBRD (*((volatile uint32_t *)(UART0BASE + UARTIBRD)))      //UART0 Integer Baud-Rate Divisor Register
#define UART0FBRD (*((volatile uint32_t *)(UART0BASE + UARTFBRD)))      //UART0 Fraction Baurd-Rate Divisor Register
#define UART0LCRH (*((volatile uint32_t *)(UART0BASE + UARTLCRH)))      //UART0 Line Control Register
#define UART0FR (*((volatile uint32_t *)(UART0BASE +UARTFR)))          //UART0 Flag Register
#define UART0DR (*((volatile uint32_t *)(UART0BASE)))                   //UART Data Register (offset is 0x00)

#endif
