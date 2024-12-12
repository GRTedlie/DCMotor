/*Date: 10/08/24
Auther: Griffin Tedlie
Init PortB function definition*/

#include <stdint.h>
#include "portb.h"
#include "Init_PortB.h"

void Init_PortB(void){
//Initializing PB0->PB1 to be used as UART1
RCGCGPIO |=0x02U;                       //enabling clock for RCGC Bit 1 for port B
while((RCGCGPIO & 0x02U) ==0 ){}       //wait for port to wake up / be ready
GPIOBAMSEL &= ~0x03U;                   //disabling analog functions for PB0->PB1
GPIOBPCTL &= ~0xFFFFFFFFU;  
GPIOBPCTL |= 0x11U;                     //setting bit 0 and 1 in Port B for UART1, Port Mux control       
//GPIOBDIR |= 0x0FU;                    //PB0->PB3 are outputs 
//GPIOBDIR &= ~0x10U;                   //PB4 is an input
GPIOBAFSEL |= 0x03FU;                   //enabling alternative functions for PB0->PB1
GPIOBDEN |= 0x03U;                      //digital enable PB0->PB1

}
