#include "gpio.h"

void gpio_init(void) {}

void gpio_set_mode(GPIO_TypeDef* GPIOx, uint32_t mode) {
    // Clear the 2 bits corresponding to the pin in the MODER register
    GPIOx->MODER &= ~(0x03U << (2 * mode)); // Clear bits for the specified pin

    // Set the mode for the pin
    GPIOx->MODER |= (mode << (2 * mode)); // Set the mode for the specified pin
}

void gpio_set_pin(GPIO_TypeDef* GPIOx, uint32_t pin) {
    GPIOx->ODR |= (1U << pin); // Set the bit corresponding to the pin in the ODR register
}

void gpio_clear_pin(GPIO_TypeDef* GPIOx, uint32_t pin) {
    GPIOx->ODR &= ~(1U << pin); // Clear the bit corresponding to the pin in the ODR register
}

void gpio_toggle_pin(GPIO_TypeDef* GPIOx, uint32_t pin) {
    GPIOx->ODR ^= (1U << pin); // Toggle the bit corresponding to the pin in the ODR register
}

uint32_t gpio_read_pin(GPIO_TypeDef* GPIOx, uint32_t pin) {
    // TODO: Implement Read Function
    return 0;
}

void gpio_write_pin(GPIO_TypeDef* GPIOx, uint32_t pin, uint32_t value) {
    // TODO: Implement Write Function
}