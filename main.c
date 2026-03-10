#include "rcc_h.h"
#include "motor.h"

int main(void)
{
	RCC_Init();
	RCC_Enable_GPIOx(GPIOA);
	RCC_Enable_GPIOx(GPIOB);
	RCC_Enable_TIMx(TIM2);
	
	PIN_Config_Init();
	GPIO_Set_Pin(STATUS_LED_PORT, STATUS_LED_PIN); 
	GPIO_Set_Pin(STANDBY_PORT, STANDBY_PIN);
	
	Motor_Set_Speed(LF, 500);
	Motor_Set_Direction(LF, 1);
	Motor_Set_Speed(LR, 650);
	Motor_Set_Direction(LR, 1);
	Motor_Set_Speed(RF, 900);
	Motor_Set_Direction(RF, 0);
	Motor_Set_Speed(RR, 1000);
	Motor_Set_Direction(RR, 0);
	
	while(1)
	{
		
	}
}