/*Date: 09/26/24
Auther: Griffin Tedlie
Init PortA function definition
PA2 for Motor 1 PWM
PA3, PA4 for motor 1 direction control
PA5 for Motor 2 PWM
PA6, PA7 for motor 2 direction control */

#include <stdint.h>
#include "porta.h"
#include "Init_PortA.h"

void Init_PortA(void){
//Initializing PA2->PA7
RCGCGPIO |=0x01U;                   //enabling clock for RCGC Bit 0 for port A
while((RCGCGPIO & 0x01U) ==0 ){}    //wait for port to wake up / be ready
GPIOAAMSEL &= ~0xFCU;               //disabling analog functions for PA3->PA7
GPIOAPCTL &= ~0xFFFFFFFFU;     
GPIOADIR |=0xFCU;                   //set PA3->PA7 to be an output             
GPIOAAFSEL &= ~0xFCU;              //disabling alternative function for PA3->PA7
GPIOADEN |= 0xFCU;                  //enable digital functionality on PA3->PA7 

}
