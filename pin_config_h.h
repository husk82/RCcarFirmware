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

Driver Control
--------------
PA4  -> STBY (TB6612 Standby)

Status
------
PA5 -> Status LED

Notes
-----
All PWM signals use TIM2
PWM Frequency controlled by PSC and ARR
Direction controlled by GPIO outputs

*/


#ifndef PIN_CONFIG_H
#define PIN_CONFIG_H
#include "stm32f411xe.h"
#include "gpio_h.h"
#include "tim_h.h"

typedef struct
{
	GPIO_TypeDef *pwm_port;
	uint8_t pwm_pin;
  TIM_TypeDef *timer;
  uint8_t channel;
	
	GPIO_TypeDef *dir1_port;
  uint8_t dir1_pin;
	
	GPIO_TypeDef *dir2_port;
  uint8_t dir2_pin;

} Motor_Config;

extern Motor_Config motors[4];

// Status Led Light: General output
#define STATUS_LED_PORT GPIOA
#define STATUS_LED_PIN 5

// Standby Pin for TB6612
#define STANDBY_PORT GPIOA
#define STANDBY_PIN 4

// PWM Channel
#define PWM_TIMER TIM2

// Motor PWM's PSC, ARR
#define PWM_PSC 0
#define PWM_ARR 1249


void PIN_Config_Init(void);

#endif