#include <stdint.h>

#define SRAM1_START (0x20000000U)
#define SRAM1_SIZE (112U * 1024U)
#define SRAM1_END (SRAM1_START + SRAM1_SIZE)
#define STACK_POINTER_INIT_ADDR (SRAM1_END) // Initial Stack Pointer set to end of SRAM1 (Cortex-M descending stack)
#define ISR_VECTOR_SIZE_WORDS (106) // 16 Cortex M Exceptions | 90 stm32f429 peripheral interrupts

// Cortex-M System Exceptions:
void reset_handler(void);
void default_handler(void);
void nmi_handler(void) __attribute__((weak, alias("default_handler")));
void hard_fault_handler(void) __attribute__((weak, alias("default_handler")));
void mem_manage_handler(void) __attribute__((weak, alias("default_handler")));
void bus_fault_handler(void) __attribute__((weak, alias("default_handler")));
void usage_fault_handler(void) __attribute__((weak, alias("default_handler")));
void svcall_handler(void) __attribute__((weak, alias("default_handler")));
void debug_monitor_handler(void) __attribute__((weak, alias("default_handler")));
void pendsv_handler(void) __attribute__((weak, alias("default_handler")));
void systick_handler(void) __attribute__((weak, alias("default_handler")));

// STM32F429 Interrupt Handlers:
void wwdg_handler(void) __attribute__((weak, alias("default_handler")));
void pvd_handler(void) __attribute__((weak, alias("default_handler")));
void tamp_stamp_handler(void) __attribute__((weak, alias("default_handler")));
void rtc_wakeup_handler(void) __attribute__((weak, alias("default_handler")));
void flash_handler(void) __attribute__((weak, alias("default_handler")));
void rcc_handler(void) __attribute__((weak, alias("default_handler")));
void extio0_handler(void) __attribute__((weak, alias("default_handler")));
void extio1_handler(void) __attribute__((weak, alias("default_handler")));
void extio2_handler(void) __attribute__((weak, alias("default_handler")));
void extio3_handler(void) __attribute__((weak, alias("default_handler")));
void extio4_handler(void) __attribute__((weak, alias("default_handler")));
void dma1_stream0_handler(void) __attribute__((weak, alias("default_handler")));
void dma1_stream1_handler(void) __attribute__((weak, alias("default_handler")));
void dma1_stream2_handler(void) __attribute__((weak, alias("default_handler")));
void dma1_stream3_handler(void) __attribute__((weak, alias("default_handler")));
void dma1_stream4_handler(void) __attribute__((weak, alias("default_handler")));
void dma1_stream5_handler(void) __attribute__((weak, alias("default_handler")));
void dma1_stream6_handler(void) __attribute__((weak, alias("default_handler")));
void adc_handler(void) __attribute__((weak, alias("default_handler")));
void can1_tx_handler(void) __attribute__((weak, alias("default_handler")));
void can1_rx0_handler(void) __attribute__((weak, alias("default_handler")));
void can1_rx1_handler(void) __attribute__((weak, alias("default_handler")));
void can1_rce_handler(void) __attribute__((weak, alias("default_handler")));
void exti9_5_handler(void) __attribute__((weak, alias("default_handler")));
void tim1_brk_tim9_handler(void) __attribute__((weak, alias("default_handler")));
void tim1_up_tim10_handler(void) __attribute__((weak, alias("default_handler")));
void tim1_trg_com_tim11_handler(void) __attribute__((weak, alias("default_handler")));
void tim1_cc_handler(void) __attribute__((weak, alias("default_handler")));
void tim2_handler(void) __attribute__((weak, alias("default_handler")));
void tim3_handler(void) __attribute__((weak, alias("default_handler")));
void tim4_handler(void) __attribute__((weak, alias("default_handler")));
void i2c1_ev_handler(void) __attribute__((weak, alias("default_handler")));
void i2c1_er_handler(void) __attribute__((weak, alias("default_handler")));
void i2c2_ev_handler(void) __attribute__((weak, alias("default_handler")));
void i2c2_er_handler(void) __attribute__((weak, alias("default_handler")));
void spi1_handler(void) __attribute__((weak, alias("default_handler")));
void spi2_handler(void) __attribute__((weak, alias("default_handler")));
void usart1_handler(void) __attribute__((weak, alias("default_handler")));
void usart2_handler(void) __attribute__((weak, alias("default_handler")));
void usart3_handler(void) __attribute__((weak, alias("default_handler")));
void exti15_10_handler(void) __attribute__((weak, alias("default_handler")));
void rtc_alarm_handler(void) __attribute__((weak, alias("default_handler")));
void otg_fs_wkup_handler(void) __attribute__((weak, alias("default_handler")));
void tim8_brk_tim12_handler(void) __attribute__((weak, alias("default_handler")));
void tim8_up_tim13_handler(void) __attribute__((weak, alias("default_handler")));
void tim8_trg_com_tim14_handler(void) __attribute__((weak, alias("default_handler")));
void tim8_cc_handler(void) __attribute__((weak, alias("default_handler")));
void dma1_stream7_stream0_handler(void) __attribute__((weak, alias("default_handler")));
void fsmc_handler(void) __attribute__((weak, alias("default_handler")));
void sdio_handler(void) __attribute__((weak, alias("default_handler")));
void tim5_handler(void) __attribute__((weak, alias("default_handler")));
void spi3_handler(void) __attribute__((weak, alias("default_handler")));
void uart3_handler(void) __attribute__((weak, alias("default_handler")));
void uart5_handler(void) __attribute__((weak, alias("default_handler")));
void tim6_dac_handler(void) __attribute__((weak, alias("default_handler")));
void tim7_handler(void) __attribute__((weak, alias("default_handler")));
void dma2_stream0_handler(void) __attribute__((weak, alias("default_handler")));
void dma2_stream1_handler(void) __attribute__((weak, alias("default_handler")));
void dma2_stream2_handler(void) __attribute__((weak, alias("default_handler")));
void dma2_stream3_handler(void) __attribute__((weak, alias("default_handler")));
void dma2_stream4_handler(void) __attribute__((weak, alias("default_handler")));
void eth_handler(void) __attribute__((weak, alias("default_handler")));
void eth_wkup_handler(void) __attribute__((weak, alias("default_handler")));
void can2_tx_handler(void) __attribute__((weak, alias("default_handler")));
void can2_rx0_handler(void) __attribute__((weak, alias("default_handler")));
void can2_rx1_handler(void) __attribute__((weak, alias("default_handler")));
void can2_sce_handler(void) __attribute__((weak, alias("default_handler")));
void otg_fs_handler(void) __attribute__((weak, alias("default_handler")));
void dma2_stream5_handler(void) __attribute__((weak, alias("default_handler")));
void dma2_stream6_handler(void) __attribute__((weak, alias("default_handler")));
void dma2_stream7_handler(void) __attribute__((weak, alias("default_handler")));
void usart6_handler(void) __attribute__((weak, alias("default_handler")));
void i2c3_ev_handler(void) __attribute__((weak, alias("default_handler")));
void i2c3_er_handler(void) __attribute__((weak, alias("default_handler")));
void otg_hs_ep1_out_handler(void) __attribute__((weak, alias("default_handler")));
void otg_hs_ep1_in_handler(void) __attribute__((weak, alias("default_handler")));
void otg_hs_wkup_handler(void) __attribute__((weak, alias("default_handler")));
void otg_hs_handler(void) __attribute__((weak, alias("default_handler")));
void dmci_handler(void) __attribute__((weak, alias("default_handler")));
void cryp_handler(void) __attribute__((weak, alias("default_handler")));
void hash_rng_handler(void) __attribute__((weak, alias("default_handler")));
void fpu_handler(void) __attribute__((weak, alias("default_handler")));
void uart7_handler(void) __attribute__((weak, alias("default_handler")));
void uart8_handler(void) __attribute__((weak, alias("default_handler")));
void spi4_handler(void) __attribute__((weak, alias("default_handler")));
void spi5_handler(void) __attribute__((weak, alias("default_handler")));
void spi6_handler(void) __attribute__((weak, alias("default_handler")));
void sai1_handler(void) __attribute__((weak, alias("default_handler")));
void lcd_tft_handler(void) __attribute__((weak, alias("default_handler")));
void lcd_tft_error_handler(void) __attribute__((weak, alias("default_handler")));
void dma2d_handler(void) __attribute__((weak, alias("default_handler")));

uint32_t isr_vector[ISR_VECTOR_SIZE_WORDS] __attribute__((section(".isr_vector"))) =
{
    STACK_POINTER_INIT_ADDR,
    // Cortex-M System Exceptions:
    (uint32_t)&reset_handler,
    (uint32_t)&nmi_handler,
    (uint32_t)&hard_fault_handler,
    (uint32_t)&mem_manage_handler,
    (uint32_t)&bus_fault_handler,
    (uint32_t)&usage_fault_handler,
    0,
    0,
    0,
    (uint32_t)&svcall_handler,
    (uint32_t)&debug_monitor_handler,
    0,
    (uint32_t)&pendsv_handler,
    (uint32_t)&systick_handler,
    // STM32F429 Peripheral Interrupts:
    (uint32_t)&wwdg_handler,
    (uint32_t)&pvd_handler,
    (uint32_t)&tamp_stamp_handler,
    (uint32_t)&rtc_wakeup_handler,
    (uint32_t)&flash_handler,
    (uint32_t)&rcc_handler,
    (uint32_t)&extio0_handler,
    (uint32_t)&extio1_handler,
    (uint32_t)&extio2_handler,
    (uint32_t)&extio3_handler,
    (uint32_t)&extio4_handler,
    (uint32_t)&dma1_stream0_handler,
    (uint32_t)&dma1_stream1_handler,
    (uint32_t)&dma1_stream2_handler,
    (uint32_t)&dma1_stream3_handler,
    (uint32_t)&dma1_stream4_handler,
    (uint32_t)&dma1_stream5_handler,
    (uint32_t)&dma1_stream6_handler,
    (uint32_t)&adc_handler,
    (uint32_t)&can1_tx_handler,
    (uint32_t)&can1_rx0_handler,
    (uint32_t)&can1_rx1_handler,
    (uint32_t)&can1_rce_handler,
    (uint32_t)&exti9_5_handler,
    (uint32_t)&tim1_brk_tim9_handler,
    (uint32_t)&tim1_up_tim10_handler,
    (uint32_t)&tim1_trg_com_tim11_handler,
    (uint32_t)&tim1_cc_handler,
    (uint32_t)&tim2_handler,
    (uint32_t)&tim3_handler,
    (uint32_t)&tim4_handler,
    (uint32_t)&i2c1_ev_handler,
    (uint32_t)&i2c1_er_handler,
    (uint32_t)&i2c2_ev_handler,
    (uint32_t)&i2c2_er_handler,
    (uint32_t)&spi1_handler,
    (uint32_t)&spi2_handler,
    (uint32_t)&usart1_handler,
    (uint32_t)&usart2_handler,
    (uint32_t)&usart3_handler,
    (uint32_t)&exti15_10_handler,
    (uint32_t)&rtc_alarm_handler,
    (uint32_t)&otg_fs_wkup_handler,
    (uint32_t)&tim8_brk_tim12_handler,
    (uint32_t)&tim8_up_tim13_handler,
    (uint32_t)&tim8_trg_com_tim14_handler,
    (uint32_t)&tim8_cc_handler,
    (uint32_t)&dma1_stream7_stream0_handler,
    (uint32_t)&fsmc_handler,
    (uint32_t)&sdio_handler,
    (uint32_t)&tim5_handler,
    (uint32_t)&spi3_handler,
    (uint32_t)&uart3_handler,
    (uint32_t)&uart5_handler,
    (uint32_t)&tim6_dac_handler,
    (uint32_t)&tim7_handler,
    (uint32_t)&dma2_stream0_handler,
    (uint32_t)&dma2_stream1_handler,
    (uint32_t)&dma2_stream2_handler,
    (uint32_t)&dma2_stream3_handler,
    (uint32_t)&dma2_stream4_handler,
    (uint32_t)&eth_handler,
    (uint32_t)&eth_wkup_handler,
    (uint32_t)&can2_tx_handler,
    (uint32_t)&can2_rx0_handler,
    (uint32_t)&can2_rx1_handler,
    (uint32_t)&can2_sce_handler,
    (uint32_t)&otg_fs_handler,
    (uint32_t)&dma2_stream5_handler,
    (uint32_t)&dma2_stream6_handler,
    (uint32_t)&dma2_stream7_handler,
    (uint32_t)&usart6_handler,
    (uint32_t)&i2c3_ev_handler,
    (uint32_t)&i2c3_er_handler,
    (uint32_t)&otg_hs_ep1_out_handler,
    (uint32_t)&otg_hs_ep1_in_handler,
    (uint32_t)&otg_hs_wkup_handler,
    (uint32_t)&otg_hs_handler,
    (uint32_t)&dmci_handler,
    (uint32_t)&cryp_handler,
    (uint32_t)&hash_rng_handler,
    (uint32_t)&fpu_handler,
    (uint32_t)&uart7_handler,
    (uint32_t)&uart8_handler,
    (uint32_t)&spi4_handler,
    (uint32_t)&spi5_handler,
    (uint32_t)&spi6_handler,
    (uint32_t)&sai1_handler,
    (uint32_t)&lcd_tft_handler,
    (uint32_t)&lcd_tft_error_handler,
    (uint32_t)&dma2d_handler,
};


extern uint32_t _etext, _sdata, _edata, _sbss, _ebss, _sidata;
void main(void);

void default_handler(void)
{
    while (1);
}

void reset_handler(void)
{
    // Copy .data section from flash to SRAM
    uint8_t *flash_data = (uint8_t*)&_sidata;
    uint8_t *sram1_data = (uint8_t*)&_sdata;
    while (sram1_data < (uint8_t*)&_edata)
    {
        *sram1_data++ = *flash_data++;
    }

    // Zero initialize the .bss section in SRAM
    uint32_t *sram1_bss = (uint32_t*)&_sbss;
    while (sram1_bss < (uint32_t*)&_ebss)
    {
        *sram1_bss++ = 0;
    }

    // Call the main application entry point
    main();
}