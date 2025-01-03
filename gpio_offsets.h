/*Date: 09/19/24
Auther: Griffin Tedlie
GPIO offsets for setting up and initializing GPIO ports
Includes RCGCGPIO */

#ifndef GPIO_OFFSETS
#define GPIO_OFFSETS

#define RCGCGPIO (*((volatile uint32_t *)0x400FE608U))          //GPIO clock gating register

#define GPIOCR 0x524U                //GPIO commit offset
#define GPIOLOCK 0x520U             //GPIO Lock register, need to unlock for PF0
#define GPIOAMSEL 0x528U             //GPIO Analog Function register
#define GPIOPCTL 0x52CU              //GPIO Port Control
#define GPIODIR 0x400U
#define GPIOAFSEL 0x420U            //GPIO Alternative Function Select Register
#define GPIODEN 0x51C
#define GPIOPDR 0x514U              //GPIO pull down select register
#define GPIOPUR 0x510U             //GPIO pull up select register

#define GPIODATAMASK    0x3FCU              //GPIO data mask, offset is 0x000U
//GPIODATA + GPIODATAMASK IS WHERE TO READ GPIO DATA FROM!!

//UART Below
#define UARTCTL 0x030U              //UART CTL register offset
#define UARTIBRD   0x024U           //UART Integer Baud-Rate Divisor
#define UARTFBRD 0x028U             //UART Integer Baud-Rate Divisor
#define UARTLCRH 0x02CU             //UART Line Control Register
#define UARTFR 0x018U               //UART Flag register, mostly used for FIFO with UART


//GPIO Interrupt Registers below
#define GPIOIS 0x404U              //GPIO Interrupt Sense Register offset
#define GPIOIBE 0x408U             //GPIO Interrupt Both Edges Register offset
#define GPIOIEV 0x40CU             //GPIO Interrupt Event Register offset
#define GPIOIM 0x410U              //GPIO Interrupt Mask Register offset
#define GPIORIS 0x414U             //GPIO Raw Interrupt Status Register offset
#define GPIOICR 0x41CU             //GPIO Interrupt Clear Register offset

//GPIO Open Drain Select below -- used for I2C
#define GPIOODR 0x50CU              //GPIO Open Drain Select


//I2C Below
#define I2CMCR 0x020U               //Master Configuration
#define I2CMTPR 0x00CU              //Master Timer Period for SCL
#define I2CMSA 0x000U               //Master Slave Address
#define I2CMDR 0x008U               //Master Data
#define I2CMCS 0x004U               //Master / Control Status
#define I2CMIMR 0x010U              //Master Interrupt Mask
#define I2CMRIS 0x014U              //Master Raw Interrupt Status


//Peripheral Ready
#define PRGPIO (*((volatile uint32_t *)0x400FEA08))         //GPIO Peripheral Ready, B is bit 1
#define PRI2C (*((volatile uint32_t *)0x400FEA20))          //I2C Perpheral Ready, I2C0 is bit 0

#endif
