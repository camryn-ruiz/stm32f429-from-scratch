#!/usr/bin/env bash

# This script sets up the environment for building the STM32F4xx project.
# It checks for the presence of the ARM GCC toolchain and Flash tools

. /etc/os-release

if [[ "$ID" == "ubuntu" ]]; then
	sudo apt install gcc-arm-none-eabi
	sudo apt install openocd
    echo "Running on Ubuntu"
elif [[ "$ID" == "arch" ]]; then 
	sudo pacman -S arm-none-eabi-gcc arm-none-eabi-binutils arm-none-eabi-newlib
	sudo pacman -S openocd
    echo "Running on Arch Linux"
else
    echo "Unknown distro: $ID"
fi


