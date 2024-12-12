/*Date: 10/03/24
Author: Griffin Tedlie
Init PortF function definition
Initializing PF1 for the Launchpad red LED,
PF0 for SW2 and PF4 for SW1*/

#include <stdint.h>
#include "portf.h"
#include "Init_PortF.h"


void Init_PortF(void){
//Initializing PF1 red LED in Port F, PF0 User SW2, and PF4 User SW1
//and PF2 blue LED
RCGCGPIO |=0x20U;                    //enabling clock for RCGC Bit 5 for port F
while((RCGCGPIO & 0x20U) ==0 ){}   //wait for port to wake up / be ready
GPIOFLOCK = 0x4C4F434BU;            //unlocking lock register according to datasheet
GPIOFCR |=0x01U;                    //GPIO PF0 can now be used
GPIOFAMSEL &=~0x17U;                //disabling analog functions for PF0, PF1, PF2, PF4
GPIOFPCTL &=~0xFFFFFFFFU;           //clearing CTL bits to select digital function of pins
GPIOFDIR |=0x06U;                   //PF1 and PF2 as an output
GPIOFDIR &= ~0x11U;                 //PF0 and PF4 as inputs
GPIOFAFSEL &= ~0x17U;               //disable alternative function for PF0, PF1, PF2, PF4
GPIOFDEN |=0x17U;                   //digital enable PF0, PF1, PF2, PF4
                                    //ON BOARD SWITCHES ARE NEGATIVE LOGIC SO REQUIRE PUR!
GPIOFPUR |=0x11U;                   //pull=up resisotrs for SW2 (PF0) and SW1 (PF4)

}

//Below is function to configure PF4 (SW1) and PF0 (SW2) for edge interrupts!
void Init_PortF_EdgeInterrupts(void){
GPIOFIS &= ~0x11U;                  //Clearing Interrupt Sense to config for edge trigger not level
GPIOFIBE &= ~0x11U;                 //Clearing Interrupt both edges
GPIOFIEV &= ~0x11U;                 //Clearing Interrupt Event to define active edge as falling edge
GPIOFICR |= 0x11U;                  //Clear interrupt flags
GPIOFIM |= 0x11U;                   //Arm interrupts for PF4 and PF0
//clearing the priority field for interrupt 30 and then setting to 2 to math systick interrupt level
NVIC_PRI7_R = (NVIC_PRI7_R & 0xFF00FFFF) | 0x00400000U;     
NVIC_EN0_R = 0x40000000U;          //Enabling interrupt 30 in NVIC

}

/*The NVIC_PRI7_R register is laid out as follows:

Bits 31–24: Priority for Interrupt 31.
Bits 23–16: Priority for Interrupt 30 (GPIO Port F).
Bits 15–8: Priority for Interrupt 29.
Bits 7–0: Priority for Interrupt 28.
Each interrupt's priority uses the upper 3 bits of its respective byte.*/
