#include <stdint.h>
#include "status.h"

#ifndef _GPIO_H
#define _GPIO_H

// GPIO Peripheral Register Offsets:
typedef struct {
    volatile uint32_t MODER;    // 0x00
    volatile uint32_t OTYPER;   // 0x04
    volatile uint32_t OSPEEDR;  // 0x08
    volatile uint32_t PUPDR;    // 0x0C
    volatile uint32_t IDR;      // 0x10
    volatile uint32_t ODR;      // 0x14
    volatile uint32_t BSRR;     // 0x18
    volatile uint32_t LCKR;     // 0x1C
    volatile uint32_t AFRL;     // 0x20
    volatile uint32_t AFRH;     // 0x24
} GPIO_TypeDef;

// GPIO Peripheral Offsets:
#define GPIOA_BASE_OFFSET (0x0000U)
#define GPIOB_BASE_OFFSET (0x0400U)
#define GPIOC_BASE_OFFSET (0x0800U)
#define GPIOD_BASE_OFFSET (0x0C00U)
#define GPIOE_BASE_OFFSET (0x1000U)
#define GPIOF_BASE_OFFSET (0x1400U)
#define GPIOG_BASE_OFFSET (0x1800U)
#define GPIOH_BASE_OFFSET (0x1C00U)
#define GPIOI_BASE_OFFSET (0x2000U)
#define GPIOJ_BASE_OFFSET (0x2400U)
#define GPIOK_BASE_OFFSET (0x2800U)

// GPIO Peripheral Base Addresses:
#define GPIOA_BASE_ADDR (AHB1_BASE_ADDR + GPIOA_BASE_OFFSET)
#define GPIOB_BASE_ADDR (AHB1_BASE_ADDR + GPIOB_BASE_OFFSET)
#define GPIOC_BASE_ADDR (AHB1_BASE_ADDR + GPIOC_BASE_OFFSET)
#define GPIOD_BASE_ADDR (AHB1_BASE_ADDR + GPIOD_BASE_OFFSET)
#define GPIOE_BASE_ADDR (AHB1_BASE_ADDR + GPIOE_BASE_OFFSET)
#define GPIOF_BASE_ADDR (AHB1_BASE_ADDR + GPIOF_BASE_OFFSET)
#define GPIOG_BASE_ADDR (AHB1_BASE_ADDR + GPIOG_BASE_OFFSET)
#define GPIOH_BASE_ADDR (AHB1_BASE_ADDR + GPIOH_BASE_OFFSET)
#define GPIOI_BASE_ADDR (AHB1_BASE_ADDR + GPIOI_BASE_OFFSET)
#define GPIOJ_BASE_ADDR (AHB1_BASE_ADDR + GPIOJ_BASE_OFFSET)
#define GPIOK_BASE_ADDR (AHB1_BASE_ADDR + GPIOK_BASE_OFFSET)

// GPIO Peripheral Pointers:
#define GPIOA ((GPIO_TypeDef*) GPIOA_BASE_ADDR)
#define GPIOB ((GPIO_TypeDef*) GPIOB_BASE_ADDR)
#define GPIOC ((GPIO_TypeDef*) GPIOC_BASE_ADDR)
#define GPIOD ((GPIO_TypeDef*) GPIOD_BASE_ADDR)
#define GPIOE ((GPIO_TypeDef*) GPIOE_BASE_ADDR)
#define GPIOF ((GPIO_TypeDef*) GPIOF_BASE_ADDR)
#define GPIOG ((GPIO_TypeDef*) GPIOG_BASE_ADDR)
#define GPIOH ((GPIO_TypeDef*) GPIOH_BASE_ADDR)
#define GPIOI ((GPIO_TypeDef*) GPIOI_BASE_ADDR)
#define GPIOJ ((GPIO_TypeDef*) GPIOJ_BASE_ADDR)
#define GPIOK ((GPIO_TypeDef*) GPIOK_BASE_ADDR)

typedef enum {
    GPIO_MODE_INPUT = 0x00U,
    GPIO_MODE_OUTPUT = 0x01U,
    GPIO_MODE_ALTFN = 0x02U,
    GPIO_MODE_ANALOG = 0x03U,
} GPIO_Mode;

// GPIO Helper Fuinctions Prototypes:
// TODO: Implement Status later for Error Handling in these functions
STATUS_CODE gpio_init(void);
STATUS_CODE gpio_set_mode(GPIO_TypeDef* GPIOx, uint8_t pin, uint8_t mode);

STATUS_CODE gpio_set_pin(GPIO_TypeDef* GPIOx, uint32_t pin);
STATUS_CODE gpio_clear_pin(GPIO_TypeDef* GPIOx, uint32_t pin);
STATUS_CODE gpio_toggle_pin(GPIO_TypeDef* GPIOx, uint32_t pin);

uint32_t gpio_read_pin(GPIO_TypeDef* GPIOx, uint32_t pin);
STATUS_CODE gpio_write_pin(GPIO_TypeDef* GPIOx, uint32_t pin, uint32_t value);

#endif // _GPIO_H