#include <stdint.h>
#include <stdio.h>

#include "delay.h"
#include "gpio.h"
#include "pcf8574a.h"
#include "hd44780u.h"
#include "tcn75a.h"
#include "usart.h"
#include "rcc.h"

#define TEMP_INIT_STR "Temp: "
#define TEMP_BUFF_SIZE 64U
#define INIT_MSG "System Initialized!\r\n"

void uart_init(void) {
    GPIO_InitTypeDef gpiouart4_tx = {GPIO_PIN_10, GPIO_MODE_ALTFN, GPIO_PUSH_PULL, GPIO_SPEED_FAST, GPIO_NONE, GPIO_AF8};
    GPIO_InitTypeDef gpiouart4_rx = {GPIO_PIN_11, GPIO_MODE_ALTFN, GPIO_PULL_NONE, GPIO_SPEED_FAST, GPIO_PULLUP, GPIO_AF8};
    gpio_init(GPIOC, &gpiouart4_tx);
    gpio_init(GPIOC, &gpiouart4_rx);

    // Initialize UART4 for printf output
    // 115200 baud, 1 stop bit, 8 data bits, no parity
    USART_Init(UART4, 115200, STOP_1_BIT, USART_8_DATA_BITS, USART_PARITY_NONE); 
}

void i2c_init(void) {
    // LCD I2C Pins:
    GPIO_InitTypeDef gpioI2C1SCL = {GPIO_PIN_6, GPIO_MODE_ALTFN, GPIO_OPEN_DRAIN, GPIO_SPEED_FAST, GPIO_PULLUP, GPIO_AF4};
    GPIO_InitTypeDef gpioI2C1SDA = {GPIO_PIN_7, GPIO_MODE_ALTFN, GPIO_OPEN_DRAIN, GPIO_SPEED_FAST, GPIO_PULLUP, GPIO_AF4};
    gpio_init(GPIOB, &gpioI2C1SCL);
    gpio_init(GPIOB, &gpioI2C1SDA);

    // Temp Sensor I2C Pins:
    GPIO_InitTypeDef gpioI2C2SCL = {GPIO_PIN_10, GPIO_MODE_ALTFN, GPIO_OPEN_DRAIN, GPIO_SPEED_FAST, GPIO_PULLUP, GPIO_AF4};
    GPIO_InitTypeDef gpioI2C2SDA = {GPIO_PIN_11, GPIO_MODE_ALTFN, GPIO_OPEN_DRAIN, GPIO_SPEED_FAST, GPIO_PULLUP, GPIO_AF4};
    gpio_init(GPIOB, &gpioI2C2SCL);
    gpio_init(GPIOB, &gpioI2C2SDA);

    PCF8574A_Init(I2C1); // Initialize the PCF8574A I/O Expander for LCD Control
    LCD_Init(I2C1);      // Initialize the LCD Display
    LCD_Clear(I2C1);     // Clear the LCD for the main loop messages
    LCD_WriteString(I2C1, TEMP_INIT_STR); // Initial message on LCD

    TCN75A_Init(I2C2);   // Initialize the TCN75A Temperature Sensor
}

void test_init(void) {
    // Test LEDs & Button Initialization:
    GPIO_InitTypeDef gpioLEDGreen = {GREEN_LED_PIN, GPIO_MODE_OUTPUT, GPIO_PUSH_PULL, GPIO_SPEED_LOW, GPIO_PULL_NONE, GPIO_AF0};
    GPIO_InitTypeDef gpioLEDRed = {RED_LED_PIN, GPIO_MODE_OUTPUT, GPIO_PUSH_PULL, GPIO_SPEED_LOW, GPIO_PULL_NONE, GPIO_AF0};
    GPIO_InitTypeDef gpioUsrBtn = {USER_BUTTON_PIN, GPIO_MODE_INPUT, GPIO_PULLUP, GPIO_SPEED_LOW, GPIO_AF0};
    gpio_init(GPIOG, &gpioLEDGreen);
    gpio_init(GPIOG, &gpioLEDRed);
    gpio_init(GPIOA, &gpioUsrBtn);

    GPIO_InitTypeDef gpioDIP1 = {GPIO_PIN_3, GPIO_MODE_INPUT, GPIO_PULL_NONE, GPIO_SPEED_LOW, GPIO_AF0};
    gpio_init(GPIOB, &gpioDIP1);
}

void main(void) {
    SYSCLK_Config(RCC_CFGR_SW_HSI);
    STATUS_CODE status = STATUS_OK;

    uart_init();
    i2c_init();
    test_init();
	delay_ms(50);

    float temperature = 0.0f; // Temperature reading
    char tempStr[TEMP_BUFF_SIZE]; // Buffer for LCD/UART

	USART_TransmitString(UART4, INIT_MSG);

    LCD_Clear(I2C1);
    LCD_SetCursor(I2C1, 0, 0);
    LCD_WriteString(I2C1, "Cels:");       // Label for Celsius
    LCD_SetCursor(I2C1, 1, 0);
    LCD_WriteString(I2C1, "Fahr:");       // Label for Fahrenheit

    while (1) {
        status = TCN75A_ReadTemperature(I2C2, &temperature);
        if (status != STATUS_OK) {
            // Could print error to UART
			USART_TransmitString(UART4, "Temp Read Failed");
            continue;
        }

        // Convert to Celsius integers
        int tempC_int  = (int)temperature;
        int tempC_frac = (int)((temperature - tempC_int) * 100);

        // Convert to Fahrenheit integers
        float tempF = temperature * 9.0f / 5.0f + 32.0f;
        int tempF_int  = (int)tempF;
        int tempF_frac = (int)((tempF - tempF_int) * 100);

        // Prepare strings padded with spaces to clear previous LCD data
        snprintf(tempStr, sizeof(tempStr), "%d.%02d C   ", tempC_int, tempC_frac);
        LCD_SetCursor(I2C1, 0, 6); 
        LCD_WriteString(I2C1, tempStr);

        snprintf(tempStr, sizeof(tempStr), "%d.%02d F   ", tempF_int, tempF_frac);
        LCD_SetCursor(I2C1, 1, 6);
        LCD_WriteString(I2C1, tempStr);

        // Also send to UART for debugging
        snprintf(tempStr, sizeof(tempStr), "Temp: %d.%02d C\r\n", tempC_int, tempC_frac);
        USART_TransmitString(UART4, tempStr);

		snprintf(tempStr, sizeof(tempStr), "Temp: %d.%02d F\r\n", tempF_int, tempF_frac);
		USART_TransmitString(UART4, tempStr);

        // Toggle LEDs based on DIP switch
        if (gpio_read_pin(GPIOB, GPIO_PIN_3)) {
            gpio_set_pin(GPIOG, GREEN_LED_PIN);
            gpio_set_pin(GPIOG, RED_LED_PIN);
        } else {
            gpio_clear_pin(GPIOG, GREEN_LED_PIN);
            gpio_clear_pin(GPIOG, RED_LED_PIN);
        }

        delay_ms(1000);
    }
}
