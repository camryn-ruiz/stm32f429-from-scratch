/* Tells the Program that execution begins at reset_handler */
ENTRY(reset_handler)

/* Memory Regions for the STM32F429 MCU */
MEMORY
{
    /* Internal Flash Memory */
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 2048K

    /* Main SRAM used for stack, heap, .data, and .bss */
	SRAM1 (rwx) : ORIGIN = 0x20000000, LENGTH = 112K

    /* Additional SRAM regions (unused) */
	SRAM2 (rwx) : ORIGIN = 0x2001C000, LENGTH = 16K
    SRAM3 (rwx) : ORIGIN = 0x20020000, LENGTH = 64K
}

/* Initial stack pointer value 
 * on reset, Cortex-M loads MSP from the first word of the vector table
 */
_estack = ORIGIN(SRAM1) + LENGTH(SRAM1);

SECTIONS
{
    /* Keep ISR Vector at starting address */
    . = ORIGIN(FLASH);
    .isr_vector :
    {
        KEEP(*(.isr_vector))
    } >FLASH

    /* Program code and read-only data stored in Flash */
    .text :
    {
        . = ALIGN(4);

        *(.text)   /* Executable instructions */
        *(.rodata) /* Read-only Data */

        . = ALIGN(4);
        _etext = .; /* End of code section in Flash */
    } >FLASH

    /* Initialized global/static Variables (Flash -> SRAM on reset) */
    .data :
    {
        . = ALIGN(4);
        _sdata = .; /* Start of SRAM */

        *(.data)

        . = ALIGN(4);
        _edata = .; /* End of SRAM */
    } >SRAM1 AT> FLASH

    /* Load address of .data section into Flash */
    _sidata = LOADADDR(.data);

    /* Uninitialized global/static Variables (zero-init) */
    .bss :
    {
        . = ALIGN(4);
        _sbss = .;

        *(.bss)
        *(COMMON)

        . = ALIGN(4);
        _ebss = .;
        _end = .;
    } >SRAM1

    /* Remove unecessary sections for bare-metal firmware */
    /DISCARD/ :
    {
        *(.note.gnu.build-id)
    }
}
