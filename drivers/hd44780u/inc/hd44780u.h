//! @file hd44780u.h
//! @brief HD44780U LCD Controller Driver Header File
//! @details
//! > This Driver is for the HD44780U LCD Controller, which is a widely used character LCD controller with a 5x8 or 5x10 dot matrix for each character.
//! > It supports both 4-bit and 8-bit data bus modes and provides various display control options such as cursor on/off, blink on/off, and display on/off.
//! > The LCD is controlled via an I2C-based PCF8574A I/O expander, which allows for communication with the LCD using only 2 I2C lines (SCL and SDA) and 
//! > provides 8 GPIO pins to control the LCD's RS, RW, E, and data lines (D4-D7 in 4-bit mode).

#ifndef _HD44780U_H
#define _HD44780U_H

#include <stdint.h>
#include "i2c.h"

// HD44780U Command Instructions:
#define HD44780U_CMD_CLEAR_DISPLAY       0x01
#define HD44780U_CMD_RETURN_HOME         0x02
#define HD44780U_CMD_ENTRY_MODE_SET      0x04
#define HD44780U_CMD_DISPLAY_CONTROL     0x08
#define HD44780U_CMD_CURSOR_SHIFT        0x10
#define HD44780U_CMD_FUNCTION_SET        0x20
#define HD44780U_CMD_SET_CGRAM_ADDR      0x40
#define HD44780U_CMD_SET_DDRAM_ADDR      0x80

// Entry Mode Set Options:
#define HD44780U_ENTRY_MODE_DECREMENT   0x00
#define HD44780U_ENTRY_MODE_INCREMENT   0x02
#define HD44780U_ENTRY_MODE_SHIFT_OFF   0x00
#define HD44780U_ENTRY_MODE_SHIFT_ON    0x01

// Display Control Options:
#define HD44780U_DISPLAY_BLINK_OFF   0x00
#define HD44780U_DISPLAY_BLINK_ON    0x01
#define HD44780U_DISPLAY_CURSOR_OFF  0x00
#define HD44780U_DISPLAY_CURSOR_ON   0x02
#define HD44780U_DISPLAY_OFF         0x00
#define HD44780U_DISPLAY_ON          0x04
// Cursor/Display Shift Options:
#define HD44780U_SHIFT_DISPLAY 0x08
#define HD44780U_SHIFT_CURSOR  0x00
#define HD44780U_SHIFT_LEFT    0x00
#define HD44780U_SHIFT_RIGHT   0x04

// Function Set Options:
#define HD44780U_FUNCTION_FONT_5x8         0x00
#define HD44780U_FUNCTION_FONT_5x10        0x04
#define HD44780U_FUNCTION_1LINE            0x00
#define HD44780U_FUNCTION_2LINE            0x08
#define HD44780U_FUNCTION_DATA_LENGTH_4BIT 0x00
#define HD44780U_FUNCTION_DATA_LENGTH_8BIT 0x10

STATUS_CODE LCD_Init(I2C_TypeDef* I2Cx);
STATUS_CODE LCD_Clear(I2C_TypeDef* I2Cx);
STATUS_CODE LCD_ReturnHome(I2C_TypeDef* I2Cx);
STATUS_CODE LCD_FunctionSet(I2C_TypeDef* I2Cx, uint8_t flags);
STATUS_CODE LCD_DisplayControl(I2C_TypeDef* I2Cx, uint8_t flags);
STATUS_CODE LCD_EntryModeSet(I2C_TypeDef* I2Cx, uint8_t flags);
STATUS_CODE LCD_SendCommand(I2C_TypeDef* I2Cx, uint8_t cmd);
STATUS_CODE LCD_SendData(I2C_TypeDef* I2Cx, uint8_t data);
STATUS_CODE LCD_WriteString(I2C_TypeDef* I2Cx, const char* str);
STATUS_CODE LCD_SetCursor(I2C_TypeDef* I2Cx, uint8_t row, uint8_t col);

#endif // _HD44780U_H