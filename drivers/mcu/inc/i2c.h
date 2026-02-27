#include <stdint.h>
#include "stm32f429.h"
#include "status.h"

#ifndef _I2C_H
#define _I2C_H

// CR1 Register Bits:
#define PE (1U << 0) // Peripheral Enable
#define START (1U << 8) // Start Generation
#define STOP (1U << 9) // Stop Generation
#define ACK (1U << 10) // Acknowledge Enable

// SR1 Register Bits:
#define SB (1U << 0) // Start Bit (Master Mode)
#define ADDR (1U << 1) // Address Sent/Matched
#define BTF (1U << 2) // Byte Transfer Finished
#define TXE (1U << 7) // Data Register Empty

// SR2 Register Bits:
#define MSL (1U << 0) // Master/Slave
#define BUSY (1U << 1) // Bus Busy
#define TRA (1U << 2) // Transmitter/Receiver

    typedef struct {
    uint32_t CR1;
    uint32_t CR2;
    uint32_t OAR1;
    uint32_t OAR2;
    uint32_t DR;
    uint32_t SR1;
    uint32_t SR2;
    uint32_t CCR;
    uint32_t TRISE;
    uint32_t FLTR;
} I2C_TypeDef;

#define I2C1_BASE (APB1_BASE_ADDR + 0x5400)
#define I2C2_BASE (APB1_BASE_ADDR + 0x5800)
#define I2C3_BASE (APB1_BASE_ADDR + 0x5C00)

                                        // SDA | SCL | SMBA
#define I2C1 ((I2C_TypeDef*) I2C1_BASE) // PB7 | PB6 | PB5
#define I2C2 ((I2C_TypeDef*) I2C2_BASE) // PF0 | PF1 | PF2
#define I2C3 ((I2C_TypeDef*) I2C3_BASE) // PC9 | PA8 | PA9

STATUS_CODE I2C_Init(I2C_TypeDef* I2Cx, uint32_t clock_speed);
STATUS_CODE I2C_Start();
STATUS_CODE I2C_Stop();
STATUS_CODE I2C_SendAddress(I2C_TypeDef* I2Cx, uint8_t slave_address, uint8_t direction);
STATUS_CODE I2C_Transmit(I2C_TypeDef* I2Cx, uint8_t* data, uint16_t size);
STATUS_CODE I2C_Receive(I2C_TypeDef* I2Cx, uint8_t* data, uint16_t size);
STATUS_CODE I2C_Master_Transmit(I2C_TypeDef* I2Cx, uint8_t slave_address, uint8_t* data, uint16_t size);
STATUS_CODE I2C_Master_Receive(I2C_TypeDef* I2Cx, uint8_t slave_address, uint8_t* data, uint16_t size);

#endif // _I2C_H