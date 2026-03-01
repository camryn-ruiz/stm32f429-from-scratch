#include <stdint.h>
#include <stdio.h>
#include "gpio.h"

STATUS_CODE gpio_init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* InitStruct) {
    if (InitStruct == NULL) {
        return STATUS_INVALID_PARAM; // Invalid configuration pointer
    }

    // Set the mode for the specified pin
    gpio_set_mode(GPIOx, InitStruct->pin, InitStruct->mode);

    // TODO: Add speeds if needed in the future
    // Set Output Type (Push-Pull/Open-Drain)
    if (InitStruct->mode == GPIO_MODE_OUTPUT || InitStruct->mode == GPIO_MODE_ALTFN) {
        if (InitStruct->otype == GPIO_PUSH_PULL) {
            GPIOx->OTYPER &= ~(1U << InitStruct->pin); // Set to Push-Pull
        } else if (InitStruct->otype == GPIO_OPEN_DRAIN) {
            GPIOx->OTYPER |= (1U << InitStruct->pin); // Set to Open-Drain
        }
    }

    // Set Pull-Up/Pull-Down resistors
    GPIOx->PUPDR &= ~(0x03U << (2 * InitStruct->pin)); // Clear previous pull-up/pull-down configuration
    GPIOx->PUPDR |= (InitStruct->pull << (2 * InitStruct->pin)); // Set new pull-up/pull-down configuration

    // Set Output Speed (Low/Medium/Fast/High)
    GPIOx->OSPEEDR &= ~(0x03U << (2 * InitStruct->pin)); // Clear previous speed configuration
    GPIOx->OSPEEDR |= (InitStruct->speed << (2 * InitStruct->pin)); // Set new speed configuration

    // If alternate function mode is selected, set the alternate function
    if (InitStruct->mode == GPIO_MODE_ALTFN) {
        gpio_write_alternate(GPIOx, InitStruct->pin, InitStruct->alternate_function);
    }

    return STATUS_OK;
}

STATUS_CODE gpio_set_mode(GPIO_TypeDef* GPIOx, GPIO_PinTypeDef pin, GPIO_ModeTypeDef mode) {
    // Clear the 2 bits corresponding to the pin in the MODER register
    GPIOx->MODER &= ~(0x03U << (2 * pin)); // Clear bits for the specified pin

    // Set the mode for the pin
    GPIOx->MODER |= (mode << (2 * pin)); // Set the mode for the specified pin

    return STATUS_OK;
}

STATUS_CODE gpio_set_pin(GPIO_TypeDef* GPIOx, GPIO_PinTypeDef pin) {
    GPIOx->ODR |= (1U << pin); // Set the bit corresponding to the pin in the ODR register

    return STATUS_OK;
}

STATUS_CODE gpio_clear_pin(GPIO_TypeDef* GPIOx, GPIO_PinTypeDef pin) {
    GPIOx->ODR &= ~(1U << pin); // Clear the bit corresponding to the pin in the ODR register

    return STATUS_OK;
}

STATUS_CODE gpio_toggle_pin(GPIO_TypeDef* GPIOx, GPIO_PinTypeDef pin) {
    GPIOx->ODR ^= (1U << pin); // Toggle the bit corresponding to the pin in the ODR register

    return STATUS_OK;
}

uint32_t gpio_read_pin(GPIO_TypeDef* GPIOx, GPIO_PinTypeDef pin) {
    uint32_t val = GPIOx->IDR & (1U << pin); // Read the bit corresponding to the pin in the IDR register
    return val;
}

STATUS_CODE gpio_write_pin(GPIO_TypeDef* GPIOx, GPIO_PinTypeDef pin, uint32_t value) {
    GPIOx->ODR = (GPIOx->ODR & ~(1U << pin)) | ((value & 0x01U) << pin); // Write the value to the bit corresponding to the pin in the ODR register

    return STATUS_OK;
}

STATUS_CODE gpio_write_alternate(GPIO_TypeDef* GPIOx, GPIO_PinTypeDef pin, GPIO_ALTFTypeDef alt) {
    // Clear the 4 bits corresponding to the pin in the AFRL or AFRH register
    if (pin < 8) {
        GPIOx->AFRL &= ~(0xF0U << (4 * pin)); // Clear bits for the specified pin in AFRL
        GPIOx->AFRL |= (alt << (4 * pin)); // Set the alternate function bits
    }
    else {
        GPIOx->AFRH &= ~(0x0FU << (4 * (pin - 8))); // Clear bits for the specified pin in AFRH
        GPIOx->AFRH |= (alt << (4 * (pin - 8))); /// Set the alternate function bits
    }

    return STATUS_OK;
}