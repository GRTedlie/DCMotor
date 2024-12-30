/*Date: 12/23/24
Auther: Griffin Tedlie
Init I2C0 function declaration
AND I2C0 functions for......*/
#include <stdint.h>

#ifndef PORT_I2C0_INIT
#define PORT_I2C0_INIT

void Init_I2C0(void);
void Init_I2C0_Loopback(void);
void I2C0_Loopback_test(void);
void I2C0_Write(uint8_t slaveAddr, uint8_t regAddr, uint8_t data);
uint8_t I2C0_Read(uint8_t slaveAddr, uint8_t regAddr);


#endif