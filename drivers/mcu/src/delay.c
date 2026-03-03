#include "delay.h"
#include "rcc.h"

void delay_ms(uint32_t ms) {
    volatile uint32_t count = ms * SYSCLK_GetFreq() / 1000; // Approximate number of iterations for 1 ms delay
    while (count--) {
        __asm__("nop"); // Prevent optimization of empty loop
    }
}