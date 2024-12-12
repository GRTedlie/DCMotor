/*Date: 10/08/24
Auther: Griffin Tedlie
Defining general constants for port B offsets
*/
#include "gpio_offsets.h"       //IMPORTANT!!

#ifndef PORT_B_DEFINE
#define PORT_B_DEFINE

#define RCGCGPIO (*((volatile uint32_t *)0x400FE608U))          //GPIO clock gating register

#define GPIOBBASE 0x40005000U      //(*((volatile uint32_t *)0x40005000U))

#define GPIOBAMSEL (*((volatile uint32_t *)(GPIOBBASE + GPIOAMSEL)))
#define GPIOBPCTL (* ((volatile uint32_t *) (GPIOBBASE + GPIOPCTL)))
#define GPIOBDIR (*((volatile uint32_t *)(GPIOBBASE + GPIODIR)))
#define GPIOBAFSEL (*((volatile uint32_t *)(GPIOBBASE + GPIOAFSEL)))
#define GPIOBDEN (*((volatile uint32_t *)(GPIOBBASE + GPIODEN)))
#define GPIOBDATA (*((volatile uint32_t *)(GPIOBBASE + GPIODATAMASK)))

//UART Specific below -- UART1 -- PB0 is U1RX -- PB1 is U1TX
#define RCGCUART (*((volatile uint32_t *)0x400FE618U))

#define UART1BASE 0x4000D000U                                             //(*((volatile uint32_t *)0x4000C000))
#define UART1CTL (*((volatile uint32_t *)(UART1BASE + UARTCTL)))        //UART0 Control Register
#define UART1IBRD (*((volatile uint32_t *)(UART1BASE + UARTIBRD)))      //UART0 Integer Baud-Rate Divisor Register
#define UART1FBRD (*((volatile uint32_t *)(UART1BASE + UARTFBRD)))      //UART0 Fraction Baurd-Rate Divisor Register
#define UART1LCRH (*((volatile uint32_t *)(UART1BASE + UARTLCRH)))      //UART0 Line Control Register
#define UART1FR (*((volatile uint32_t *)(UART1BASE +UARTFR)))          //UART0 Flag Register
#define UART1DR (*((volatile uint32_t *)(UART1BASE)))                   //UART Data Register (offset is 0x00)

#endif
