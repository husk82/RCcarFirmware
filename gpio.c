#include "gpio_h.h"

void GPIO_Init(GPIO_TypeDef *GPIOx, uint8_t pin, uint8_t mode, uint8_t otype, uint8_t speed, uint8_t pupd)
{
	// Moder
	GPIOx->MODER &= ~(0x3 << (pin * 2));
	GPIOx->MODER |= (mode << (pin * 2));
	
	// OTYPER
	GPIOx->OTYPER &= ~(0x1 << pin);
	GPIOx->OTYPER |= (otype << pin);
	
	// OSPEEDR
	GPIOx->OSPEEDR &= ~(0x3 << (pin * 2));
  GPIOx->OSPEEDR |= (speed << (pin * 2));
	
	// PUPDR
	GPIOx->PUPDR &= ~(0x3 << (pin * 2));
  GPIOx->PUPDR |= (pupd << (pin * 2));
	
}

void GPIO_Set_AF(GPIO_TypeDef *GPIOx, uint8_t pin, uint8_t af)
{
	if (pin< 8)
	{
		GPIOx->AFRL &= ~(0xF << (pin * 4));
		GPIOx->AFRL |= (af << (pin * 4));
	}
	else
	{
		GPIOx->AFRH &= ~(0xF << ((pin - 8) * 4));
		GPIOx->AFRH |= (af << ((pin - 8) * 4));
	}
}

void GPIO_Set_Pin(GPIO_TypeDef *GPIOx, uint16_t pin)
{
	GPIOx->BSRR = (1 << pin);
}

void GPIO_Reset_Pin(GPIO_TypeDef *GPIOx, uint16_t pin)
{
	GPIOx->BSRR = (1 << (pin+16));
}

void GPIO_Toggle_Pin(GPIO_TypeDef *GPIOx, uint16_t pin)
{
	GPIOx->ODR ^= (1 << pin);
}

