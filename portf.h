/*Date: 10/03/24
Author: Griffin Tedlie
Defining preprocessor macro definitions for port A*/


#include "gpio_offsets.h"       //IMPORTANT!!

#ifndef PORT_F_DEFINE
#define PORT_F_DEFINE

#define RCGCGPIO (*((volatile uint32_t *)0x400FE608U))          //GPIO clock gating register

#define GPIOFBASE 0x40025000U      //(*((volatile uint32_t *)0x40025000U))


#define GPIOFCR (*((volatile uint32_t *)(GPIOFBASE + GPIOCR)))
#define GPIOFLOCK (*((volatile uint32_t *)(GPIOFBASE + GPIOLOCK)))

#define GPIOFAMSEL (*((volatile uint32_t *)(GPIOFBASE + GPIOAMSEL)))
#define GPIOFPCTL (* ((volatile uint32_t *) (GPIOFBASE + GPIOPCTL)))
#define GPIOFDIR (*((volatile uint32_t *)(GPIOFBASE + GPIODIR)))
#define GPIOFAFSEL (*((volatile uint32_t *)(GPIOFBASE + GPIOAFSEL)))
#define GPIOFDEN (*((volatile uint32_t *)(GPIOFBASE + GPIODEN)))
#define GPIOFPDR (*((volatile uint32_t *)(GPIOFBASE + GPIOPDR)))
#define GPIOFPUR (*((volatile uint32_t *)(GPIOFBASE + GPIOPUR)))
#define GPIOFDATA (*((volatile uint32_t *)(GPIOFBASE + GPIODATAMASK)))


//Interrupt Registers Below
#define GPIOFIS (*((volatile uint32_t *)(GPIOFBASE + GPIOIS)))       //GPIOF Interrupt Sense Register
#define GPIOFIBE (*((volatile uint32_t *)(GPIOFBASE + GPIOIBE)))     //GPIOF Interrupt Both Edges Register 
#define GPIOFIEV (*((volatile uint32_t *)(GPIOFBASE + GPIOIEV)))     //GPIOF Interrupt Event Register 
#define GPIOFIM (*((volatile uint32_t *)(GPIOFBASE + GPIOIM)))       //GPIOF Interrupt Mask Register
#define GPIOFRIS (*((volatile uint32_t *)(GPIOFBASE + GPIORIS)))    //GPIOF Raw Interrupt Status
#define GPIOFICR (*((volatile uint32_t *)(GPIOFBASE + GPIOICR)))     //GPIOF Interrupt Clear Register
//Interrupt Bit 30 for Port F //TABLE 2-9 ON PAGE 105 OF DATASHEET
//PAge 154 for offset
#define NVIC_PRI7_R (*((volatile uint32_t *)(0xE000E41CU)))           
//Interrupt enable EN0 Page 142 on DATASHEET                                                            
#define NVIC_EN0_R (*((volatile uint32_t *)(0xE000E100U)))           



#endif
