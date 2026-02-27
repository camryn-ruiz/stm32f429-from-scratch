#include "gpio.h"

STATUS_CODE gpio_init(void) {}

STATUS_CODE gpio_set_mode(GPIO_TypeDef* GPIOx, uint8_t pin, GPIO_Mode mode) {
    // Clear the 2 bits corresponding to the pin in the MODER register
    GPIOx->MODER &= ~(0x03U << (2 * pin)); // Clear bits for the specified pin

    // Set the mode for the pin
    GPIOx->MODER |= (mode << (2 * pin)); // Set the mode for the specified pin

    return STATUS_OK;
}

STATUS_CODE gpio_set_pin(GPIO_TypeDef* GPIOx, uint32_t pin) {
    GPIOx->ODR |= (1U << pin); // Set the bit corresponding to the pin in the ODR register

    return STATUS_OK;
}

STATUS_CODE gpio_clear_pin(GPIO_TypeDef* GPIOx, uint32_t pin) {
    GPIOx->ODR &= ~(1U << pin); // Clear the bit corresponding to the pin in the ODR register

    return STATUS_OK;
}

STATUS_CODE gpio_toggle_pin(GPIO_TypeDef* GPIOx, uint32_t pin) {
    GPIOx->ODR ^= (1U << pin); // Toggle the bit corresponding to the pin in the ODR register

    return STATUS_OK;
}

uint32_t gpio_read_pin(GPIO_TypeDef* GPIOx, uint32_t pin) {
    uint32_t val = GPIOx->IDR & (1U << pin); // Read the bit corresponding to the pin in the IDR register
    return val;
}

STATUS_CODE gpio_write_pin(GPIO_TypeDef* GPIOx, uint32_t pin, uint32_t value) {
    GPIOx->ODR = (GPIOx->ODR & ~(1U << pin)) | ((value & 0x01U) << pin); // Write the value to the bit corresponding to the pin in the ODR register

    return STATUS_OK;
}

STATUS_CODE gpio_write_alternate(GPIO_TypeDef* GPIOx, uint32_t pin, AF alt) {
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