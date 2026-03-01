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
    GPIO_InitPinConfig GPIO_InitGreenLED = {GREEN_LED_PIN, GPIO_MODE_OUTPUT, 0}; // Pin 13, Output Mode, No Alternate Function
    GPIO_InitPinConfig GPIO_InitRedLED = {RED_LED_PIN, GPIO_MODE_OUTPUT, 0}; // Pin 14, Output Mode, No Alternate Function
    GPIO_InitPinConfig GPIO_InitUserButton = {USER_BUTTON_PIN, GPIO_MODE_INPUT, 0}; // Pin 0, Input Mode, No Alternate Function
    gpio_init(GPIOG, &GPIO_InitGreenLED); // Initialize GPIOG Pin 13 for Green LED
    gpio_init(GPIOG, &GPIO_InitRedLED); // Initialize GPIOG Pin 14 for Red LED
    gpio_init(GPIOA, &GPIO_InitUserButton); // Initialize GPIOA Pin 0 for User Button

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
    GPIO_InitPinConfig GPIO_DEBUG_LED0 = {GPIO_PIN_3, GPIO_MODE_OUTPUT, 0}; // PB3 as Debug LED
    GPIO_InitPinConfig GPIO_DEBUG_LED1 = {GPIO_PIN_4, GPIO_MODE_OUTPUT, 0}; // PB4 as Debug LED
    GPIO_InitPinConfig GPIO_DEBUG_LED2 = {GPIO_PIN_5, GPIO_MODE_OUTPUT, 0}; // PB5 as Debug LED
    GPIO_InitPinConfig GPIO_I2C1_SCL = {GPIO_PIN_6, GPIO_MODE_ALTFN, GPIO_OPEN_DRAIN, GPIO_SPEED_FAST, GPIO_PULLUP, GPIO_AF4}; // PB6 as I2C1 SCL
    GPIO_InitPinConfig GPIO_I2C1_SDA = {GPIO_PIN_7, GPIO_MODE_ALTFN, GPIO_OPEN_DRAIN, GPIO_SPEED_FAST, GPIO_PULLUP, GPIO_AF4}; // PB7 as I2C1 SDA
    gpio_init(GPIOB, &GPIO_I2C1_SCL); // Initialize PB6 for I2C1 SCL
    gpio_init(GPIOB, &GPIO_I2C1_SDA); // Initialize PB7 for I2C1 SDA
    gpio_init(GPIOB, &GPIO_DEBUG_LED0); // Initialize PB3 for Debug LED
    gpio_init(GPIOB, &GPIO_DEBUG_LED1); // Initialize PB4 for Debug LED
    gpio_init(GPIOB, &GPIO_DEBUG_LED2); // Initialize PB5 for Debug LED

    uint8_t status = 0;
    status = PCF8574A_Init(I2C1); // Initialize the PCF8574A I/O Expander for LCD Control
    if (STATUS_OK != status) {
        gpio_set_pin(GPIOB, GPIO_PIN_3); // Turn on Debug LED to indicate initialization is complete
        while(1); // Halt execution if initialization fails
    }

    status = LCD_Init(I2C1); // Initialize the LCD Display
    if (STATUS_OK != status) {
        gpio_set_pin(GPIOB, GPIO_PIN_4); // Turn on Debug LED to indicate initialization error
        while(1); // Halt execution if initialization fails
    }

    
    status = LCD_WriteString(I2C1, "Hello, World!"); // Write a test string to the LCD
    //LCD_SendData(I2C1, 0x41); // Write a test byte (A) to the LCD (should display a character if working)
    
    if (STATUS_OK != status) {
        gpio_set_pin(GPIOB, GPIO_PIN_5); // Turn on Debug LED to indicate initialization error
        while(1); // Halt execution if initialization fails
    }

    while (1) {
        //GPIOG->BSRR = RED_LED_MASK | (GREEN_LED_MASK << 16); // LEDs <R|G> : <ON|OFF>
        //gpio_toggle_pin(GPIOG, GREEN_LED_PIN);
        //gpio_toggle_pin(GPIOG, RED_LED_PIN);
        //for (volatile uint32_t i = 0; i < 1000000; i++); // Delay
        if (gpio_read_pin(GPIOA, USER_BUTTON_PIN)) {
            gpio_set_pin(GPIOG, RED_LED_PIN);
            gpio_clear_pin(GPIOG, GREEN_LED_PIN);
        } else {
            gpio_clear_pin(GPIOG, RED_LED_PIN);
            gpio_set_pin(GPIOG, GREEN_LED_PIN);
        }
        //GPIOG->BSRR = (RED_LED_MASK << 16) | GREEN_LED_MASK; // LEDs <R|G> : <OFF|ON>
        //for (volatile uint32_t i = 0; i < 1000000; i++); // Delay
    }
}
