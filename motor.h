#ifndef MOTOR_H
#define MOTOR_H

#include "stm32f411xe.h"
#include "pin_config_h.h"

#define MAX_DUTY (PWM_ARR + 1)
#define MIN_DUTY 0

typedef enum
{
	LF = 0,		// Left Front
	LR = 1, 	// Left Rear 
	RF = 2,		// Right Front
	RR = 3		// Right Rear
} MOTOR_ID;

//Motor control functions
void Motor_Set_Speed(MOTOR_ID motor_id, uint32_t duty);
void Motor_Set_Direction(MOTOR_ID motor_id, uint8_t dir);
void Motor_Stop(MOTOR_ID motor_id);

#endif