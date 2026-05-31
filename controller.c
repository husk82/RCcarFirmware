#include "usart_h.h"
#include "gpio_h.h"

static char current_cmd = 0;

void Controller_Update_Command(char cmd)
{
	
	current_cmd = cmd;
}

char Controller_Get_Command(void)
{
	return current_cmd;
}