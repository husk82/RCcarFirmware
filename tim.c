#include "tim_h.h"

void TIM_PWM_Init(TIM_TypeDef *TIMx, uint32_t psc, uint32_t arr)
{
	TIMx->CR1 &= ~TIM_CR1_CEN;
	TIMx->PSC = psc;
	TIMx->ARR = arr;
	TIMx->EGR |= TIM_EGR_UG;              // Force update to load PSC/ARR
	TIMx->CR1 |= TIM_CR1_ARPE;						// Enable auto-reload preload
}
void TIM_PWM_Enable_Channel(TIM_TypeDef *TIMx, uint8_t channel)
{
	switch(channel)
	{
		case 1: 
			TIMx->CCMR1 &= ~TIM_CCMR1_OC1M;
			TIMx->CCMR1 |= (6 << 4 );							// OC1M = 110 -> PWM Mode 1
			TIMx->CCMR1 |= TIM_CCMR1_OC1PE;				// Preload enable
			TIMx->CCER |= TIM_CCER_CC1E;					// Enable output
			break;
		case 2: 
			TIMx->CCMR1 &= ~TIM_CCMR1_OC2M;
			TIMx->CCMR1 |= (6 << 12 );						// OC1M = 110 -> PWM Mode 1
			TIMx->CCMR1 |= TIM_CCMR1_OC2PE;				// Preload enable
			TIMx->CCER |= TIM_CCER_CC2E;					// Enable output
			break;
		case 3: 
			TIMx->CCMR2 &= ~TIM_CCMR2_OC3M;
			TIMx->CCMR2 |= (6 << 4 );							// OC1M = 110 -> PWM Mode 1
			TIMx->CCMR2 |= TIM_CCMR2_OC3PE;				// Preload enable
			TIMx->CCER |= TIM_CCER_CC3E;					// Enable output
			break;
		case 4: 
			TIMx->CCMR2 &= ~TIM_CCMR2_OC4M;
			TIMx->CCMR2 |= (6 << 12 );						// OC1M = 110 -> PWM Mode 1
			TIMx->CCMR2 |= TIM_CCMR2_OC4PE;				// Preload enable
			TIMx->CCER |= TIM_CCER_CC4E;					// Enable output
			break;
	}
}
void TIM_PWM_Set_Duty(TIM_TypeDef *TIMx, uint8_t channel, uint32_t duty)
{
	switch(channel)
	{
		case 1: TIMx->CCR1 = duty; break;
		case 2: TIMx->CCR2 = duty; break;
		case 3: TIMx->CCR3 = duty; break;
		case 4: TIMx->CCR4 = duty; break;
	}
}

void TIM_Start(TIM_TypeDef *TIMx)
{
	TIMx->CNT = 0;
	TIMx->CR1 |= TIM_CR1_CEN;
}

void TIM_Stop(TIM_TypeDef *TIMx)
{
	TIMx->CR1 &= ~TIM_CR1_CEN;
}
