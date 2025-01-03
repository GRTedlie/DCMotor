/*Date: 09/21/24
Auther: Griffin Tedlie
Init SysTick and PLL function definitions*/

#include "sysTimer.h"
#include "SysTick_Init.h"

void SysTick_Init(void){
NVIC_ST_CTRL_R = 0;                 //Step 1) disable SysTick during setup
//NVIC_ST_RELOAD_R = 0x00FFFFFF;      //Step 2) maximum reload value
NVIC_ST_CURRENT_R = 0;              //Step 3) any write to current clears it
NVIC_ST_CTRL_R = 0x00000005;        //Step 4) enable SysTick with core clock

}


void SysTick_wait(uint32_t delay){
NVIC_ST_RELOAD_R = delay - 1;                    //number of counts to wait
NVIC_ST_CURRENT_R = 0;                           //any write to current clears it
while ((NVIC_ST_CTRL_R & (0x00010000U)) == 0){}  //wait until count flag is set

}

void SysTick_wait10ms (uint32_t delay){
    uint32_t i;
    for (i=0; i<delay; i++){
        SysTick_wait(800000);          //wait 10ms per 1 delay         
    }
}

void PLL_Init(void){
    //Step 0) Use RCC2 because it provides more options/clock divisions
    SYSCTL_RCC2_R |=0x80000000U;                  //setting USERCC2 so that RCC2 overwrites RCC
    //Step 1) bypass PLL while initializing
    SYSCTL_RCC2_R |= 0x00000800U;                //setting BYPASS2, PLL bypass
    //Step 2) select crystal value and oscillator source
    SYSCTL_RCC_R |= (SYSCTL_RCC_R &~0x000007C0U) //clear XTAL field, bits 10-6
         + 0x00000540U;                          //configure for 16 MHZ crystal, 10101
    SYSCTL_RCC2_R &= ~0x00000070U;                 //configure for the main oscilator source
    //Step 3) Activate PLL by clearning PWRDN
    SYSCTL_RCC2_R &= ~0x00002000U;  
    //Step 4) Set the desired system divider
    SYSCTL_RCC2_R |=0x40000000;                 //use the 400 MHz PLL output for divider; DIV400=1
    SYSCTL_RCC2_R = (SYSCTL_RCC2_R &~(0x7FU<<22))   //clearing SYSDIV2 AND SYSDIV2LSB
        +(0x02U<<23);                                   //setting SYSDIV2 for 80 MHz
        //DIV400 is set so using table 5-6 on Pg. 224, using SYSDIV2LSB
    // 400 MHz output / 5 (0x2 = 5 in table 5.6) = 80 MHz clock                     
    //Step 5) Waiting for the PLL to lock by polling PLLLRIS
    while ((SYSCTL_RIS_R & 0x00000040U) == 0){}     //wait for PLLLRIS bit
    //Step 6) Enable use of PLL by clearing BYPASS
    SYSCTL_RCC2_R &= ~0x00000800U;

}

//New Functions for edX Chapter 12 Interrupts
void SysTickInterrupt_Init(void){//uint32_t period){                             
NVIC_ST_CTRL_R = 0;                 //Step 1) Disable SysTick during setup
//NVIC_ST_RELOAD_R = period-1;    //Step 2) Reload value  // This will be taken care of with above functions
NVIC_ST_CURRENT_R = 0;              //Step 3) any write to current clears it
//Step 4) setting SysTick interrupts/exepetion priority level, settgin to 2 here, friendly setting
NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R & 0x00FFFFFFFFU) | 0x40000000U;  
NVIC_ST_CTRL_R = 0x00000007;        //Step 4) enable SysTick with core clock and interrupts enabled
//IMPORTANT: SysTick interrupt is the only interrupt on the TM4C that has an automatic ack
}

//New Functions for edX Chapter 12 Interrupts
//Initializes SysTick with intervals of 1us
//SysTick_wait10ms really only intializes NVIC_ST_RELOAD_R with 800,000 a different # of times
//depending on 'delay' input.
//SysTick_wait1msInterrupts will initialize NVIC_ST_RELOAD_R in intervals of 1 mSecond
void SysTick_wait1msInterrupts(uint32_t delay){
NVIC_ST_RELOAD_R = (80000*delay) - 1;               //number of counts to wait
NVIC_ST_CURRENT_R = 0;                      //any write to current clears it
}

//IMPORTANT: GET GARBAGE RELOAD VALUE IF TRYING TO RELOAD OVER 0X00FFFFFF (MAKES SENSE AS THIS IS THE 
// MAX THAT CAN FIT IN NVIC_ST_RELOAD_R 32 - 8 RESERVED BITS. LIMITING INPUT FOR SysTick_wait1msInterrupts
// is 209 which = 209 *80,000 =16,720,000 = 0xFF207F reload value (16,720,000 - 1))
// and 209.75 = 209.75 *80,000 =  0xFFFFFF


//Going to use below function for PWM at intervals of 8000 which means 8,000 Hz/80,0000,000 MHz 
// = 100 us
void SysTick_wait100usInterrupts(uint32_t delay){   //going to use for PWM at intervals of 800        
NVIC_ST_RELOAD_R = (8000*delay) - 1;                //number of counts to wait
NVIC_ST_CURRENT_R = 0;                              //any write to current clears it
}

