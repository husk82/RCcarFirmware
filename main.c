#include "motor.h"
#include "pin_config_h.h"
#include "controller.h"
#include "gpio_h.h"

int main(void)
{
	PIN_Config_Init();
	__enable_irq();
	
	while(1)
	{
		char cmd = Controller_Get_Command();
		
		if (cmd == 'L')
			GPIO_Set_Pin(GPIOA, 5);
		else
			GPIO_Reset_Pin(GPIOA, 5);
	}
}