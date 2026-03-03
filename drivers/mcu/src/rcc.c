#include "stm32f429.h"
#include "rcc.h"

STATUS_CODE RCC_EnableGPIOx(GPIO_TypeDef* GPIOx)
{
    if      (GPIOx == GPIOA) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    else if (GPIOx == GPIOB) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    else if (GPIOx == GPIOC) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    else if (GPIOx == GPIOD) RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    else if (GPIOx == GPIOE) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
    else if (GPIOx == GPIOF) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;
    else if (GPIOx == GPIOG) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
    else if (GPIOx == GPIOH) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN;
    else if (GPIOx == GPIOI) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOIEN;
    else return STATUS_INVALID_PARAM;

    return STATUS_OK;
}

STATUS_CODE RCC_DisableGPIOx(GPIO_TypeDef* GPIOx)
{
    if      (GPIOx == GPIOA) RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOAEN;
    else if (GPIOx == GPIOB) RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOBEN;
    else if (GPIOx == GPIOC) RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOCEN;
    else if (GPIOx == GPIOD) RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIODEN;
    else if (GPIOx == GPIOE) RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOEEN;
    else if (GPIOx == GPIOF) RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOFEN;
    else if (GPIOx == GPIOG) RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOGEN;
    else if (GPIOx == GPIOH) RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOHEN;
    else if (GPIOx == GPIOI) RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOIEN;
    else return STATUS_INVALID_PARAM; // Invalid port, do nothing

    return STATUS_OK;
}

STATUS_CODE RCC_EnableI2Cx(I2C_TypeDef* I2Cx) {
    if (I2Cx == I2C1) RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
    else if (I2Cx == I2C2) RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;
    else if (I2Cx == I2C3) RCC->APB1ENR |= RCC_APB1ENR_I2C3EN;
    else return STATUS_INVALID_PARAM; // Invalid I2C port, do nothing

    return STATUS_OK;
}

STATUS_CODE RCC_DisableI2Cx(I2C_TypeDef* I2Cx) {
    if (I2Cx == I2C1) RCC->APB1ENR &= ~RCC_APB1ENR_I2C1EN;
    else if (I2Cx == I2C2) RCC->APB1ENR &= ~RCC_APB1ENR_I2C2EN;
    else if (I2Cx == I2C3) RCC->APB1ENR &= ~RCC_APB1ENR_I2C3EN;
    else return STATUS_INVALID_PARAM; // Invalid I2C port, do nothing

    return STATUS_OK;
}

uint32_t SYSCLK_GetFreq(void) {
    uint32_t sysclk_source = (RCC->CFGR >> 2) & 0x3; // SWS bits
    switch (sysclk_source) {
        case SWS_HSI: // HSI oscillator used as system clock
            return 16000000; // HSI frequency is 16 MHz
        case SWS_HSE: // HSE oscillator used as system clock
            return 8000000; // STM32F429 Discovery has 8 MHz external crystal
        case SWS_PLL: // PLL used as system clock
            // TODO: Calculate from RCC->PLLCFGR register
            // PLL_OUT = (PLL_IN × PLLN) / (PLLM × PLLP)
            // For now, assume typical 168 MHz configuration
            return 168000000;
        default:
            return 0; // Invalid clock source
    }
}

uint32_t I2C_GetPCLK1Freq(void) {
    uint32_t SYSCLK = SYSCLK_GetFreq();
    uint32_t ppre1 = (RCC->CFGR >> 10) & 0x7; // APB1 prescaler bits

    uint8_t apb1_divider = DIV_1; // Default: no division
    if (ppre1 >= 4) { // If prescaler is not DIV_1
        apb1_divider = ppre1 - 3; // Map 4->DIV_2, 5->DIV_4, 6->DIV_8, 7->DIV_16
    }
    
    // Typical configuration for STM32F429 Discovery at 180 MHz:
    // SYSCLK = 180 MHz
    // AHB = 180 MHz (HPRE = 1)
    // APB1 = 45 MHz (PPRE1 = 4, divide by 4)
    // APB2 = 90 MHz (PPRE2 = 2, divide by 2)
    
    return SYSCLK / (1 << apb1_divider); // Calculate APB1 clock frequency
}