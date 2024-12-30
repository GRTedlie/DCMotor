/*Date: 12/23/24
Author: Griffin Tedlie
I2C0 initialization
AND I2C0 functions for......*/

//I2C Specific below -- I2C0 --- PB2 is I2C0SCL , PB3 is I2C0SDA
#include <stdint.h>
#include "portb.h"

void Init_I2C0(void){
    RCGCI2C |= 0x01U;                       //Enable I2C0 and provide clock to I2C0
    while ((RCGCI2C & 0x01U) == 0){}        //Wait until I2C0 port awake
    //MCR MTPR
    I2C0MCR= ((I2C0MCR &~ 0x20U) | 0x10U);  //Master Function enabled, slave disabled
    //I2COMCR |= 0x01U;                     //Enable loopback Test Mode
    I2C0MTPR = 0x27U;                       //Setting the SCL clock, high-speed mode not enabled
    //Setting SCL-PERIOD AT 0X27U BASED ON TABLE ON PAGE 1004 AND BELOW CALCULATION, THIS GIVES 100kHz I2C clock
    /*SCL_PERIOD = 2x(1+TPR) x (SCL_LP +  SCP_HP) x CLK_PRD
    where :
    SCL_PRD is the SCL line period (I2C clock).
    TPR is the Timer Period register value (range of 1 to 127).
    SCL_LP is the SCL Low period (fixed at 6).
    SCL_HP is the SCL High period (fixed at 4).
    CLK_PRD is the system clock period in ns.
    */
}


void Init_I2C0_Loopback(void){
    RCGCI2C |= 0x01U;                       //Enable I2C0 and provide clock to I2C0
    while ((RCGCI2C & 0x01U) == 0){}        //Wait until I2C0 port awake
    //MCR MTPR
    I2C0MCR= ((I2C0MCR &~ 0x20U) | 0x10U);  //Master Function enabled, slave disabled
    I2C0MCR |= 0x01U;                       //Enable loopback Test Mode
    I2C0MTPR = 0x27U;                       //Setting the SCL clock, high-speed mode not enabled
}

void I2C0_Loopback_test(void){
    uint8_t sendTestData = 0x24;
    uint8_t receiveTestData;

    I2C0MDR = sendTestData;                 //load test data byte into I2C0 data register
    I2C0MCS = 0x03;                         //START, RUN
    while(I2C0MCS & 0x01);                  //wait for I2C controller not busy      

    I2C0MCS = 0x07;                         //START, RUN, STOP
    receiveTestData = I2C0MDR;              //read data from data register into receiveTestData

    if (receiveTestData == sendTestData){
        //I2C loopback test successful
    }

    if (receiveTestData != sendTestData){
        //I2C loopback test not successful
    }

}


void I2C0_Write(uint8_t slaveAddr, uint8_t regAddr, uint8_t data){
    I2C0MSA = (slaveAddr << 1) & 0xFE;      //Slave Address, write mode 
    I2C0MDR = regAddr;                      //Reg address want to send data to on device
    I2C0MCS = 0x03;                         //START, RUN
    while (I2C0MCS & 0x01);                 //wait for I2C controller not busy

    if (I2C0MCS & 0x02){                    //check for errors
    I2C0MCS = 0x4;                          //stop I2C data transfer  
    return;                                 //return from write function
    }

    //Sending data now to regAddr of device at slaveAddr
    I2C0MDR = data;  
    I2C0MCS = 0x5;                          //RUN, STOP
    while (I2C0MCS & 0x01);                 //wait for I2C controller not busy
}

uint8_t I2C0_Read(uint8_t slaveAddr, uint8_t regAddr){
    I2C0MSA = (slaveAddr << 1) & 0xFE;      //Slave Address, write mode
    I2C0MDR = regAddr;                      //reg address want to read from
    I2C0MCS = 0x03;                         //START, RUN
    while (I2C0MCS & 0x01);                 //wait for I2C controller not busy

    if (I2C0MCS & 0x02){                    //check for errors
    I2C0MCS = 0x4;                          //stop I2C data transfer  
    return;                                 //return from read function
    }

    //Reading data now from regAddr of device at slaveAddr
    I2C0MSA = (slaveAddr << 1) | 0x01;      //Slave Address, read mode 
    I2C0MCS = 0x7;                          //START, RUN, STOP
    while (I2C0MCS & 0x01);                 //wait for I2C controller not busy

    return  I2C0MDR;                        //return data read

}

    /*//I2C Specific below -- I2C0 --- PB2 is I2C0SCL , PB3 is I2C0SDA
#define RCGCI2C (*((volatile uint32_t* )0x400FE620U))

#define I2C0BASE 0x4002000
#define I2C0MSA (*((volatile uint32_t*)(I2C0BASE + I2CMSA)))            //I2C0 Master Slave Address
#define I2C0MCS (*((volatile uint32_t*)(I2C0BASE + I2CMCS)))            //I2C0 Master Control/Status
#define I2C0MDR (*((volatile uint32_t*)(I2C0BASE + I2CMDR)))            //I2C0 Master Data
#define I2C0MTPR (*((volatile uint32_t*)(I2C0BASE + I2CMTPR)))          //I2C0 Master Timer Period for SCL
#define I2C0MCR (*((volatile uint32_t*)(I2C0BASE + I2CMCR)))            //I2C0 Master Configuration

*/