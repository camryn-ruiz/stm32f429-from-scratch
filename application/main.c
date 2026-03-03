#include <stdint.h>
#include <stdio.h>

#include "delay.h"
#include "gpio.h"
#include "pcf8574a.h"
#include "hd44780u.h"
#include "tcn75a.h"

#define TEMP_INIT_STR "Temp: "
#define TEMP_BUFF_SIZE 16U

void main(void) {
    // Test LEDs and Button Initialization:
    GPIO_InitTypeDef gpioLEDGreen = {GREEN_LED_PIN, GPIO_MODE_OUTPUT, GPIO_PUSH_PULL, GPIO_SPEED_LOW, GPIO_PULL_NONE, GPIO_AF0};
    GPIO_InitTypeDef gpioLEDRed = {RED_LED_PIN, GPIO_MODE_OUTPUT, GPIO_PUSH_PULL, GPIO_SPEED_LOW, GPIO_PULL_NONE, GPIO_AF0};
    GPIO_InitTypeDef gpioUsrBtn = {USER_BUTTON_PIN, GPIO_MODE_INPUT, GPIO_PULLUP, GPIO_SPEED_LOW, GPIO_AF0};
    gpio_init(GPIOG, &gpioLEDGreen);
    gpio_init(GPIOG, &gpioLEDRed);
    gpio_init(GPIOA, &gpioUsrBtn);

    // I2C Pins Initialization:
    // LCD GPIO Initialization:
    GPIO_InitTypeDef gpioDIP1 = {GPIO_PIN_3, GPIO_MODE_INPUT, GPIO_PULL_NONE, GPIO_SPEED_LOW, GPIO_AF0};
    GPIO_InitTypeDef gpioI2C1SCL = {GPIO_PIN_6, GPIO_MODE_ALTFN, GPIO_OPEN_DRAIN, GPIO_SPEED_FAST, GPIO_PULLUP, GPIO_AF4};
    GPIO_InitTypeDef gpioI2C1SDA = {GPIO_PIN_7, GPIO_MODE_ALTFN, GPIO_OPEN_DRAIN, GPIO_SPEED_FAST, GPIO_PULLUP, GPIO_AF4};
    gpio_init(GPIOB, &gpioI2C1SCL);
    gpio_init(GPIOB, &gpioI2C1SDA);
    gpio_init(GPIOB, &gpioDIP1);

    GPIO_InitTypeDef gpioI2C2SCL = {GPIO_PIN_10, GPIO_MODE_ALTFN, GPIO_OPEN_DRAIN, GPIO_SPEED_FAST, GPIO_PULLUP, GPIO_AF4};
    GPIO_InitTypeDef gpioI2C2SDA = {GPIO_PIN_11, GPIO_MODE_ALTFN, GPIO_OPEN_DRAIN, GPIO_SPEED_FAST, GPIO_PULLUP, GPIO_AF4};
    gpio_init(GPIOB, &gpioI2C2SCL);
    gpio_init(GPIOB, &gpioI2C2SDA);

    PCF8574A_Init(I2C1); // Initialize the PCF8574A I/O Expander for LCD Control
    LCD_Init(I2C1);      // Initialize the LCD Display
    LCD_Clear(I2C1);     // Clear the LCD for the main loop messages
    TCN75A_Init(I2C2);   // Initialize the TCN75A Temperature Sensor

    float temperature = 0.0f; // Variable to store temperature reading from TCN75A sensor
    STATUS_CODE status = STATUS_OK;
    char tempStr[TEMP_BUFF_SIZE]; // Buffer to hold formatted temperature string for LCD display
    LCD_WriteString(I2C1, TEMP_INIT_STR); // Initial message on LCD
    
    while (1) {
        status = TCN75A_ReadTemperature(I2C2, &temperature);
        LCD_SetCursor(I2C1, 0, 6); // Set cursor to the position after the first print (only overwrite the temperature value, not the "Temp: " label)
        if (gpio_read_pin(GPIOB, GPIO_PIN_3)) { // Check if DIP Switch 1 is ON (active high)
            gpio_set_pin(GPIOG, GREEN_LED_PIN); // Toggle Green LED to indicate main loop is running
            gpio_set_pin(GPIOG, RED_LED_PIN); // Toggle Green LED to indicate main loop is running
            snprintf(tempStr, sizeof(tempStr), "%.2f C", temperature); // Format temperature reading into string with 2 decimal places
            LCD_WriteString(I2C1, tempStr);
            delay_ms(1000);
        }
        else {
            gpio_clear_pin(GPIOG, GREEN_LED_PIN); // Toggle Green LED to indicate main loop is running
            gpio_clear_pin(GPIOG, RED_LED_PIN); // Toggle Green LED to indicate main loop is running
            snprintf(tempStr, sizeof(tempStr), "%.2f F", temperature * (9.0f/5.0f) + 32.0f); // Format temperature reading into string with 2 decimal places
            LCD_WriteString(I2C1, tempStr);
            delay_ms(1000);
        }
    }
}
