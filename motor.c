#include "motor.h"
#include "pin_config_h.h"
#include "tim_h.h"
#include "gpio_h.h"

// Hardware Config table from pin_config
extern Motor_Config motors[4];

#define MAX_DUTY (PWM_ARR + 1)

void Motor_Set_Speed(MOTOR_ID motor_id, uint32_t duty)
{
	if (motor_id > RR) return;
	
	Motor_Config *motor = &motors[motor_id];
	
	float scaled = duty * motor->calibration;
	
	if (scaled > MAX_DUTY) scaled = MAX_DUTY;

	TIM_PWM_Set_Duty(motor->timer, motor->channel, (uint32_t) scaled);
	
}
void Motor_Set_Direction(MOTOR_ID motor_id, uint8_t dir)
{
	if (motor_id > RR) return;
	
	Motor_Config *motor = &motors[motor_id];
	
	if(dir)
	{
		GPIO_Set_Pin(motor->dir1_port, motor->dir1_pin);
		GPIO_Reset_Pin(motor->dir2_port, motor->dir2_pin);
	}
	else
	{
		GPIO_Set_Pin(motor->dir2_port, motor->dir2_pin);
		GPIO_Reset_Pin(motor->dir1_port, motor->dir1_pin);
	}
}
	
void Motor_Stop(MOTOR_ID motor_id)
{
	if (motor_id > RR) return;
	
	Motor_Config *motor = &motors[motor_id];
	
	TIM_PWM_Set_Duty(motor->timer, motor->channel, 0);
}