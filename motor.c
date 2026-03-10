#include "motor.h"
#include "pin_config_h.h"

void Motor_Set_Speed(MOTOR_ID motor_id, uint32_t duty)
{
	if (motor_id > RR) return;
	
	if (duty > MAX_DUTY) duty = MAX_DUTY;
	if (duty < MIN_DUTY) duty = MIN_DUTY;
	
	TIM_PWM_Set_Duty(motors[motor_id].timer, motors[motor_id].channel, duty);
	
}
void Motor_Set_Direction(MOTOR_ID motor_id, uint8_t dir)
{
	if (motor_id > RR) return;
	
	if(dir)
	{
		GPIO_Set_Pin(motors[motor_id].dir1_port, motors[motor_id].dir1_pin);
		GPIO_Reset_Pin(motors[motor_id].dir2_port, motors[motor_id].dir2_pin);
	}
	else
	{
		GPIO_Set_Pin(motors[motor_id].dir2_port, motors[motor_id].dir2_pin);
		GPIO_Reset_Pin(motors[motor_id].dir1_port, motors[motor_id].dir1_pin);
	}
}
	
void Motor_Stop(MOTOR_ID motor_id)
{
	TIM_PWM_Set_Duty(motors[motor_id].timer, motors[motor_id].channel, 0);
}