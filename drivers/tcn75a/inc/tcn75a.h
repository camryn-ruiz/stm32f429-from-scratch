//! @file tcn75a.h
//! @brief TCN75A Temperature Sensor Driver Header File
//! @details
//! > This Driver is for the TCN75A Temperature Sensor, which is a simple I2C-based temperature sensor with a 9-bit to 12-bit resolution and a 
//! > temperature range of -55°C to +125°C. It has a fixed I2C address of 0x48 (when A0-A2 pins are tied to GND) and supports both read and 
//! > write operations for configuration and temperature data retrieval.

//! > Application is used on the PMOD TMP3 breakout board

#ifndef _TCN75A_H
#define _TCN75A_H

#include <stdint.h>
#include "i2c.h"

#define TCN75A_I2C_ADDRESS 0x48U // Base I2C address for TCN75A (A0, A1, A2 all tied to GND defaults to 0x48)

typedef enum {
    FAULT_QUEUE_1 = 0x00U,
    FAULT_QUEUE_2 = 0x01U,
    FAULT_QUEUE_4 = 0x02U,
    FAULT_QUEUE_6 = 0x03U
} TCN75A_FaultQueue_TypeDef;

typedef enum {
    RESOLUTION_9_BIT  = 0x00U,
    RESOLUTION_10_BIT = 0x01U,
    RESOLUTION_11_BIT = 0x02U,
    RESOLUTION_12_BIT = 0x03U
} TCN75A_ADCResolution_TypeDef;

typedef enum {
    NEGATIVE = -1,
    POSITIVE = 1
} SIGN_TypeDef;

typedef struct {
    volatile uint8_t SHUTDOWN_MODE : 1;                     // Bit 0: Shutdown Mode (0 = Normal Operation, 1 = Shutdown)
    volatile uint8_t COMPARATOR_MODE : 1;                   // Bit 1: Comparator/Interrupt Mode (0 = Comparator, 1 = Interrupt)
    volatile uint8_t POLARITY : 1;                          // Bit 2: Alert Polarity (0 = Active Low, 1 = Active High)
    volatile TCN75A_FaultQueue_TypeDef FAULT_QUEUE : 2;     // Bits 3-4: Fault Queue
    volatile TCN75A_ADCResolution_TypeDef RESOLUTION : 2;   // Bits 5-6: Temperature Resolution
    volatile uint8_t RESERVED : 1;                          // Bit 7: Reserved (Must be set to 0)
} Config_Bits_TypeDef;

#define TCN75A_REG_AMB_TEMP   0x00 // Ambient Temperature Register (Read-Only)
#define TCN75A_REG_CONFIG     0x01 // Configuration Register (Read/Write)
#define TCN75A_REG_TEMP_HYST  0x02 // Temperature Hysteresis Register (Read/Write) Default = 75°C
#define TCN75A_REG_TEMP_SET   0x03 // Temperature Limit-Set Register (Read/Write) Default = 80°C

STATUS_CODE TCN75A_Init(I2C_TypeDef* I2Cx);
STATUS_CODE TCN75A_ReadTemperature(I2C_TypeDef* I2Cx, float* temperature);
STATUS_CODE TCN75A_WriteConfig(I2C_TypeDef* I2Cx, Config_Bits_TypeDef config);
STATUS_CODE TCN75A_WriteTempHysteresis(I2C_TypeDef* I2Cx, float hysteresis);
STATUS_CODE TCN75A_WriteTempSet(I2C_TypeDef* I2Cx, float tempSet);
STATUS_CODE TCN75A_SendCommand(I2C_TypeDef* I2Cx, uint8_t command);

#endif // _TCN75A_H