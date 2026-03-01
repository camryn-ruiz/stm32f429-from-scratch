#include <stdint.h>
#include "status.h"

#ifndef _I2C_H
#define _I2C_H

#define TIMEOUT (100000U) // Arbitrary timeout value for I2C operations

// CR1 Register Bits:
#define PE      (1U << 0) // Peripheral Enable
#define START   (1U << 8) // Start Generation
#define STOP    (1U << 9) // Stop Generation
#define ACK     (1U << 10) // Acknowledge Enable
#define POS     (1U << 11) // Acknowledge/PEC Position (for data reception)

// SR1 Register Bits:
#define SB      (1U << 0) // Start Bit (Master Mode)
#define ADDR    (1U << 1) // Address Sent/Matched
#define BTF     (1U << 2) // Byte Transfer Finished
#define RXNE    (1U << 6) // Data Register Not Empty
#define TXE     (1U << 7) // Data Register Empty

// SR2 Register Bits:
#define MSL     (1U << 0) // Master/Slave
#define BUSY    (1U << 1) // Bus Busy
#define TRA     (1U << 2) // Transmitter/Receiver

// CCR Register Bits:
#define FAST_MODE (1U << 15)
#define SLOW_MODE (0U << 15)
/* Fast mode duty cycle options:
 * 0: T_low/_high = 2
 * 1: T_low/T_high = 16/9
 */
#define DUTY      (1U << 14) 

typedef struct {
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t OAR1;
    volatile uint32_t OAR2;
    volatile uint32_t DR;
    volatile uint32_t SR1;
    volatile uint32_t SR2;
    volatile uint32_t CCR;
    volatile uint32_t TRISE;
    volatile uint32_t FLTR;
} I2C_TypeDef;

enum TransferDirection {
    I2C_WRITE = 0,
    I2C_READ = 1
};

STATUS_CODE I2C_Init(I2C_TypeDef* I2Cx, uint16_t mode, uint16_t duty_cycle, uint32_t clock_speed);
STATUS_CODE I2C_ClockConfig(I2C_TypeDef* I2Cx, uint16_t mode, uint16_t duty_cycle, uint32_t clock_speed);
STATUS_CODE I2C_Start(I2C_TypeDef* I2Cx);
void I2C_Stop(I2C_TypeDef* I2Cx);
STATUS_CODE I2C_SendAddress(I2C_TypeDef* I2Cx, uint8_t slave_address, uint8_t direction);
STATUS_CODE I2C_Transmit(I2C_TypeDef* I2Cx, uint8_t* data, uint16_t size);
STATUS_CODE I2C_Receive(I2C_TypeDef* I2Cx, uint8_t* data, uint16_t size);
STATUS_CODE I2C_Master_Transmit(I2C_TypeDef* I2Cx, uint8_t slave_address, uint8_t* data, uint16_t size);
STATUS_CODE I2C_Master_Receive(I2C_TypeDef* I2Cx, uint8_t slave_address, uint8_t* data, uint16_t size);

#endif // _I2C_H