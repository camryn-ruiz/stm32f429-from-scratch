#include <stdint.h>
#include "rcc.h"

STATUS_CODE RCC_EnableGPIOx(char port)
{
    if (port < 'A' || port > 'I') {
        return STATUS_INVALID_PARAM; // Invalid port, do nothing
    }

    RCC->AHB1ENR |= (1U << (port - 'A')); // Enable the clock for the specified GPIO port
    return STATUS_OK;
}

STATUS_CODE RCC_DisableGPIOx(char port)
{
    if (port < 'A' || port > 'I') {
        return STATUS_INVALID_PARAM; // Invalid port, do nothing
    }

    RCC->AHB1ENR &= ~(1U << (port - 'A')); // Disable the clock for the specified GPIO port
    return STATUS_OK;
}

STATUS_CODE RCC_EnableI2Cx(uint8_t i2c_port) {
    if (i2c_port < 1 || i2c_port > 3) {
        return STATUS_INVALID_PARAM; // Invalid I2C port, do nothing
    }

    RCC->APB1ENR |= (1U << (i2c_port + 21)); // Enable the clock for the specified I2C port
    return STATUS_OK;
}

STATUS_CODE RCC_DisableI2Cx(uint8_t i2c_port) {
    if (i2c_port < 1 || i2c_port > 3) {
        return STATUS_INVALID_PARAM; // Invalid I2C port, do nothing
    }

    RCC->APB1ENR &= ~(1U << (i2c_port + 21)); // Disable the clock for the specified I2C port
    return STATUS_OK;
}