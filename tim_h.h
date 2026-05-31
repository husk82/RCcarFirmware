#ifndef TIM_H
#define TIM_H

#include <stdint.h>
#include "stm32f4xx.h"

/*
TIM2 Input Clock = 16 MHz (HSI)

PWM Frequency:
16 MHz / ((PSC + 1) * (ARR + 1))

= 12.8 kHz
*/
#define PWM_ARR 1249

// Timer base config
void TIM_PWM_Init(TIM_TypeDef *TIMx, uint32_t psc, uint32_t arr);

// Enable specific PWM Channel
void TIM_PWM_Enable_Channel(TIM_TypeDef *TIMx, uint8_t channel);

// Set duty cycle(channel 1-4)
void TIM_PWM_Set_Duty(TIM_TypeDef *TIMx, uint8_t channel, uint32_t duty);

// Start timer
void TIM_Start(TIM_TypeDef *TIMx);

// Stop timer
void TIM_Stop(TIM_TypeDef *TIMx);

#endif