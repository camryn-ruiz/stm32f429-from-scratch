#ifndef _I2C_H
#define _I2C_H

#include <stdint.h>
#include "status.h"
#include "stm32f429.h"

#define TIMEOUT (100000U) // Arbitrary timeout value for I2C operations

// CR1 Register Bits:
#define I2C_PE      (1U << 0) // Peripheral Enable
#define I2C_START   (1U << 8) // Start Generation
#define I2C_STOP    (1U << 9) // Stop Generation
#define I2C_ACK     (1U << 10) // Acknowledge Enable
#define I2C_POS     (1U << 11) // Acknowledge/PEC Position (for data reception)

// SR1 Register Bits:
#define I2C_SB      (1U << 0) // Start Bit (Master Mode)
#define I2C_ADDR    (1U << 1) // Address Sent/Matched
#define I2C_BTF     (1U << 2) // Byte Transfer Finished
#define I2C_RXNE    (1U << 6) // Data Register Not Empty
#define I2C_TXE     (1U << 7) // Data Register Empty

// SR2 Register Bits:
#define I2C_MSL     (1U << 0) // Master/Slave
#define I2C_BUSY    (1U << 1) // Bus Busy
#define I2C_TRA     (1U << 2) // Transmitter/Receiver

// CCR Register Bits:
#define I2C_FAST_MODE (1U << 15)
#define I2C_SLOW_MODE (0U << 15)
/* Fast mode duty cycle options:
 * 0: T_low/_high = 2
 * 1: T_low/T_high = 16/9
 */
#define I2C_DUTY      (1U << 14) 

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