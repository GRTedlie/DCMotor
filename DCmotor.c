/*Date: 10/31/24
Author: Griffin Tedlie
Interrupts using systick interrupts and PWN for DC Motor!!!
I2C0 being used for MPU6050 to obtain orientation erector car
TM4C123 Tiva Launchpad, uC = TM4C123GH6PMI*/

#include <stdio.h>
#include "porta.h" 
#include "portf.h"
#include "portb.h"

#include "SysTick_Init.h"
#include "Init_PortA.h"
#include "Init_PortF.h"
#include "Init_PortB.h"
#include "Init_I2C0.h"                  //I2C0 is PB2, PB3

//declarations for ASM function, in startup_TM4C123.s
void EnableInterrupts(void);            //Enable global interrupts, I=0
void WaitForInterrupt(void);            //low power mode while waiting for next interrupt
void SysTick_Handler(void);             //Branched to when Systick Interrupt occurs
void GPIOPortF_Handler(void);            //Branched to when PortF Interrupt occurs


uint32_t static count;                     //for counting interrupts, global so can be seen in any scope
uint32_t static H , L;                     //H= high for PWM and L= low for PWM
//MPU6050 data; [0:5] = [ACCEL_XOUT[15:8]:ACCEL_ZOUT[7:0]]
//[6:7] = [TEMP_OUT[15:8]:TEMP_OUT[7:0]]
//[8:13] = [GYRO_XOUT[15:8]:GYRO_ZOUT[7:0]]
uint8_t static MPU6050Data[14] = {0};                    

int main(void){

H = L = 50;                   //initialize to 10 and use with SysTick_wait100usInterrupts() 
//H = 35;                        //initialize for TESTING
//L = 21;                        //initialize for TESTING
Init_PortA();                  
Init_PortF();
SysTickInterrupt_Init();       //SysTick Timer w/ interrupts enabled and set to priorty of 2 (3rd highest priority)
PLL_Init();                     //MAKE SURE TO CALL ALL! CLOCK INIT FUNCTIONS!
Init_PortF_EdgeInterrupts();
                 
//EnableInterrupts();             //enable global interrupts, THIS CALLS A FUNCTION IN THE startup_TM4C123.s file!      Prod        

//Initializing SysTick with 100 x 1 ms count
SysTick_wait1msInterrupts(100);
count =0;
//Initialize direction to reverse, Motor 1 and Motor 2
GPIOADATA |= 0x90U;             //PA4, PA7
GPIOADATA &= ~0x48U;            //PA3, PA6

//I2C initialization below
//Init_I2C0_Loopback();                     //testing
//I2C0_Loopback_test();                     //testing

Init_I2C0();                            //Prod
I2C0_Write(0x68, 0x6B, 0x00);           //writing to MPU6050 PWR_MGMT_1 to wake up ;  Prod
MPU6050Data[0] = I2C0_Read(0x68, 0x1B); //Reading from MPU6050, Gyro config reg ; testing
I2C0_Write(0x68, 0x1B, 0x08);           //Writing to MPU6050, Gyro config reg ; testing
MPU6050Data[1] = I2C0_Read(0x68, 0x1B); //Reading back, checking changes; testing

while (1){

//WaitForInterrupt();             //THIS CALLS A FUNCTION IN THE startup_TM4C123.s file! Prod  
count +=1;                        //increment every interrupt

}


    return 0;
}


//New Function for edX Chapter 12 Interrupts
//This function is branched to using the ASM code in startup_TM4C123.s
//Currently having it toggle the RED LED but can put anything 
//in here to happen when Systick count flag is set and throws an interrupt
void SysTick_Handler(void){

GPIOFDATA ^=0x02;                   //Blinky red LED, PF1
if (GPIOADATA & 0x20){              //check if PA5 is high
    GPIOADATA &= ~0x24U;            //toggle PA2, PA5
    SysTick_wait100usInterrupts(L);    //reload SysTick with interrupts with L value for PWM
    }
else{
    GPIOADATA |= 0x24U;             //toggle PA2, PA5
    SysTick_wait100usInterrupts(H);   //reload SysTick with interrupts with H value for PWM
    }

}
//Using range of 10>=H>=100 and 10>=L>=100 which is equivalent to 1ms>=H>=10ms
//PF0 for SW2 and PF4 for SW1
//PA2 for PWM, PA5 for PWM
//PA3, PA4 for DC Motor 1
//PA6, PA7 for DC Motor 2
void GPIOPortF_Handler(void){

if (GPIOFRIS & 0x10U){                      //Checking RIS for SW1, slow down, switch direction if past zero speed
        GPIOFICR |= 0x10U;                  //Clear/ack interrupt for SW1   WAS WRITING TO GPIOFCR NOT GPIOFICR!
            H-=10;
            if (H==0){
                H = 10;
                GPIOADATA ^= 0xF8U;         //Toggle PA3, PA4 and PA6, PA7 to change direction
            }
            L=100-H;
        GPIOFDATA^=0x04;                    //Blinky blue LED, PF2
    }
else if (GPIOFRIS & 0x01U){                 //Checking RIS for SW2, speed up
        GPIOFICR |= 0x01U;                  //Clear/ack interrupt for SW2   WAS WRITING TO GPIOFCR NOT GPIOFICR!!
        if (H<90){
            H+=10;
            L=100-H;
        }
        GPIOFDATA^=0x04;                           //Blinky blue LED, PF2, check
    }
    //GPIOFCR &= ~0x11;                       //Clear/ack noth interrupts no matter what?                    
}
