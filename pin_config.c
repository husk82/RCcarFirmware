#include "pin_config_h.h"
#include "rcc_h.h"
#include "gpio_h.h"
#include "tim_h.h"
#include "usart_h.h"

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

USART1
-------
PA9 -> TX
PA10 -> RX

Notes
-----
All PWM signals use TIM2
PWM Frequency controlled by PSC and ARR
Direction controlled by GPIO outputs

*/


/*
PWM Frequency Calculation

F_PWM = TimerClock / ((PSC + 1) * (ARR + 1))

16 MHz / ((0 + 1) * (1249 + 1))
= 12.8 kHz
*/
PWM_Config pwm = {TIM2, 0 , PWM_ARR};

#define MOTOR_COUNT 4

Motor_Config motors[4] =
{
    {GPIOA, 0, GPIO_AF1, TIM2, 1, GPIOB, 0,  GPIOB, 1,  1.00f},  // LF
    {GPIOA, 1, GPIO_AF1, TIM2, 2, GPIOB, 10, GPIOB, 12, 0.95f},  // LR
    {GPIOA, 2, GPIO_AF1, TIM2, 3, GPIOB, 13, GPIOB, 14, 1.05f},  // RF
    {GPIOA, 3, GPIO_AF1, TIM2, 4, GPIOB, 15, GPIOA, 8,  0.97f}   // RR
};

USART_Config usart1 = {GPIOA, 9, GPIOA, 10, GPIO_AF7, USART1};

void PIN_Config_Init(void)
{
	// Clock enable
	RCC_Init();
	
	RCC_Enable_GPIOx(GPIOA);
	RCC_Enable_GPIOx(GPIOB);
	
	RCC_Enable_TIMx(TIM2);
	
	RCC_Enable_USARTx(USART1);
	
	// Init STATUS LED   
	GPIO_Init(GPIOA, 5, GPIO_MODE_OUTPUT, GPIO_OTYPE_PP, GPIO_SPEED_LOW, GPIO_NOPUPD);
	GPIO_Reset_Pin(GPIOA, 5); 
	
	// Init MOTOR PWM PINS and set AF
	for (int i = 0; i < MOTOR_COUNT; i++)
	{
		Motor_Config *motor = &motors[i];
		GPIO_Init(motor->pwm_port, motor->pwm_pin, GPIO_MODE_AF, GPIO_OTYPE_PP, GPIO_SPEED_MEDIUM, GPIO_NOPUPD);
		GPIO_Set_AF(motor->pwm_port, motor->pwm_pin, motor->pwm_af);
		GPIO_Init(motor->dir1_port, motor->dir1_pin, GPIO_MODE_OUTPUT, GPIO_OTYPE_PP, GPIO_SPEED_MEDIUM, GPIO_NOPUPD); 
		GPIO_Init(motor->dir2_port, motor->dir2_pin, GPIO_MODE_OUTPUT, GPIO_OTYPE_PP, GPIO_SPEED_MEDIUM, GPIO_NOPUPD); 
		GPIO_Reset_Pin(motor->dir1_port, motor->dir1_pin);
		GPIO_Reset_Pin(motor->dir2_port, motor->dir2_pin);
	}
	
	TIM_PWM_Init(pwm.timer, pwm.psc, pwm.arr);          //PSC = 0 and ARR = 1249
	
	for (int i = 0; i < MOTOR_COUNT; i++)
	{
    TIM_PWM_Enable_Channel(motors[i].timer, motors[i].channel);
		TIM_PWM_Set_Duty(motors[i].timer, motors[i].channel, 0);
	}
	
	TIM_Start(TIM2);
	
	// Init USART PINS and set AF
	GPIO_Init(usart1.tx_port, usart1.tx_pin, GPIO_MODE_AF, GPIO_OTYPE_PP, GPIO_SPEED_VERYHIGH, GPIO_NOPUPD);
	GPIO_Init(usart1.rx_port, usart1.rx_pin, GPIO_MODE_AF, GPIO_OTYPE_PP, GPIO_SPEED_VERYHIGH, GPIO_PULLUP);
	
	GPIO_Set_AF(usart1.tx_port, usart1.tx_pin, usart1.af);
	GPIO_Set_AF(usart1.rx_port, usart1.rx_pin, usart1.af);

	USART_Init(usart1.instance, 16000000, 115200);
	
	// Init STANDBY PORT
  GPIO_Init(GPIOA, 4, GPIO_MODE_OUTPUT, GPIO_OTYPE_PP, GPIO_SPEED_LOW, GPIO_NOPUPD);
	GPIO_Set_Pin(GPIOA, 4);
}
