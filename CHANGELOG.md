# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/)

## [0.1.3]

### Added
- UART Functionality
- `APB2_GetPCLKFreq()` to get the APB2 clock frequency

### Changed
- Made init functions for the seperate peripherals in `main.c` such as `i2c_init()`, `uart_init()`, `test_init()`
- Renamed function `I2C_GetPCLK1Freq()` -> `APB1_GetPCLKFreq()`
- Renamed bit specific macros to include perihperal prefix such as `I2C_TXE`

## [0.1.2]

### Added
- delay.c/.h where the delay functions will live
- Some USART related defines/files
- Added some info at the top of sensor drivers to give background

### Changed
- Location of the Register Typedefs `RCC_TypeDef`, `I2C_TypeDef`, `GPIO_TypeDef` moved to `stm32f429.h`
- `RCC_EnableGPIOx`, `RCC_EnableI2Cx`, and respective disable functions logic changed so you can pass in the I2Cx/GPIOx instead of different values
- `gpio_init` now will enable the clock for the passed in gpio register

### Fixed
- Include Headers
- Include/Redundant Includes
## [0.1.1]

### Added
- TCN75 Driver basic functionality
- basic newlib syscall stubs to be able to use `snprintf` to print temp values to the LCD

### Changed
- Move linker libraries into LDLIBS

## [0.1.0] - 2026-02-27
### Added
- I2C driver and start function
- LCD driver with working row/column and print functions
- GPIO initialization functions
- RCC initialization functions
- `RCC_TypeDef` definition for STM32F429

### Changed
- Code cleanup: fixed typedef names and moved register info to `stm32f429.h`
- Updated Linker Script to include _end to signify the start of the heap
- Removed dead code from main

### Fixed
- Minor cleanup and bug fixes in LCD set row function

### Other
- Updated `.gitignore` to exclude build directory
- Test pushes and initial project setup

## [0.0.1] - 2026-02-20
### Added
- Initial commit with basic blink example
- Created linker and startup script for `stm32f429`
- Started GPIO driver base functionality