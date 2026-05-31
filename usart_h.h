#ifndef USART_H
#define USART_H

#include "stm32f411xe.h"

void USART_Init(USART_TypeDef *USARTx, uint32_t pclk, uint32_t baud);

void USART_Write_Char(USART_TypeDef *USARTx, char ch);

void USART_Write_String(USART_TypeDef *USARTx, char *str);

char USART_ReadChar(USART_TypeDef *USARTx);

#endif