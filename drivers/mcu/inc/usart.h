#ifndef _USART_H
#define _USART_H

#include <stdint.h>
#include "stm32f429.h"
#include "status.h"

// USART Status Register Bits:
#define USART_TXE (1U << 7) // Transmit Data Register Empty
#define USART_TC (1U << 6) // Transmission Complete
#define USART_RXNE (1U << 5) // Read Data Register Not Empty
#define USART_NF (1U << 2) // Noise Flag
#define USART_FE (1U << 1) // Framing Error
#define USART_PE (1U << 0) // Parity Error

// USART Control Register 1 Bits:
#define USART_UE (1U << 13) // USART Enable
#define USART_M (1U << 12) // Word Length
#define USART_WAKE (1U << 11) // Wakeup Method
#define USART_PCE (1U << 10) // Parity Control Enable
#define USART_PS (1U << 9) // Parity Selection
#define USART_TE (1U << 3) // Transmitter Enable
#define USART_RE (1U << 2) // Receiver Enable

// USART Control Register 3 Bits:
#define USART_ONEBIT (1U << 11) // One Sample Bit Method Enable
#define USART_HDSEL (1U << 3) // Half-Duplex Selection

// USART Control Register 2 Bits:
typedef enum {
    STOP_1_BIT = 0x00U,
    STOP_0_5_BIT = 0x01U,
    STOP_2_BIT = 0x02U,
    STOP_1_5_BIT = 0x03U
} STOP_BITS_TypeDef;

typedef enum {
    USART_PARITY_NONE, 
    USART_PARITY_EVEN,
    USART_PARITY_ODD
} USART_Parity_TypeDef;

#define USART_8_DATA_BITS 8
#define USART_9_DATA_BITS 9
#define USART_PARITY_NONE 0

STATUS_CODE USART_Init(USART_TypeDef* USARTx, uint32_t baudRate, STOP_BITS_TypeDef stopBits, uint8_t wordLength, uint8_t parity);
STATUS_CODE USART_Transmit(USART_TypeDef* USARTx, uint8_t data);
STATUS_CODE USART_Receive(USART_TypeDef* USARTx, uint8_t* data);
STATUS_CODE USART_TransmitString(USART_TypeDef* USARTx, const char* str);
STATUS_CODE USART_ReceiveString(USART_TypeDef* USARTx, char* buffer, uint32_t bufferSize);

#endif // _USART_H