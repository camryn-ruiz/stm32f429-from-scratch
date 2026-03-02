#include <stdint.h>
#include <stdio.h>
#include "stm32f429.h"
#include "rcc.h"
#include "gpio.h"
#include "i2c.h"
#include "pcf8574a.h"
#include "hd44780u.h"
#include "tcn75a.h"

void main(void) {
    RCC_EnableGPIOx('A'); // Enable GPIOA Clock
    RCC_EnableGPIOx('B'); // Enable GPIOB Clock for I2C1 Pins
    RCC_EnableGPIOx('G'); // Enable GPIOG Clock
    RCC_EnableI2Cx(1); // Enable I2C1 Clock
    
    // LEDs and Button Initialization:
    GPIO_InitTypeDef gpioInitGreenLED = {GREEN_LED_PIN, GPIO_MODE_OUTPUT, 0}; // Pin 13, Output Mode, No Alternate Function
    GPIO_InitTypeDef gpioInitRedLED = {RED_LED_PIN, GPIO_MODE_OUTPUT, 0}; // Pin 14, Output Mode, No Alternate Function
    GPIO_InitTypeDef gpioInitUserButton = {USER_BUTTON_PIN, GPIO_MODE_INPUT, 0}; // Pin 0, Input Mode, No Alternate Function
    gpio_init(GPIOG, &gpioInitGreenLED); // Initialize GPIOG Pin 13 for Green LED
    gpio_init(GPIOG, &gpioInitRedLED); // Initialize GPIOG Pin 14 for Red LED
    gpio_init(GPIOA, &gpioInitUserButton); // Initialize GPIOA Pin 0 for User Button

    // I2C Pins Initialization:
    // LCD GPIO Initialization:
    GPIO_InitTypeDef gpioDIP1 = {GPIO_PIN_3, GPIO_MODE_INPUT, 0}; // PD3 as DIP Switch 1 Input
    GPIO_InitTypeDef gpioI2C1SCL = {GPIO_PIN_6, GPIO_MODE_ALTFN, GPIO_OPEN_DRAIN, GPIO_SPEED_FAST, GPIO_PULLUP, GPIO_AF4}; // PB6 as I2C1 SCL
    GPIO_InitTypeDef gpioI2C1SDA = {GPIO_PIN_7, GPIO_MODE_ALTFN, GPIO_OPEN_DRAIN, GPIO_SPEED_FAST, GPIO_PULLUP, GPIO_AF4}; // PB7 as I2C1 SDA
    gpio_init(GPIOB, &gpioI2C1SCL); // Initialize PB6 for I2C1 SCL
    gpio_init(GPIOB, &gpioI2C1SDA); // Initialize PB7 for I2C1 SDA
    gpio_init(GPIOB, &gpioDIP1); // Initialize PD3 for DIP Switch 1 Input

    RCC_EnableI2Cx(2); // Enable I2C2 Clock for Temperature Sensor
    GPIO_InitTypeDef gpioI2C2SCL = {GPIO_PIN_10, GPIO_MODE_ALTFN, GPIO_OPEN_DRAIN, GPIO_SPEED_FAST, GPIO_PULLUP, GPIO_AF4}; // PB10 as I2C2 SCL
    GPIO_InitTypeDef gpioI2C2SDA = {GPIO_PIN_11, GPIO_MODE_ALTFN, GPIO_OPEN_DRAIN, GPIO_SPEED_FAST, GPIO_PULLUP, GPIO_AF4}; // PB11 as I2C2 SDA
    gpio_init(GPIOB, &gpioI2C2SCL); // Initialize PB10 for I2C2 SCL
    gpio_init(GPIOB, &gpioI2C2SDA); // Initialize PB11 for I2C2 SDA

    //STATUS_CODE status = STATUS_OK;
    PCF8574A_Init(I2C1); // Initialize the PCF8574A I/O Expander for LCD Control
    LCD_Init(I2C1); // Initialize the LCD Display
    LCD_Clear(I2C1); // Clear the LCD for the main loop messages
    TCN75A_Init(I2C2); // Initialize the TCN75A Temperature Sensor

    int toggle = !gpio_read_pin(GPIOB, GPIO_PIN_3); // Variable to track button state for LCD updates
    float temperature = 0.0f; // Variable to store temperature reading from TCN75A sensor
    STATUS_CODE status = STATUS_OK;
    char tempStr[16]; // Buffer to hold formatted temperature string for LCD display
    LCD_WriteString(I2C1, "Temp: "); // Initial message on LCD
    while (1) {
        status = TCN75A_ReadTemperature(I2C2, &temperature); // Read temperature from TCN75A sensor at address 0x48
        LCD_SetCursor(I2C1, 0, 6); // Set cursor to the position after the first print (only overwrite the temperature value, not the "Temp: " label)
        if (gpio_read_pin(GPIOB, GPIO_PIN_3)) { // Check if DIP Switch 1 is ON (active high)
            snprintf(tempStr, sizeof(tempStr), "%.2f C", temperature); // Format temperature reading into string with 2 decimal places
            LCD_WriteString(I2C1, tempStr); // Write Status OK
            delay_ms(1000); // Delay to allow user to read status message before writing temperature value
        }
        else {

            snprintf(tempStr, sizeof(tempStr), "%.2f F", temperature * (9.0f/5.0f) + 32.0f); // Format temperature reading into string with 2 decimal places
            LCD_WriteString(I2C1, tempStr); // Write Status Not OK
            delay_ms(1000); // Delay to allow user to read error message before next attempt
        }
    }
}
