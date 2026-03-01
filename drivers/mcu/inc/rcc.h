#include <stdint.h>
#include "status.h"

#ifndef _RCC_H
#define _RCC_H

// RCC Peripheral:
typedef struct {
    volatile uint32_t CR;
    volatile uint32_t PLLCFGR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t AHB1RSTR;
    volatile uint32_t AHB2RSTR;
    volatile uint32_t AHB3RSTR;
    volatile uint32_t RESERVED0; // Reserved: 0x1C
    volatile uint32_t APB1RSTR;
    volatile uint32_t APB2RSTR;
    volatile uint32_t RESERVED1[2]; // Reserved: 0x28-0x2C
    volatile uint32_t AHB1ENR;
    volatile uint32_t AHB2ENR;
    volatile uint32_t AHB3ENR;
    volatile uint32_t RESERVED2; // Reserved: 0x3C
    volatile uint32_t APB1ENR;
    volatile uint32_t APB2ENR;
    volatile uint32_t RESERVED3[2]; // Reserved: 0x48-0x4C
    volatile uint32_t AHB1LPENR;
    volatile uint32_t AHB2LPENR;
    volatile uint32_t AHB3LPENR;
    volatile uint32_t RESERVED4; // Reserved: 0x5C
    volatile uint32_t APB1LPENR;
    volatile uint32_t APB2LPENR;
    volatile uint32_t RESERVED5[2]; // Reserved: 0x68-0x6C
    volatile uint32_t BDCR;
    volatile uint32_t CSR;
    volatile uint32_t RESERVED6[2]; // Reserved: 0x78-0x7C
    volatile uint32_t SSCGR;
    volatile uint32_t PLLI2SCFGR;
    volatile uint32_t PLLSAICFGR;
    volatile uint32_t DCKCFGR;
} RCC_TypeDef;

enum SWS {
    SWS_HSI = 0,
    SWS_HSE = 1,
    SWS_PLL = 2,
    SWS_INVALID = 3
};

enum CLOCK_DIVIDER {
    DIV_1 = 0,
    DIV_2 = 0x4,
    DIV_4 = 0x5,
    DIV_8 = 0x6,
    DIV_16 = 0x7
};

#define RCC_BASE (AHB1_BASE_ADDR + 0x3800)
#define RCC ((RCC_TypeDef*) RCC_BASE)

#define RCC_AHB1ENR_GPIOAEN (0x00U)
#define RCC_AHB1ENR_GPIOGEN (0x06U)

#define CLOCK_SPEED_100KHz 100000
#define CLOCK_SPEED_400KHz 400000

STATUS_CODE RCC_Init(void);

STATUS_CODE RCC_EnableGPIOx(char gpio_port);
STATUS_CODE RCC_DisableGPIOx(char gpio_port);
STATUS_CODE RCC_EnableI2Cx(uint8_t i2c_port);
STATUS_CODE RCC_DisableI2Cx(uint8_t i2c_port);
uint32_t SYSCLK_GetFreq(void);
uint32_t I2C_GetPCLK1Freq(void);

void delay_ms(uint32_t ms);

#endif // _RCC_H