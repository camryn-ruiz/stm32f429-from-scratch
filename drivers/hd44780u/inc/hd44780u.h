#include <stdint.h>
#include "status.h"
#include "pcf8574a.h"
#include "i2c.h"

#ifndef _HD44780U_H
#define _HD44780U_H

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

#endif // _HD44780U_H