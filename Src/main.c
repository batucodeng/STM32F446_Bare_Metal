#include <stdint.h>
#include <stdio.h>
#include "main.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

/* Global Değişkenler */
volatile uint32_t buton_basma_sayisi = 0;
volatile uint8_t kesme_tetiklendi = 0;

/* 1. SysTick Gecikme Sürücüsü */
void systick_init(void)
{
    SysTick->CTRL = 0;                  // Önce sayacı durdur
    SysTick->LOAD = (16000 - 1);        // 16 MHz / 16000 = 1 ms
    SysTick->VAL = 0;                   // Sayacı sıfırla
    SysTick->CTRL = (1U << 0) | (1U << 2); // ENABLE ve CLKSOURCE (İşlemci Saati)
}

void delay_ms(uint32_t ms)
{
    for (uint32_t i = 0; i < ms; i++)
    {
        while (!(SysTick->CTRL & (1U << 16)))
        {
            __asm("nop");
        }
    }
}

void usart2_init(void)
{
    RCC->AHB1ENR |= (1U << 0);
    RCC->APB1ENR |= (1U << 17);

    GPIOA->MODER &= ~(3U << (2 * 2));
    GPIOA->MODER |=  (2U << (2 * 2));

    GPIOA->AFR[0] &= ~(0xFU << (2 * 4));
    GPIOA->AFR[0] |=  (7U << (2 * 4));

    USART2->BRR = 0x8B;
    USART2->CR1 = (1U << 3) | (1U << 13);

}

void usart2_write_char(char ch)
{
    while (!(USART2->SR & (1U << 7))) { __asm("nop"); }
    USART2->DR = (ch & 0xFF);
}

int __io_putchar(int ch)
{
    usart2_write_char((char)ch);
    return ch;
}

int _write(int file, char *ptr, int len)
{
    for (int i = 0; i < len; i++)
    {
        __io_putchar(*ptr++);
    }
    return len;
}


void gpio_led_init(void)
{
    RCC->AHB1ENR |= (1U << 0);

    GPIOA->MODER &= ~(3U << (5 * 2));
    GPIOA->MODER |=  (1U << (5 * 2));
}

void exti_pc13_init(void)
{
    RCC->AHB1ENR |= (1U << 2);
    RCC->APB2ENR |= (1U << 14);

    GPIOC->MODER &= ~(3U << (13 * 2));

    SYSCFG->EXTICR[3] &= ~(0xFU << 4);
    SYSCFG->EXTICR[3] |=  (0x2U << 4);

    EXTI->IMR  |= (1U << 13);
    EXTI->FTSR |= (1U << 13);

    NVIC->ISER[1] = (1U << 8);
}

void EXTI15_10_IRQHandler(void)
{
    if (EXTI->PR & (1U << 13))
    {
        EXTI->PR |= (1U << 13);
        buton_basma_sayisi++;
        kesme_tetiklendi = 1;
    }
}

void tim2_init(void) {

	RCC->APB1ENR |= (1U << 0);

	TIM2->PSC = 1599;  /* 16 MHZ / 1600 = 10KHZ SAYMA FREKANSI */
	TIM2->ARR = 9999;  /* 10000 ADIM = 1 SANIYE*/
	TIM2->CNT = 0;     /* SAYACI SIFIRLA */

	TIM2->CR1 |= (1U << 0);
}

void tim2_delay_1s(void) {
	while (!(TIM2->SR & (1U << 0)));

	TIM2->SR &= ~(1U << 0);
}


int main(void)
{
    systick_init();
    gpio_led_init();
    usart2_init();
    exti_pc13_init();
    tim2_init();

    printf("   STM32 Bare-Metal Sistem Baslatildi   \r\n");
    printf("   PA5: Heartbeat LED (500ms Periyot)   \r\n");
    printf("   PC13: EXTI Buton Kesmesi Devrede     \r\n");

    while (1)
    {
        GPIOA->ODR ^= (1U << 5);

        if (kesme_tetiklendi)
        {
            printf("[KESME] Butona Basildi! Toplam Basma: %lu\r\n", buton_basma_sayisi);
            kesme_tetiklendi = 0;
        }

        tim2_delay_1s();
    }

    return 0;
}
