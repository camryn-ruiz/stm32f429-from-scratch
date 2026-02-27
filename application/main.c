#include <stdint.h>
#include "stm32f429.h"
#include "rcc.h"
#include "gpio.h"

// STM32F429 Eval Board on Board LEDs:
#define USER_BUTTON_PIN 0U
#define GREEN_LED_PIN 13U
#define RED_LED_PIN 14U
#define GREEN_LED_MASK (1U << GREEN_LED_PIN)
#define RED_LED_MASK (1U << RED_LED_PIN)

void main(void) {
    RCC->AHB1ENR |= (1 << RCC_AHB1ENR_GPIOAEN); // Turn on RCC for GPIOA Peripheral
    RCC->AHB1ENR |= (1 << RCC_AHB1ENR_GPIOGEN); // Turn on RCC for GPIOG Peripheral

    //GPIOG->MODER &= ~((3 << 26) | (3 << 28)); // Clear Bits for Pins 13 & 14
    //GPIOG->MODER |= (1 << 26) | (1 << 28); // Set MODER13=01 & MODER14=01
    gpio_set_mode(GPIOA, USER_BUTTON_PIN, GPIO_MODE_INPUT); // Set PA0 as Input (User Button)
    gpio_set_mode(GPIOG, GREEN_LED_PIN, GPIO_MODE_OUTPUT);
    gpio_set_mode(GPIOG, RED_LED_PIN, GPIO_MODE_OUTPUT);
    gpio_set_pin(GPIOG, GREEN_LED_PIN);

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
