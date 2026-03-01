#include <stdint.h>
#include "stm32f429.h"
#include "rcc.h"
#include "gpio.h"
#include "i2c.h"
#include "pcf8574a.h"
#include "hd44780u.h"

void main(void) {
    //RCC->AHB1ENR |= (1 << RCC_AHB1ENR_GPIOAEN); // Turn on RCC for GPIOA Peripheral
    //RCC->AHB1ENR |= (1 << RCC_AHB1ENR_GPIOGEN); // Turn on RCC for GPIOG Peripheral
    RCC_EnableGPIOx('A'); // Enable GPIOA Clock
    RCC_EnableGPIOx('G'); // Enable GPIOG Clock
    RCC_EnableI2Cx(1); // Enable I2C1 Clock
    
    // LEDs and Button Initialization:
    GPIO_InitTypeDef gpioInitGreenLED = {GREEN_LED_PIN, GPIO_MODE_OUTPUT, 0}; // Pin 13, Output Mode, No Alternate Function
    GPIO_InitTypeDef gpioInitRedLED = {RED_LED_PIN, GPIO_MODE_OUTPUT, 0}; // Pin 14, Output Mode, No Alternate Function
    GPIO_InitTypeDef gpioInitUserButton = {USER_BUTTON_PIN, GPIO_MODE_INPUT, 0}; // Pin 0, Input Mode, No Alternate Function
    gpio_init(GPIOG, &gpioInitGreenLED); // Initialize GPIOG Pin 13 for Green LED
    gpio_init(GPIOG, &gpioInitRedLED); // Initialize GPIOG Pin 14 for Red LED
    gpio_init(GPIOA, &gpioInitUserButton); // Initialize GPIOA Pin 0 for User Button

    // Deadcode below is just for testing the GPIO functions and can be removed later:
    //GPIOG->MODER &= ~((3 << 26) | (3 << 28)); // Clear Bits for Pins 13 & 14
    //GPIOG->MODER |= (1 << 26) | (1 << 28); // Set MODER13=01 & MODER14=01
    //gpio_set_mode(GPIOA, USER_BUTTON_PIN, GPIO_MODE_INPUT); // Set PA0 as Input (User Button)
    //gpio_set_mode(GPIOG, GREEN_LED_PIN, GPIO_MODE_OUTPUT);
    //gpio_set_mode(GPIOG, RED_LED_PIN, GPIO_MODE_OUTPUT);
    //gpio_set_pin(GPIOG, GREEN_LED_PIN);

    // I2C Pins Initialization:
    RCC_EnableGPIOx('B'); // Enable GPIOB Clock for I2C1 Pins

    // LCD GPIO Initialization:
    GPIO_InitTypeDef gpioDIP1 = {GPIO_PIN_3, GPIO_MODE_INPUT, 0}; // PD3 as DIP Switch 1 Input
    GPIO_InitTypeDef gpioI2C1SCL = {GPIO_PIN_6, GPIO_MODE_ALTFN, GPIO_OPEN_DRAIN, GPIO_SPEED_FAST, GPIO_PULLUP, GPIO_AF4}; // PB6 as I2C1 SCL
    GPIO_InitTypeDef gpioI2C1SDA = {GPIO_PIN_7, GPIO_MODE_ALTFN, GPIO_OPEN_DRAIN, GPIO_SPEED_FAST, GPIO_PULLUP, GPIO_AF4}; // PB7 as I2C1 SDA
    gpio_init(GPIOB, &gpioI2C1SCL); // Initialize PB6 for I2C1 SCL
    gpio_init(GPIOB, &gpioI2C1SDA); // Initialize PB7 for I2C1 SDA
    gpio_init(GPIOB, &gpioDIP1); // Initialize PD3 for DIP Switch 1 Input

    uint8_t status = 0;
    status = PCF8574A_Init(I2C1); // Initialize the PCF8574A I/O Expander for LCD Control
    if (STATUS_OK != status) {
        while(1); // Halt execution if initialization fails
    }

    status = LCD_Init(I2C1); // Initialize the LCD Display
    if (STATUS_OK != status) {
        while(1); // Halt execution if initialization fails
    }

    status = LCD_WriteString(I2C1, "Hello, World!"); // Write a test string to the LCD
    delay_ms(2000); // Delay to allow reading the initial message
    LCD_Clear(I2C1); // Clear the LCD for the main loop messages
    
    if (STATUS_OK != status) {
        while(1); // Halt execution if initialization fails
    }

    int toggle = !gpio_read_pin(GPIOB, GPIO_PIN_3); // Variable to track button state for LCD updates
    while (1) {
        //GPIOG->BSRR = RED_LED_MASK | (GREEN_LED_MASK << 16); // LEDs <R|G> : <ON|OFF>
        //gpio_toggle_pin(GPIOG, GREEN_LED_PIN);
        //gpio_toggle_pin(GPIOG, RED_LED_PIN);
        //for (volatile uint32_t i = 0; i < 1000000; i++); // Delay
        if (gpio_read_pin(GPIOB, GPIO_PIN_3)) {
            gpio_set_pin(GPIOG, RED_LED_PIN);
            gpio_clear_pin(GPIOG, GREEN_LED_PIN);
            if (toggle == 0) {
                LCD_Clear(I2C1); // Clear LCD before writing new message
                delay_ms(2); // Short delay to ensure LCD is cleared before writing new messages
                LCD_WriteString(I2C1, "Button Pressed!"); // Update LCD when button is pressed
                toggle = 1;
            }
        } else {
            gpio_clear_pin(GPIOG, RED_LED_PIN);
            gpio_set_pin(GPIOG, GREEN_LED_PIN);
            if (toggle == 1) {
                LCD_Clear(I2C1); // Clear LCD before writing new message
                delay_ms(2); // Short delay to ensure LCD is cleared before writing new messages
                LCD_WriteString(I2C1, "Button Released!"); // Update LCD when button is released
                toggle = 0;
            }
        }
        //GPIOG->BSRR = (RED_LED_MASK << 16) | GREEN_LED_MASK; // LEDs <R|G> : <OFF|ON>
        //for (volatile uint32_t i = 0; i < 1000000; i++); // Delay
    }
}
