//! @file tcn75a.c
//! @brief TCN75A Temperature Sensor Driver Source File
//! @details
//! > See Header File for details.

#include "tcn75a.h"

STATUS_CODE TCN75A_Init(I2C_TypeDef* I2Cx) {
    // Initialize the I2C peripheral for communication with the TCN75A
    STATUS_CODE status = I2C_Init(I2Cx, SLOW_MODE, DUTY, 100000); // Initialize I2C in standard mode (100 kHz)
    if (status != STATUS_OK) {
        return status; // Failed to initialize I2C
    }
    return status;
}

STATUS_CODE TCN75A_ReadTemperature(I2C_TypeDef* I2Cx, float* temperature) {
    // WIP
    uint8_t data[2];
    // Read 2 bytes from the TCN75A ambient temperature register (0x00)
    STATUS_CODE status = I2C_Master_Receive(I2Cx, TCN75A_I2C_ADDRESS, data, 2);
    if (status != STATUS_OK) {
        return status; // Failed to read temperature data
    }
    
    int16_t temp_raw = (data[0] << 8) | data[1];  // Combine MSB and LSB
    temp_raw >>= 4;                               // Keep only the top 12 bits
    if (temp_raw & 0x800) {                       // Sign bit check (negative)
        temp_raw |= 0xF000;                       // Sign-extend to 16-bit
    }
    *temperature = temp_raw * 0.0625f;            // 1 LSB = 0.0625 °C
    return STATUS_OK;
}

STATUS_CODE TCN75A_WriteConfig(I2C_TypeDef* I2Cx, Config_Bits_TypeDef config) {
    uint8_t config_byte = *((uint8_t*)&config); // Convert bitfield struct to byte
    uint8_t data[2] = {TCN75A_REG_CONFIG, config_byte}; // First byte is register address, second byte is config data
    STATUS_CODE status = I2C_Master_Transmit(I2Cx, TCN75A_I2C_ADDRESS, data, 2); // Write config byte to TCN75A
    if (status != STATUS_OK) {
        return status; // Failed to write configuration
    }
    return STATUS_OK;
}

STATUS_CODE TCN75A_WriteTempHysteresis(I2C_TypeDef* I2Cx, float hysteresis) {
    // TODO Implement function to write temperature hysteresis value to TCN75A : Default 75 C
    return STATUS_OK;
}

STATUS_CODE TCN75A_WriteTempSet(I2C_TypeDef* I2Cx, float tempSet) {
    // TODO Implement function to write temperature limit-set value to TCN75A : Default 80 C
    return STATUS_OK;
}