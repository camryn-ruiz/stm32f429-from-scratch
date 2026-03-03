//! @file pcf8574a.h
//! @brief PCF8574A I2C I/O Expander Driver Header File
//! @details
//! > This Driver is for the PCF8574A I2C I/O Expander, which is an 8-bit I/O expander that communicates via the I2C protocol. 
//! > It provides 8 GPIO pins that can be used for various input/output applications, such as controlling an LCD display or reading button states. 
//! > The PCF8574A has a fixed I2C address of 0x3F (when A0-A2 pins are tied to VCC) and supports both read and write operations for controlling the state of the GPIO pins.

#ifndef PCF8574A_H
#define PCF8574A_H

#include <stdint.h>
#include "i2c.h"

// Originally Made for PCF8574A, but can be used with HLF8574T by changing the I2C address in the source file
#define HLF8574T_I2C_ADDRESS 0x27 // Base address for HLF8574 (A0, A1, A2 all tied to VCC defaults to 0x27)
#define PCF8574A_I2C_ADDRESS 0x3F // Base address for PCF8574A (A0, A1, A2 all tied to VCC defaults to 0x3F)

#define PCF8574A_PIN_RS        (1 << 0U) // Register Select Pin
#define PCF8574A_PIN_RW        (1 << 1U) // Read/Write Pin
#define PCF8574A_PIN_EN        (1 << 2U) // Enable Pin
#define PCF8574A_PIN_BACKLIGHT (1 << 3U) // Backlight Control Pin
#define PCF8574A_PIN_4         (1 << 4U) // Data Pin 4
#define PCF8574A_PIN_5         (1 << 5U) // Data Pin 5
#define PCF8574A_PIN_6         (1 << 6U) // Data Pin 6
#define PCF8574A_PIN_7         (1 << 7U) // Data Pin 7

STATUS_CODE PCF8574A_Init(I2C_TypeDef* I2Cx);
STATUS_CODE PCF8574A_LCD_SendInitNibble(I2C_TypeDef* I2Cx, uint8_t nibble);
STATUS_CODE PCF8574A_WriteByte(I2C_TypeDef* I2Cx, uint8_t data);
STATUS_CODE PCF8574A_ReadByte(I2C_TypeDef* I2Cx, uint8_t* data);
STATUS_CODE PCF8574A_LCD_SendNibble(I2C_TypeDef* I2Cx, uint8_t nibble, uint8_t rs);
STATUS_CODE PCF8574A_LCD_SendByte(I2C_TypeDef* I2Cx, uint8_t byte, uint8_t rs);

#endif // PCF8574A_H