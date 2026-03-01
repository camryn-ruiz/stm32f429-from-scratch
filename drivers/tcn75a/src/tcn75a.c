#include "tcn75a.h"

STATUS_CODE TCN75A_Init(I2C_TypeDef* I2Cx) {
    // Initialize the I2C peripheral for communication with the TCN75A
    return STATUS_OK;
}

STATUS_CODE TCN75A_ReadTemperature(I2C_TypeDef* I2Cx, float* temperature) {
    /* // WIP
    uint8_t data[2];
    // Read 2 bytes from the TCN75A ambient temperature register (0x00)
    STATUS_CODE status = I2C_Master_Receive(I2Cx, TCN75A_I2C_ADDRESS, data, 2);
    if (status != STATUS_OK) {
        return status; // Failed to read temperature data
    }
    
    int16_t temp_raw = (data[0] << 8) | data[1]; // Combine the two bytes into a single 16-bit value
    *temperature = temp_raw * 0.0625; // Convert raw value to temperature in Celsius (2^(-4))
    */
    return STATUS_OK;
}

STATUS_CODE TCN75A_WriteConfig(I2C_TypeDef* I2Cx, Config_Bits_TypeDef config) {
    return STATUS_OK;
}

STATUS_CODE TCN75A_WriteTempHysteresis(I2C_TypeDef* I2Cx, float hysteresis) {
    return STATUS_OK;
}

STATUS_CODE TCN75A_WriteTempSet(I2C_TypeDef* I2Cx, float tempSet) {
    return STATUS_OK;
}