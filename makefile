# Compiler & Programmer
COMPILER = ~/tools/gcc-arm-none-eabi-10-2020-q4-major/bin/arm-none-eabi-gcc
#COMPILER = ~/tools/arm-gnu-toolchain-13.2.Rel1-x86_64-arm-none-eabi/bin/arm-none-eabi-gcc
PROGRAMMER = openocd
PROGRAMMER_FLAGS = -f interface/stlink.cfg -f target/stm32f4x.cfg

# Source Files
APPLICATION_CODE = application/*.c
DRIVERS = drivers/*/src/*.c
LINKER_SCRIPT = linker/stm32f429_linker.ld
STARTUP_SCRIPT = startup/stm32f429_startup.c
SRC_CODE = $(APPLICATION_CODE) $(DRIVERS) $(STARTUP_SCRIPT)

# Output
OUT_DIR = build
ELF_FILE = $(OUT_DIR)/stm32f429_firmware.elf

# Compiler & Linker Flags
OPT ?= -O0
CFLAGS  = -mcpu=cortex-m4 -mthumb -nostdlib $(OPT)
LDFLAGS = -T linker/stm32f429_linker.ld -Wl,--build-id=none -Wl,-Map=$(OUT_DIR)/stm32f429_firmware.map
LDLIBS = -lc -lnosys -lgcc
INC_DIRS =	-I drivers/mcu/inc \
			-I drivers/status/inc \
			-I drivers/hd44780u/inc \
			-I drivers/pcf8574a/inc \
			-I drivers/tcn75a/inc \

.PHONY: all build flash clean size

all: build

build: $(ELF_FILE)

$(ELF_FILE): $(SRC_CODE) | $(OUT_DIR)
	@echo "Compiling application..."
	$(COMPILER) $(SRC_CODE) $(CFLAGS) $(INC_DIRS) $(LDFLAGS) -o $@ $(LDLIBS)

# Ensure build directory exists
$(OUT_DIR):
	@mkdir -p $@

flash:
	@echo "======================================"
	@echo "  FLASHING STM32F429ZIT6 FIRMWARE"
	@echo "======================================"
	@$(PROGRAMMER) $(PROGRAMMER_FLAGS) -c "program $(ELF_FILE) verify reset exit"
	@echo "--------------------------------------"
	@echo "  Flash successful"
	@echo "--------------------------------------"

size: $(ELF_FILE)
	arm-none-eabi-size $<

clean:
	@echo "Cleaning build artifacts..."
	@rm -f $(OUT_DIR)/*.elf
