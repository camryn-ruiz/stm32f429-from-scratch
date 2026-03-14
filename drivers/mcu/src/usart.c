#include "usart.h"
#include "rcc.h"
#include "stm32f429.h"
#include "delay.h"

static inline uint32_t calculate_pclk(USART_TypeDef* USARTx) {
    // Get the peripheral clock frequency for the USART
    uint32_t pclk;
    if (USARTx == USART1 || USARTx == USART6) {
        pclk = APB2_GetPCLKFreq(); // USART1 and USART6 are on APB2
    } else {
        pclk = APB1_GetPCLKFreq(); // USART2, USART3, UART4, UART5 are on APB1
    }
    return pclk;
}

/* Procedure outlined in the Reference Manual for USART initialization (Section 30.3.2/3 Transmitter/Receiver) */
STATUS_CODE USART_Init(USART_TypeDef* USARTx, uint32_t baudRate, STOP_BITS_TypeDef stopBits, uint8_t wordLength, uint8_t parity) {
    // Enable the USART peripheral clock
    RCC_EnableUSARTx(USARTx);

    // Establish the USART communication parameters by configuring the CR1, CR2, and CR3 registers:
    USARTx->CR1 &= ~USART_UE;

    // Program the M bit in CR1 to define the word length
    USARTx->CR1 &= ~USART_M; // Clear M bit for 8 data bits
    if (wordLength == 9) {
        USARTx->CR1 |= USART_M; // Set M bit for 9 data bits
    }

    // Program the number of stop bits in CR2 (1 stop bit)
    USARTx->CR2 &= ~(0x3 << 12); // Clear STOP bits
    USARTx->CR2 |= (stopBits << 12); // Set the desired STOP bits

    // Configure parity control in CR1
    USARTx->CR1 &= ~(USART_PCE | USART_PS);
    if (parity == USART_PARITY_EVEN)
        USARTx->CR1 |= USART_PCE; // Set Parity Control Enable
    else if (parity == USART_PARITY_ODD)
        USARTx->CR1 |= (USART_PCE | USART_PS); // Set Parity Control Enable & Parity Selection
    
    // Select the desired baud rate by configuring the BRR register
    // BRR = USARTDIV, where USARTDIV = Fck / baudRate
    uint32_t pclk = calculate_pclk(USARTx);
    USARTx->BRR = (pclk + (baudRate / 2U)) / baudRate;

    // Enable the Transmitter and Receiver by setting the TE and RE bits in CR1
    USARTx->CR1 |= USART_TE | USART_RE; // Enable Transmitter and Receiver

    USARTx->CR1 |= USART_UE; // Enable USART

    return STATUS_OK;
}

/* Procedure outlined in the Reference Manual for USART transmission (Section 30.3.2 Transmitter) */
STATUS_CODE USART_Transmit(USART_TypeDef* USARTx, uint8_t data) {
    // If the Transmit Data Register is empty, write the data to the Data Register
    while (!(USARTx->SR & USART_TXE)); // Wait until the Transmit Data Register is empty

    USARTx->DR = data; // Write the data to the Data Register

    //while (!(USARTx->SR & USART_TC)); // Wait until the transmission is complete

    return STATUS_OK;
}

/* Procedure outlined in the Reference Manual for USART reception (Section 30.3.3 Receiver) */
STATUS_CODE USART_Receive(USART_TypeDef* USARTx, uint8_t* data) {
    // Wait for the Read Data Register to be not empty, then read the data from the Data Register
    while (!(USARTx->SR & USART_RXNE)); // Wait until the Read Data Register is not empty

    *data = (uint8_t)(USARTx->DR & 0xFF); // Read the data from the Data Register, Also resets the RXNE flag

    return STATUS_OK;
}

STATUS_CODE USART_TransmitString(USART_TypeDef* USARTx, const char* str) {
    while (*str) {
        USART_Transmit(USARTx, (uint8_t)(*str)); // Transmit each character in the string
        str++;
		delay_us(5);
    }

    return STATUS_OK;
}

STATUS_CODE USART_ReceiveString(USART_TypeDef* USARTx, char* buffer, uint32_t bufferSize) {
    while (bufferSize > 1) { // Leave space for null terminator
        uint8_t receivedChar;
        USART_Receive(USARTx, &receivedChar); // Receive a character

        if (receivedChar == '\n' || receivedChar == '\r') { // Check for newline or carriage return
            break; // End of string
        }

        *buffer = (char)receivedChar; // Store the received character in the buffer
        buffer++;
        bufferSize--;
    }
    *buffer = '\0'; // Null-terminate the string
    return STATUS_OK;
}
