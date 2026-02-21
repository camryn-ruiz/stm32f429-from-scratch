#include <stdint.h>
#include "gpio.h"

// AHB1 Peripheral:
#define PERIPHERAL_BASE (0x40000000U)
#define AHB1_BASE_ADDR (PERIPHERAL_BASE + 0x20000U)

// RCC Peripheral:
#define RCC_BASE (AHB1_BASE_ADDR + 0x3800)
#define RCC_AHB1ENR_OFFSET (0x30U)
#define RCC_AHB1ENR_GPIOGEN (0x06U)
#define RCC_AHB1ENR ((volatile uint32_t*) (RCC_BASE + RCC_AHB1ENR_OFFSET))

// STM32F429 Eval Board on Board LEDs:
#define GREEN_LED_PIN 13U
#define RED_LED_PIN 14U
#define GREEN_LED_MASK (1U << GREEN_LED_PIN)
#define RED_LED_MASK (1U << RED_LED_PIN)

void main(void) {
    *RCC_AHB1ENR |= (1 << RCC_AHB1ENR_GPIOGEN); // Turn on RCC for GPIOG Peripheral

    GPIOG->MODER &= ~((3 << 26) | (3 << 28)); // Clear Bits for Pins 13 & 14
    GPIOG->MODER |= (1 << 26) | (1 << 28); // Set MODER13=01 & MODER14=01

    while (1) {
        GPIOG->BSRR = RED_LED_MASK | (GREEN_LED_MASK << 16); // LEDs <R|G> : <ON|OFF>
        for (volatile uint32_t i = 0; i < 1000000; i++); // Delay
        GPIOG->BSRR = (RED_LED_MASK << 16) | GREEN_LED_MASK; // LEDs <R|G> : <OFF|ON>
        for (volatile uint32_t i = 0; i < 1000000; i++); // Delay
    }
}
