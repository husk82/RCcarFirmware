/*
----------------------------------------------------
STM32F411CEU6 Blackpill – Mecanum Robot Pin Layout
----------------------------------------------------

PWM (TIM2)
---------
PA0  -> TIM2_CH1 -> Motor1 PWM
PA1  -> TIM2_CH2 -> Motor2 PWM
PA2  -> TIM2_CH3 -> Motor3 PWM
PA3  -> TIM2_CH4 -> Motor4 PWM

Motor Directions
----------------
Motor1: PB0  -> IN1
        PB1  -> IN2

Motor2: PB10 -> IN1
        PB12 -> IN2

Motor3: PB13 -> IN1
        PB14 -> IN2

Motor4: PB15 -> IN1
        PA8  -> IN2

*/

#include "pin_config_h.h"

// Motor's PWM and Dir pins config
Motor_Config motors[4] =
	{
			{GPIOA, 0, TIM2, 1, GPIOB, 0, GPIOB, 1},
			{GPIOA, 1, TIM2, 2, GPIOB, 10, GPIOB, 12},
			{GPIOA, 2, TIM2, 3, GPIOB, 13, GPIOB, 14},
			{GPIOA, 3, TIM2, 4, GPIOB, 15, GPIOA, 8}
	};

void PIN_Config_Init(void)
{
	
	GPIO_Init(STATUS_LED_PORT, STATUS_LED_PIN, GPIO_MODE_OUTPUT, GPIO_OTYPE_PP, GPIO_SPEED_LOW, GPIO_NOPUPD);

  GPIO_Init(STANDBY_PORT, STANDBY_PIN, GPIO_MODE_OUTPUT, GPIO_OTYPE_PP, GPIO_SPEED_LOW, GPIO_NOPUPD);
	
	TIM_PWM_Init(TIM2, PWM_PSC, PWM_ARR);
	
	for (int i = 0; i < 4; i++)
	{
		GPIO_Init(motors[i].pwm_port, motors[i].pwm_pin, GPIO_MODE_AF, GPIO_OTYPE_PP, GPIO_SPEED_MEDIUM, GPIO_NOPUPD);

    GPIO_Set_AF(motors[i].pwm_port, motors[i].pwm_pin, GPIO_AF1);

    TIM_PWM_Enable_Channel(motors[i].timer, motors[i].channel);

    TIM_PWM_Set_Duty(motors[i].timer, motors[i].channel, 0);

    GPIO_Init(motors[i].dir1_port, motors[i].dir1_pin, GPIO_MODE_OUTPUT, GPIO_OTYPE_PP, GPIO_SPEED_MEDIUM, GPIO_NOPUPD);

    GPIO_Init(motors[i].dir2_port,motors[i].dir2_pin, GPIO_MODE_OUTPUT, GPIO_OTYPE_PP, GPIO_SPEED_MEDIUM, GPIO_NOPUPD); 
		
	}
	
	TIM_Start(TIM2);
}
