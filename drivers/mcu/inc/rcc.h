#ifndef _RCC_H
#define _RCC_H

#include <stdint.h>
#include "status.h"
#include "stm32f429.h"

typedef enum {
    SWS_HSI = 0,
    SWS_HSE = 1,
    SWS_PLL = 2,
    SWS_INVALID = 3
} SWS_TypeDef;

typedef enum {
    DIV_1 = 0,
    DIV_2 = 0x4,
    DIV_4 = 0x5,
    DIV_8 = 0x6,
    DIV_16 = 0x7
} CLOCK_DIVIDER_TypeDef;

#define CLOCK_SPEED_100KHz 100000
#define CLOCK_SPEED_400KHz 400000

STATUS_CODE RCC_Init(void);

STATUS_CODE RCC_EnableGPIOx(GPIO_TypeDef* GPIOx);
STATUS_CODE RCC_DisableGPIOx(GPIO_TypeDef* GPIOx);
STATUS_CODE RCC_EnableI2Cx(I2C_TypeDef* I2Cx);
STATUS_CODE RCC_DisableI2Cx(I2C_TypeDef* I2Cx);
uint32_t SYSCLK_GetFreq(void);
uint32_t I2C_GetPCLK1Freq(void);

#endif // _RCC_H