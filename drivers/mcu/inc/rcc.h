#include <stdint.h>
#include "stm32f429.h"

// RCC Peripheral:
#define RCC_BASE (AHB1_BASE_ADDR + 0x3800)
#define RCC_AHB1ENR_OFFSET (0x30U)
#define RCC_AHB1ENR_GPIOGEN (0x06U)
#define RCC_AHB1ENR ((volatile uint32_t*) (RCC_BASE + RCC_AHB1ENR_OFFSET))