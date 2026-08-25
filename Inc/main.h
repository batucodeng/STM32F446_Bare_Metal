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





















