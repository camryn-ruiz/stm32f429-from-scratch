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

// STM32F429 Eval Board on Board LEDs:
#define USER_BUTTON_PIN 0U
#define GREEN_LED_PIN 13U
#define RED_LED_PIN 14U
#define GREEN_LED_MASK (1U << GREEN_LED_PIN)
#define RED_LED_MASK (1U << RED_LED_PIN)

typedef enum {
    GPIO_MODE_INPUT = 0x00U,
    GPIO_MODE_OUTPUT = 0x01U,
    GPIO_MODE_ALTFN = 0x02U,
    GPIO_MODE_ANALOG = 0x03U,
} GPIO_Mode;

typedef enum {
    GPIO_PULL_NONE = 0x00U,
    GPIO_PUSH_PULL = 0x01U,
    GPIO_OPEN_DRAIN = 0x02U,
} GPIO_OType;

typedef enum {
    GPIO_SPEED_LOW = 0x00U,
    GPIO_SPEED_MEDIUM = 0x01U,
    GPIO_SPEED_FAST = 0x02U,
    GPIO_SPEED_HIGH = 0x03U,
} GPIO_Speed;

typedef enum {
    GPIO_PIN_0 = 0x00U,
    GPIO_PIN_1 = 0x01U,
    GPIO_PIN_2 = 0x02U,
    GPIO_PIN_3 = 0x03U,
    GPIO_PIN_4 = 0x04U,
    GPIO_PIN_5 = 0x05U,
    GPIO_PIN_6 = 0x06U,
    GPIO_PIN_7 = 0x07U,
    GPIO_PIN_8 = 0x08U,
    GPIO_PIN_9 = 0x09U,
    GPIO_PIN_10 = 0x0AU,
    GPIO_PIN_11 = 0x0BU,
    GPIO_PIN_12 = 0x0CU,
    GPIO_PIN_13 = 0x0DU,
    GPIO_PIN_14 = 0x0EU,
    GPIO_PIN_15 = 0x0FU,
} GPIO_Pin;

typedef enum {
    GPIO_NONE = 0x00U,
    GPIO_PULLUP = 0x01U,
    GPIO_PULLDOWN = 0x02U,
    GPIO_RESERVED = 0x03U
} GPIO_PUPD;

typedef enum {
    GPIO_AF0 = 0x00U,
    GPIO_AF1 = 0x01U,
    GPIO_AF2 = 0x02U,
    GPIO_AF3 = 0x03U,
    GPIO_AF4 = 0x04U,
    GPIO_AF5 = 0x05U,
    GPIO_AF6 = 0x06U,
    GPIO_AF7 = 0x07U,
    GPIO_AF8 = 0x08U,
    GPIO_AF9 = 0x09U,
    GPIO_AF10 = 0x0AU,
    GPIO_AF11 = 0x0BU,
    GPIO_AF12 = 0x0CU,
    GPIO_AF13 = 0x0DU,
    GPIO_AF14 = 0x0EU,
    GPIO_AF15 = 0x0FU,
} GPIO_ALTF;

typedef struct {
    GPIO_Pin pin;
    GPIO_Mode mode;
    GPIO_OType otype;
    GPIO_Speed speed;
    GPIO_PUPD pull;
    GPIO_ALTF alternate_function;
} GPIO_InitPinConfig;

// GPIO Helper Fuinctions Prototypes:
// TODO: Implement Status later for Error Handling in these functions
STATUS_CODE gpio_init(GPIO_TypeDef* GPIOx, GPIO_InitPinConfig* InitStruct);
STATUS_CODE gpio_set_mode(GPIO_TypeDef* GPIOx, GPIO_Pin pin, GPIO_Mode mode);

STATUS_CODE gpio_set_pin(GPIO_TypeDef* GPIOx, GPIO_Pin pin);
STATUS_CODE gpio_clear_pin(GPIO_TypeDef* GPIOx, GPIO_Pin pin);
STATUS_CODE gpio_toggle_pin(GPIO_TypeDef* GPIOx, GPIO_Pin pin);
uint32_t gpio_read_pin(GPIO_TypeDef* GPIOx, GPIO_Pin pin);
STATUS_CODE gpio_write_pin(GPIO_TypeDef* GPIOx, GPIO_Pin pin, uint32_t value);
STATUS_CODE gpio_write_alternate(GPIO_TypeDef* GPIOx, GPIO_Pin pin, GPIO_ALTF alt);

#endif // _GPIO_H