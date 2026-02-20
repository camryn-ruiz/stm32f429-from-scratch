COMPILER = arm-none-eabi-gcc
APPLICATION_CODE = application/*.c
LINKER_SCRIPT = linker/stm32f429_linker.ld
STARTUP_SCRIPT = startup/stm32f429_startup.c
OUT_DIR = output
ELF_FILE = $(OUT_DIR)/blink.elf
OPT ?= -O0
CFLAGS  = -mcpu=cortex-m4 -mthumb -nostdlib $(OPT)
LDFLAGS = -T $(LINKER_SCRIPT) -Wl,--build-id=none

.PHONY: build flash clean

build:
	@echo "Compiling application..."
	$(COMPILER) $(APPLICATION_CODE) $(STARTUP_SCRIPT) $(CFLAGS) $(LDFLAGS) -o $(ELF_FILE)

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