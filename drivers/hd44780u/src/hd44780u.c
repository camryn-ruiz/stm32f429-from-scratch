#include "hd44780u.h"

STATUS_CODE LCD_Init(void) {
    LCD_FunctionSet(HD44780U_FUNCTION_FONT_5x10 | HD44780U_FUNCTION_2LINE | HD44780U_FUNCTION_DATA_LENGTH_8BIT);
    LCD_DisplayControl(HD44780U_DISPLAY_ON | HD44780U_DISPLAY_CURSOR_ON | HD44780U_DISPLAY_BLINK_ON);
    LCD_EntryModeSet(HD44780U_ENTRY_MODE_INCREMENT | HD44780U_ENTRY_MODE_SHIFT_OFF);

    return STATUS_OK;
}

STATUS_CODE LCD_Clear(void) {
    return STATUS_OK;
}

STATUS_CODE LCD_ReturnHome(void) {
    return STATUS_OK;
}

STATUS_CODE LCD_FunctionSet(uint8_t flags) {
    return STATUS_OK;
}

STATUS_CODE LCD_DisplayControl(uint8_t flags) {
    return STATUS_OK;
}

STATUS_CODE LCD_EntryModeSet(uint8_t flags) {
    return STATUS_OK;
}

STATUS_CODE LCD_SendCommand(uint8_t cmd) {
    return STATUS_OK;
}

STATUS_CODE LCD_SendData(uint8_t data) {
    return STATUS_OK;
}

STATUS_CODE LCD_WriteString(const char* str) { 
    return STATUS_OK;
}

STATUS_CODE LCD_WriteByte(uint8_t data) {
    // Call I2C_Master_Transmit() to send the data byte to the LCD via I2C
    // Send to PCF8574 I2C expander at address 0x??
    // 

    return STATUS_OK;
}