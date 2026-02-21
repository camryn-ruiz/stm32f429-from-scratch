COMPILER = arm-none-eabi-gcc
APPLICATION_CODE = application/*.c
MCU_DRIVERS = drivers/mcu/src/*.c
LINKER_SCRIPT = linker/stm32f429_linker.ld
STARTUP_SCRIPT = startup/stm32f429_startup.c
SRC_CODE = $(APPLICATION_CODE) $(MCU_DRIVERS) $(STARTUP_SCRIPT)
OUT_DIR = build
ELF_FILE = $(OUT_DIR)/blink.elf
OPT ?= -O0
CFLAGS  = -mcpu=cortex-m4 -mthumb -nostdlib $(OPT)
LDFLAGS = -T $(LINKER_SCRIPT) -Wl,--build-id=none
INC_DIRS = -I drivers/mcu/inc

.PHONY: build flash clean

build:
	@mkdir -p $(OUT_DIR)
	@rm -f $(ELF_FILE)
	@echo "Compiling application..."
	$(COMPILER) $(SRC_CODE) $(CFLAGS) $(LDFLAGS) -o $(ELF_FILE) $(INC_DIRS)

flash:
	@echo "======================================"
	@echo "  FLASHING STM32F429ZIT6 FIRMWARE"
	@echo "======================================"
	@openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program $(ELF_FILE) verify reset exit"
	@echo "--------------------------------------"
	@echo "  Flash successful"
	@echo "--------------------------------------"

clean:
	@echo "Cleaning build artifacts..."
	@rm -f $(OUT_DIR)/*.elf