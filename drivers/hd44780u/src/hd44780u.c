//! @file hd44780u.c
//! @brief HD44780U LCD Controller Driver Source File
//! @details
//! > See Header File for details.

#include "hd44780u.h"
#include "pcf8574a.h"
#include "delay.h"

STATUS_CODE LCD_Init(I2C_TypeDef* I2Cx) {
    delay_ms(50);
    PCF8574A_LCD_SendInitNibble(I2Cx, 0x03); // Function Set: 8-bit mode (first part of initialization sequence)
    delay_ms(5);
    PCF8574A_LCD_SendInitNibble(I2Cx, 0x03); // Function Set: 8-bit mode (second part of initialization sequence)
    delay_ms(1);
    PCF8574A_LCD_SendInitNibble(I2Cx, 0x03); // Function Set: 8-bit mode (third part of initialization sequence)
    delay_ms(1);
    PCF8574A_LCD_SendInitNibble(I2Cx, 0x02); // Function Set: 4-bit mode
    delay_ms(1);

    LCD_FunctionSet(I2Cx, HD44780U_FUNCTION_FONT_5x10 | HD44780U_FUNCTION_2LINE | HD44780U_FUNCTION_DATA_LENGTH_4BIT);
    LCD_FunctionSet(I2Cx, HD44780U_FUNCTION_FONT_5x10 | HD44780U_FUNCTION_2LINE | HD44780U_FUNCTION_DATA_LENGTH_4BIT);
    LCD_DisplayControl(I2Cx, HD44780U_DISPLAY_ON | HD44780U_DISPLAY_CURSOR_ON | HD44780U_DISPLAY_BLINK_ON);
    LCD_EntryModeSet(I2Cx, HD44780U_ENTRY_MODE_INCREMENT | HD44780U_ENTRY_MODE_SHIFT_OFF);
    LCD_Clear(I2Cx);
    delay_ms(2);
    LCD_ReturnHome(I2Cx);
    delay_ms(2);

    return STATUS_OK;
}

STATUS_CODE LCD_Clear(I2C_TypeDef* I2Cx) {
    return LCD_SendCommand(I2Cx, HD44780U_CMD_CLEAR_DISPLAY);
}

STATUS_CODE LCD_ReturnHome(I2C_TypeDef* I2Cx) {
    return LCD_SendCommand(I2Cx, HD44780U_CMD_RETURN_HOME);
}

STATUS_CODE LCD_FunctionSet(I2C_TypeDef* I2Cx, uint8_t flags) {
    return LCD_SendCommand(I2Cx, HD44780U_CMD_FUNCTION_SET | flags);
}

STATUS_CODE LCD_DisplayControl(I2C_TypeDef* I2Cx, uint8_t flags) {
    return LCD_SendCommand(I2Cx, HD44780U_CMD_DISPLAY_CONTROL | flags);
}

STATUS_CODE LCD_EntryModeSet(I2C_TypeDef* I2Cx, uint8_t flags) {
    return LCD_SendCommand(I2Cx, HD44780U_CMD_ENTRY_MODE_SET | flags);
}

STATUS_CODE LCD_SendCommand(I2C_TypeDef* I2Cx, uint8_t cmd) {
    return PCF8574A_LCD_SendByte(I2Cx, cmd, 0); // RS=0 for command
}

STATUS_CODE LCD_SendData(I2C_TypeDef* I2Cx, uint8_t data) {
    return PCF8574A_LCD_SendByte(I2Cx, data, 1); // RS=1 for data
}

STATUS_CODE LCD_WriteString(I2C_TypeDef* I2Cx, const char* str) { 
    while (*str) {
        LCD_SendData(I2Cx, (uint8_t)(*str)); // Send each character as data
        str++;
    }
    return STATUS_OK;
}

STATUS_CODE LCD_SetCursor(I2C_TypeDef* I2Cx, uint8_t row, uint8_t col) {
    uint8_t address = (row == 0) ? col : (0x40 + col); // Calculate DDRAM address based on row and column (if row == 0 use col, else add 0x40 for second line)
    return LCD_SendCommand(I2Cx, HD44780U_CMD_SET_DDRAM_ADDR | address); // Set DDRAM address to position cursor
}