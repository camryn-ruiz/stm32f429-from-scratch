#!/bin/bash

# This script sets up the environment for building the STM32F4xx project.
# It checks for the presence of the ARM GCC toolchain and Flash tools
sudo apt install gcc-arm-none-eabi
sudo apt install openocd