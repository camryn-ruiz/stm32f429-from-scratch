# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/)

## [Unreleased]

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