#ifndef STM32F429_H
#define STM32F429_H

#include <stdint.h>

/* ---------------- Base Addresses ----------------*/
#define PERIPHERAL_BASE (0x40000000U)
#define AHB1_BASE_ADDR (PERIPHERAL_BASE + 0x20000U)
#define APB1_BASE_ADDR (PERIPHERAL_BASE + 0x00000U)
#define APB2_BASE_ADDR (PERIPHERAL_BASE + 0x10000U)


/* ---------------- RCC ----------------*/
// RCC Peripheral:
#define RCC_BASE (AHB1_BASE_ADDR + 0x3800)

// RCC Peripheral Pointer:
#define RCC ((RCC_TypeDef*) RCC_BASE)

// RCC AHB1 Peripheral Clock Enable Bits:
#define RCC_AHB1ENR_GPIOAEN (1U << 0)
#define RCC_AHB1ENR_GPIOBEN (1U << 1)
#define RCC_AHB1ENR_GPIOCEN (1U << 2)
#define RCC_AHB1ENR_GPIODEN (1U << 3)
#define RCC_AHB1ENR_GPIOEEN (1U << 4)
#define RCC_AHB1ENR_GPIOFEN (1U << 5)
#define RCC_AHB1ENR_GPIOGEN (1U << 6)
#define RCC_AHB1ENR_GPIOHEN (1U << 7)
#define RCC_AHB1ENR_GPIOIEN (1U << 8)

#define RCC_APB1ENR_USART2EN (1U << 17)
#define RCC_APB1ENR_USART3EN (1U << 18)
#define RCC_APB1ENR_UART4EN (1U << 19)
#define RCC_APB1ENR_UART5EN (1U << 20)
#define RCC_APB1ENR_I2C1EN (1U << 21)
#define RCC_APB1ENR_I2C2EN (1U << 22)
#define RCC_APB1ENR_I2C3EN (1U << 23)

#define RCC_APB2ENR_USART1EN (1U << 4)
#define RCC_APB2ENR_USART6EN (1U << 5)


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

/* ---------------- GPIO ----------------*/
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

/* ---------------- I2C ----------------*/
// I2C Peripheral Addresses:
#define I2C1_BASE (APB1_BASE_ADDR + 0x5400)
#define I2C2_BASE (APB1_BASE_ADDR + 0x5800)
#define I2C3_BASE (APB1_BASE_ADDR + 0x5C00)

// I2C Peripheral Pointers:
#define I2C1 ((I2C_TypeDef*) I2C1_BASE)
#define I2C2 ((I2C_TypeDef*) I2C2_BASE)
#define I2C3 ((I2C_TypeDef*) I2C3_BASE)

typedef struct {
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t OAR1;
    volatile uint32_t OAR2;
    volatile uint32_t DR;
    volatile uint32_t SR1;
    volatile uint32_t SR2;
    volatile uint32_t CCR;
    volatile uint32_t TRISE;
    volatile uint32_t FLTR;
} I2C_TypeDef;

/* ---------------- UART/USART ----------------*/
// USART Peripheral Addresses:
#define USART1_BASE (APB2_BASE_ADDR + 0x1000)
#define USART2_BASE (APB1_BASE_ADDR + 0x4400)
#define USART3_BASE (APB1_BASE_ADDR + 0x4800)
#define UART4_BASE (APB1_BASE_ADDR + 0x4C00)
#define UART5_BASE (APB1_BASE_ADDR + 0x5000)
#define USART6_BASE (APB2_BASE_ADDR + 0x1400)
#define UART7_BASE (APB1_BASE_ADDR + 0x7800)
#define UART8_BASE (APB1_BASE_ADDR + 0x7C00)

// USART Peripheral Pointers:
#define USART1 ((USART_TypeDef*) USART1_BASE)
#define USART2 ((USART_TypeDef*) USART2_BASE)
#define USART3 ((USART_TypeDef*) USART3_BASE)
#define UART4 ((USART_TypeDef*) UART4_BASE)
#define UART5 ((USART_TypeDef*) UART5_BASE)
#define USART6 ((USART_TypeDef*) USART6_BASE)
#define UART7 ((USART_TypeDef*) UART7_BASE)
#define UART8 ((USART_TypeDef*) UART8_BASE)

typedef struct {
    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t BRR;
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t CR3;
    volatile uint32_t GTPR;
} USART_TypeDef;

#endif //_STM32F429_H