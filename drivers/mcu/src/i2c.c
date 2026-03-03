#include "i2c.h"
#include "rcc.h"

STATUS_CODE I2C_Init(I2C_TypeDef* I2Cx, uint16_t mode, uint16_t duty_cycle, uint32_t clock_speed) {
    // Enable I2C peripheral clock via RCC
    RCC_EnableI2Cx(I2Cx);

    // Disable peripheral before configuration (clear PE bit in CR1)
    I2Cx->CR1 &= ~PE;

    // Configure I2C Frequency in CR2 register (must be set to PCLK1 frequency in MHz)
    uint32_t pclk1_mhz = I2C_GetPCLK1Freq() / 1000000;
    I2Cx->CR2 = (I2Cx->CR2 & ~0x3F) | (pclk1_mhz & 0x3F); // Clear previous frequency and set new value

    // Configure I2C clock speed (CCR register)
    I2C_ClockConfig(I2Cx, mode, duty_cycle, clock_speed);

    // Set TRISE register
    switch (mode) {
        case SLOW_MODE:
            I2Cx->TRISE = pclk1_mhz + 1; // Maximum rise time for standard mode 1000ns
            break;
        case FAST_MODE:
            I2Cx->TRISE = ((pclk1_mhz * 300) / 1000) + 1; // Maximum rise time for fast mode 300ns
            break;
        default:
            return STATUS_INVALID_PARAM;
    }
    // Enable peripheral (PE bit in CR1)
    I2Cx->CR1 |= PE;

    return STATUS_OK;
}


STATUS_CODE I2C_ClockConfig(I2C_TypeDef* I2Cx, uint16_t mode, uint16_t duty_cycle, uint32_t clock_speed) {
    // Configure the Mode (Fast/Standard) and Duty Cycle in CCR register
    I2Cx->CCR = 0; // Clear all bits
    uint32_t pclk1 = I2C_GetPCLK1Freq(); // Get APB1 clock frequency 
    uint32_t ccr_val = 0;

    // Set the CCR value based on the desired clock speed and mode
    switch (mode) {
        case SLOW_MODE: // Standard mode (100 kHz)
            // Sm: T_high = CCR * T_PCLK1 | T_low = CCR * T_PCLK1 
            ccr_val = (pclk1 / (clock_speed * 2)); // CCR = PCLK1 / (2 * I2C_speed)

            if (ccr_val < 4) {
                ccr_val = 4; // Minimum CCR value for standard mode is 4
            }
            I2Cx->CCR |= (ccr_val & 0xFFF);
            break;
        case FAST_MODE: // Fast mode (400 kHz)
            // Fm Duty = 0: T_high = CCR * T_PCLK1 | T_low = 2 * CCR * T_PCLK1
            // Fm Duty = 1: T_high = 9 * CCR * T_PCLK1 | T_low = 16 * CCR * T_PCLK1
            if (duty_cycle == DUTY) {
                ccr_val = (pclk1 / (25 * clock_speed)); // CCR = PCLK1 / (25 * I2C_speed)
            } else {
                ccr_val = (pclk1 / (clock_speed * 3));
            }

            if (ccr_val < 1) {
                ccr_val = 1; // Minimum CCR value for fast mode is 1
            }
            I2Cx->CCR |= mode | duty_cycle | (ccr_val & 0xFFF);
            break;
        default:
            return STATUS_INVALID_PARAM;
    }
        return STATUS_OK;
}

STATUS_CODE I2C_Start(I2C_TypeDef* I2Cx) {
    // Wait until BUSY flag is cleared
    uint32_t timeout = TIMEOUT;
    while ((I2Cx->SR2 & BUSY) && --timeout);
    if (timeout == 0) {
        return STATUS_TIMEOUT; // Bus is busy, cannot start
    }
    
    // Generate START condition
    I2Cx->CR1 |= START;

    // Wait for SB flag to be set
    timeout = TIMEOUT;
    while (!(I2Cx->SR1 & SB) && --timeout);
    if (timeout == 0) {
        return STATUS_TIMEOUT; // Start condition not generated
    }
    
    return STATUS_OK;
}

void I2C_Stop(I2C_TypeDef* I2Cx) {
    // Generate STOP condition
    I2Cx->CR1 |= STOP;
}

STATUS_CODE I2C_SendAddress(I2C_TypeDef* I2Cx, uint8_t slave_address, uint8_t direction) {
    // Send slave address with R/W bit
    I2Cx->DR = (slave_address << 1) | (direction & 0x1);

    // Wait for ADDR flag
    uint32_t timeout = TIMEOUT;
    while (!(I2Cx->SR1 & ADDR) && --timeout);
    if (timeout == 0) {
        return STATUS_TIMEOUT; // Address not acknowledged
    }

    // Clear ADDR flag by reading SR1 then SR2
    (void) I2Cx->SR1;
    (void) I2Cx->SR2;

    return STATUS_OK;
}

STATUS_CODE I2C_Transmit(I2C_TypeDef* I2Cx, uint8_t* data, uint16_t size) {
    uint32_t timeout = TIMEOUT;

    // Transmit data bytes
    for (uint16_t i = 0; i < size; i++) {
        I2Cx->DR = data[i]; // Write Byte to Data Register
        
        // Wait for TXE flag
        timeout = TIMEOUT;
        while (!(I2Cx->SR1 & TXE) && --timeout);
        if (timeout == 0) {
            return STATUS_TIMEOUT; // Data not transmitted
        }
    }
    
    // Wait for BTF after last byte
    timeout = TIMEOUT;
    while (!(I2Cx->SR1 & BTF) && --timeout);
    if (timeout == 0) {
        return STATUS_TIMEOUT; // Byte transfer not finished
    }
    
    return STATUS_OK;
}

STATUS_CODE I2C_Receive(I2C_TypeDef* I2Cx, uint8_t* data, uint16_t size) {
    uint32_t timeout = TIMEOUT;
    if (size == 0) {
        return STATUS_INVALID_PARAM; // No data to receive
    }

    // Enable/disable ACK based on size
    if (size == 1) {
        // Single byte reception:
        I2Cx->CR1 &= ~ACK; // Disable ACK for last byte
        
        timeout = TIMEOUT;
        while (!(I2Cx->SR1 & RXNE) && --timeout); // Wait for RXNE
        if (timeout == 0) {
            return STATUS_TIMEOUT; // Data not received
        }

        data[0] = I2Cx->DR; // Read the single byte
    } else if (size == 2) {
        I2Cx->CR1 |= ACK; // Enable ACK for multiple bytes
        I2Cx->CR1 |= POS; // Set POS

        timeout = TIMEOUT;
        while(!(I2Cx->SR1 & BTF) && --timeout); // Wait for first byte
        if (timeout == 0) {
            return STATUS_TIMEOUT; // Data not received
        }

        I2Cx->CR1 &= ~ACK; // Disable ACK for last byte
        data[0] = I2Cx->DR; // Read first byte
        data[1] = I2Cx->DR; // Read second byte

        I2Cx->CR1 &= ~POS; // Clear POS
    }

    else {
        I2Cx->CR1 |= ACK; // Enable ACK for multiple bytes

        for (uint16_t i = 0; i < size - 3; i++) {
            timeout = TIMEOUT;
            while(!(I2Cx->SR1 & RXNE) && --timeout); // Wait for first byte
            if (timeout == 0) {
                return STATUS_TIMEOUT; // Data not received
            }
            data[i] = I2Cx->DR; // Read byte
        }

        // Handle last 3 bytes
        timeout = TIMEOUT;
        while (!(I2Cx->SR1 & BTF) && --timeout);
        if (timeout == 0) {
            return STATUS_TIMEOUT;
        }

        I2Cx->CR1 &= ~ACK; // Set ACK low
        data[size - 3] = I2Cx->DR; // Read data N-2
        
        timeout = TIMEOUT;
        while (!(I2Cx->SR1 & BTF) && --timeout); // Wait for second to last byte
        if (timeout == 0) {
            return STATUS_TIMEOUT; // Data not received
        }

        I2Cx->CR1 |= STOP; // Generate STOP condition after reading second to last byte
        data[size - 2] = I2Cx->DR; // Read second to last byte
        data[size - 1] = I2Cx->DR; // Read last byte
    }

    return STATUS_OK;
}

STATUS_CODE I2C_Master_Transmit(I2C_TypeDef* I2Cx, uint8_t slave_address, uint8_t* data, uint16_t size) {
    // Call I2C_Start()
    STATUS_CODE status = I2C_Start(I2Cx);
    if (status != STATUS_OK) {
        return status; // Failed to generate start condition
    }
    
    // Call I2C_SendAddress() with write direction
    status = I2C_SendAddress(I2Cx, slave_address, I2C_WRITE);
    if (status != STATUS_OK) {
        I2C_Stop(I2Cx); // Ensure we stop if address sending fails
        return status; // Failed to send address
    }
    
    // Call I2C_Transmit()
    status = I2C_Transmit(I2Cx, data, size);
    if (status != STATUS_OK) {
        I2C_Stop(I2Cx); // Ensure we stop if transmission fails
        return status; // Failed to transmit data
    }

    // Call I2C_Stop()
    I2C_Stop(I2Cx);

    return STATUS_OK;
}

STATUS_CODE I2C_Master_Receive(I2C_TypeDef* I2Cx, uint8_t slave_address, uint8_t* data, uint16_t size) {
    // Call I2C_Start()
    STATUS_CODE status = I2C_Start(I2Cx);
    if (status != STATUS_OK) {
        return status; // Failed to generate start condition
    }
    // Call I2C_SendAddress() with read direction
    status = I2C_SendAddress(I2Cx, slave_address, I2C_READ);
    if (status != STATUS_OK) {
        I2C_Stop(I2Cx); // Ensure we stop if address sending fails
        return status; // Failed to send address
    }

    // Call I2C_Receive()
    status = I2C_Receive(I2Cx, data, size);
    if (status != STATUS_OK) {
        I2C_Stop(I2Cx); // Ensure we stop if reception fails
        return status; // Failed to receive data
    }

    // Call I2C_Stop()
    I2C_Stop(I2Cx);
    return STATUS_OK;
}