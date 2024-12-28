/*Date: 10/08/24
Auther: Griffin Tedlie
Init PortB function definition*/

#include <stdint.h>
#include "portb.h"
#include "Init_PortB.h"

void Init_PortB(void){
//PB0->PB1 can be used as UART1
//Initializing I2C0 --- PB2 is I2C0SCL ; PB3 is I2C0SDA
RCGCGPIO |=0x02U;                       //enabling clock for RCGC Bit 1 for port B
while((RCGCGPIO & 0x02U) ==0 ){}       //wait for port to wake up / be ready
GPIOBAMSEL &= ~0x0CU;                   //disabling analog functions for PB2,PB3
GPIOBPCTL &= ~0xFFFFFFFFU;  
GPIOBPCTL |= 0x3300U;                   //setting bit 2 , 3 in Port B for I2C0, Port Mux control       
//GPIOBDIR |= 0x0FU;                    //PB0,PB3 are outputs 
//GPIOBDIR &= ~0x10U;                   //PB4 is an input
GPIOBAFSEL |= 0x0CU;                   //enabling alternative functions for PB2,PB3
GPIOBDEN |= 0x0CU;                      //digital enable PB2,PB3
GPIOBODR |= 0x08U;                      //Setting PB3 to open drain for I2C0SDA

}
