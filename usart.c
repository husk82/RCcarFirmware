#include "usart_h.h"
#include "controller.h"


void USART_Init(USART_TypeDef *USARTx, uint32_t pclk, uint32_t baud)
{
	USARTx->BRR = (pclk + (baud/2)) / baud;
	USARTx->CR1 |= USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE | USART_CR1_UE;
	
	//NVIC enable 
	if (USARTx == USART1)
	{
		NVIC_EnableIRQ(USART1_IRQn);
	}
}

void USART_Write_Char(USART_TypeDef *USARTx, char ch)
{
	while (!(USARTx->SR & USART_SR_TXE));
	USARTx->DR = (uint8_t)ch;
}

void USART_Write_String(USART_TypeDef *USARTx, char *str)
{
	while (*str)
	{
		USART_Write_Char(USARTx, *str++);
	}
}

	// -- USE ISR  instead. This have blocking code of line --
char USART_ReadChar(USART_TypeDef *USARTx)
{
	while (!(USARTx->SR & USART_SR_RXNE));
	return (char)(USARTx->DR & 0xFF);
}

/*
----------------------------------
USART INTERRUPT HANDLER
FILLS BUFFER UNTIL '\n'
----------------------------------
*/
void USART1_IRQHandler(void)
{                
	volatile uint32_t temp;
	if (USART1->SR & USART_SR_RXNE)
	{
		temp = USART1->DR;
		char c = (char)temp;
		if (c != '\n' && c != '\r')
		{
			Controller_Update_Command(c);
		}
	}
}