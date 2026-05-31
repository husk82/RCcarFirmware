#include "rcc_h.h"

void RCC_Init()
{
	// Enable HSI
	RCC->CR |= RCC_CR_HSION;
	while (!(RCC->CR & RCC_CR_HSIRDY));
	
	// Use HSI as system clock
	RCC->CFGR &= ~RCC_CFGR_SW;
	RCC->CFGR |= RCC_CFGR_SW_HSI;
	
	// Wait until switch is confirmed (SWS = 00)
	while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI);
}

void RCC_Enable_GPIOx(GPIO_TypeDef *GPIOx)
{
	if (GPIOx == GPIOA)
	{
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
		(void)RCC->AHB1ENR;                     //dummy read
	}
	else if (GPIOx == GPIOB)
	{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
		(void)RCC->AHB1ENR;
	}
	else if (GPIOx == GPIOC)
	{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
		(void)RCC->AHB1ENR;
	}
}

void RCC_Enable_TIMx(TIM_TypeDef *TIMx)
{
	if (TIMx == TIM1)
		RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	else if (TIMx == TIM2)
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	else if (TIMx == TIM3)
		RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	else if (TIMx == TIM4)
		RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	
}

void RCC_Enable_USARTx(USART_TypeDef *USARTx)
{
	if (USARTx == USART1) RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	else if (USARTx == USART2) RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
}