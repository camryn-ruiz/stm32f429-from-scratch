//! @file pcf8574a.c
//! @brief PCF8574A I2C I/O Expander Driver Source File
//! @details
//! > See Header File for details.

#include "pcf8574a.h"
#include "delay.h"

STATUS_CODE PCF8574A_Init(I2C_TypeDef* I2Cx) {
    return I2C_Init(I2Cx, SLOW_MODE, DUTY, 100000); // Initialize I2C in standard mode (100 kHz)
}

STATUS_CODE PCF8574A_WriteByte(I2C_TypeDef* I2Cx, uint8_t data) {
    // Call I2C_Master_Transmit() to send the data byte to the PCF8574A via I2C
    return I2C_Master_Transmit(I2Cx, HLF8574T_I2C_ADDRESS, &data, 1);
}

STATUS_CODE PCF8574A_ReadByte(I2C_TypeDef* I2Cx, uint8_t* data) {
    // Call I2C_Master_Receive() to read a byte of data from the PCF8574A via I2C
    return I2C_Master_Receive(I2Cx, HLF8574T_I2C_ADDRESS, data, 1);
}

STATUS_CODE PCF8574A_LCD_SendNibble(I2C_TypeDef* I2Cx, uint8_t nibble, uint8_t rs) {
    uint8_t data = (nibble << 4) | (rs ? PCF8574A_PIN_RS : 0) | PCF8574A_PIN_BACKLIGHT; // Shift nibble to upper 4 bits, set RS and backlight
    PCF8574A_WriteByte(I2Cx, data); // Send the nibble with RS and backlight
    // Toggle the Enable pin to latch the data into the LCD
    PCF8574A_WriteByte(I2Cx, data | PCF8574A_PIN_EN); // Set EN high
    delay_ms(1); // Short delay for EN pulse width
    PCF8574A_WriteByte(I2Cx, data & ~PCF8574A_PIN_EN); // Set EN low
    delay_ms(1); // Short delay for command execution
    return STATUS_OK;
}

STATUS_CODE PCF8574A_LCD_SendInitNibble(I2C_TypeDef* I2Cx, uint8_t nibble) {
    uint8_t data = (nibble << 4) | PCF8574A_PIN_BACKLIGHT; // RS=0
    PCF8574A_WriteByte(I2Cx, data | PCF8574A_PIN_EN); // EN high
    delay_ms(1); // EN pulse width > 450ns
    PCF8574A_WriteByte(I2Cx, data & ~PCF8574A_PIN_EN); // EN low
    delay_ms(5); // first few init commands require longer delay
    return STATUS_OK;
}

STATUS_CODE PCF8574A_LCD_SendByte(I2C_TypeDef* I2Cx, uint8_t byte, uint8_t rs) {
    PCF8574A_LCD_SendNibble(I2Cx, (byte >> 4) & 0x0F, rs); // Send upper nibble
    PCF8574A_LCD_SendNibble(I2Cx, byte & 0x0F, rs); // Send lower nibble
    return STATUS_OK;
}