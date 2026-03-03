#ifndef _USART_H
#define _USART_H

#include <stdint.h>
#include "stm32f429.h"

// USART Status Register Bits:
#define TXE (1U << 7) // Transmit Data Register Empty
#define TC (1U << 6) // Transmission Complete
#define RXNE (1U << 5) // Read Data Register Not Empty
#define NF (1U << 2) // Noise Flag
#define FE (1U << 1) // Framing Error
#define PE (1U << 0) // Parity Error

// USART Baud Rate Register Bits:

// USART Control Register 1 Bits:
#define UE (1U << 13) // USART Enable
#define M (1U << 12) // Word Length
#define WAKE (1U << 11) // Wakeup Method
#define PCE (1U << 10) // Parity Control Enable
#define PS (1U << 9) // Parity Selection
#define TE (1U << 3) // Transmitter Enable
#define RE (1U << 2) // Receiver Enable

// USART Control Register 2 Bits:

// USART Control Register 3 Bits:
#define ONEBIT (1U << 11) // One Sample Bit Method Enable
#define HDSEL (1U << 3) // Half-Duplex Selection

#endif // _USART_H