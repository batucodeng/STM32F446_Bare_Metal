#ifndef MAIN_H_
#define MAIN_H_

#include <stdint.h>

#define PERIPH_BASE           0x40000000UL
#define AHB1PERIPH_BASE			(PERIPH_BASE + 0x00020000UL)
#define GPIO_BASE		(AHB1PERIPH_BASE + 0x0000UL)
#define RCC_BASE		(AHB1PERIPH_BASE + 0x3800UL)
#define SysTick_BASE		(0xE000E010UL)
#define SysTick 	((SysTick_TypeDef *) SysTick_BASE)
#define APB1PERIPH_BASE       (PERIPH_BASE + 0x00000000UL)
#define USART2_BASE           (APB1PERIPH_BASE + 0x4400UL)
#define USART2 			((USART_TypeDef *)USART2_BASE)
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x00010000UL)
#define SYSCFG_BASE           (APB2PERIPH_BASE + 0x3800UL)
#define EXTI_BASE             (PERIPH_BASE + 0x00013C00UL)
#define NVIC_BASE             (0xE000E100UL)
#define SYSCFG 		((SYSCFG_TypeDef *) SYSCFG_BASE)
#define EXTI 		((EXTI_TypeDef *) EXTI_BASE)
#define NVIC  		((NVIC_TypeDef *) NVIC_BASE)
#define GPIOA_BASE            (AHB1PERIPH_BASE + 0x0000UL)
#define GPIOC_BASE            (AHB1PERIPH_BASE + 0x0800UL) // <-- Burayı ekle
#define GPIOA                 ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOC                 ((GPIO_TypeDef *) GPIOC_BASE)
#define TIM2_BASE             (APB1PERIPH_BASE + 0x0000UL)
#define TIM2   ((TIM_TypeDef *) TIM2_BASE)


typedef struct {
    volatile uint32_t CR1;         /* 0x00: Kontrol Register 1 */
    volatile uint32_t CR2;         /* 0x04: Kontrol Register 2 */
    volatile uint32_t SMCR;        /* 0x08: Slave Mode Kontrol */
    volatile uint32_t DIER;        /* 0x0C: DMA/Kesme İzinleri */
    volatile uint32_t SR;          /* 0x10: Durum Register */
    volatile uint32_t EGR;         /* 0x14: Olay Üretme */
    volatile uint32_t CCMR1;       /* 0x18: Capture/Compare Mod 1 */
    volatile uint32_t CCMR2;       /* 0x1C: Capture/Compare Mod 2 */
    volatile uint32_t CCER;        /* 0x20: Capture/Compare Çıkış İzni */
    volatile uint32_t CNT;         /* 0x24: Anlık Sayaç Değeri */
    volatile uint32_t PSC;         /* 0x28: Ön Bölücü (Prescaler) */
    volatile uint32_t ARR;         /* 0x2C: Sayaç Limiti (Auto-Reload) */
    volatile uint32_t CCR1;        /* 0x30: Kanal 1 Eşik Değeri (Duty) */
    volatile uint32_t CCR2;        /* 0x34: Kanal 2 Eşik Değeri */
    volatile uint32_t CCR3;        /* 0x38: Kanal 3 Eşik Değeri */
    volatile uint32_t CCR4;        /* 0x3C: Kanal 4 Eşik Değeri */
} TIM_TypeDef;


typedef struct
{
	volatile uint32_t MEMRMP;
	volatile uint32_t PMC;
	volatile uint32_t EXTICR[4];
	volatile uint32_t CMPCR;
	volatile uint32_t CFGR;
} SYSCFG_TypeDef;

typedef struct
{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
} EXTI_TypeDef;

typedef struct
{
	volatile uint32_t ISER[8];
}NVIC_TypeDef;

typedef struct
{
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t GTPR;
} USART_TypeDef;

typedef struct
{
	volatile uint32_t CTRL;
	volatile uint32_t LOAD;
	volatile uint32_t VAL;
	volatile uint32_t CALIB;
}SysTick_TypeDef;


typedef struct
{
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFR[2];
} GPIO_TypeDef;

typedef struct
{
	volatile uint32_t CR;
	volatile uint32_t PLLCFGR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t AHB1RSTR;
	volatile uint32_t AHB2RSTR;
	volatile uint32_t AHB3RSTR;
	uint32_t RESERVED0;
	volatile uint32_t APB1RSTR;
	volatile uint32_t APB2RSTR;
	uint32_t RESERVED1[2];
	volatile uint32_t AHB1ENR;
	volatile uint32_t AHB2ENR;
	volatile uint32_t AHB3ENR;
	uint32_t RESERVED2;
	volatile uint32_t APB1ENR;
	volatile uint32_t APB2ENR;
} RCC_TypeDef;

#define RCC ((RCC_TypeDef *) RCC_BASE)

#define GPIOA ((GPIO_TypeDef *) GPIO_BASE)

#endif





















