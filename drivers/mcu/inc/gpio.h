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
} GPIO_ModeTypeDef;

typedef enum {
    GPIO_PULL_NONE = 0x00U,
    GPIO_PUSH_PULL = 0x01U,
    GPIO_OPEN_DRAIN = 0x02U,
} GPIO_OTypeTypeDef;

typedef enum {
    GPIO_SPEED_LOW = 0x00U,
    GPIO_SPEED_MEDIUM = 0x01U,
    GPIO_SPEED_FAST = 0x02U,
    GPIO_SPEED_HIGH = 0x03U,
} GPIO_SpeedTypeDef;

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
    GPIO_PIN_MAX = 0x10U
} GPIO_PinTypeDef;

typedef enum {
    GPIO_NONE = 0x00U,
    GPIO_PULLUP = 0x01U,
    GPIO_PULLDOWN = 0x02U,
    GPIO_RESERVED = 0x03U
} GPIO_PUPDTypeDef;

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
} GPIO_ALTFTypeDef;

typedef struct {
    GPIO_PinTypeDef pin;
    GPIO_ModeTypeDef mode;
    GPIO_OTypeTypeDef otype;
    GPIO_SpeedTypeDef speed;
    GPIO_PUPDTypeDef pull;
    GPIO_ALTFTypeDef alternate_function;
} GPIO_InitTypeDef;

// GPIO Helper Fuinctions Prototypes:
// TODO: Implement Status later for Error Handling in these functions
STATUS_CODE gpio_init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* InitStruct);
STATUS_CODE gpio_set_mode(GPIO_TypeDef* GPIOx, GPIO_PinTypeDef pin, GPIO_ModeTypeDef mode);
STATUS_CODE gpio_set_pin(GPIO_TypeDef* GPIOx, GPIO_PinTypeDef pin);
STATUS_CODE gpio_clear_pin(GPIO_TypeDef* GPIOx, GPIO_PinTypeDef pin);
STATUS_CODE gpio_toggle_pin(GPIO_TypeDef* GPIOx, GPIO_PinTypeDef pin);
uint32_t gpio_read_pin(GPIO_TypeDef* GPIOx, GPIO_PinTypeDef pin);
STATUS_CODE gpio_write_pin(GPIO_TypeDef* GPIOx, GPIO_PinTypeDef pin, uint32_t value);
STATUS_CODE gpio_write_alternate(GPIO_TypeDef* GPIOx, GPIO_PinTypeDef pin, GPIO_ALTFTypeDef alt);

#endif // _GPIO_H