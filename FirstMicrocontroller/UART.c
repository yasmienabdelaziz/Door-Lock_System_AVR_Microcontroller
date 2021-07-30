/******************************************************************************
 *
 * Module: UART
 *
 * File Name: UART.c
 *
 * Description: Source file for the UART driver
 *
 * Author: Yasmien Abdelaziz Hamza
 *
 *******************************************************************************/

#include "UART.h"

#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 8UL))) - 1)

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void UART_init(const UART_ConfigType * Config_Ptr)
{
	UCSRA |= (1<<U2X);
	UCSRB |= (1<<RXEN) | (1<<TXEN);
	UCSRC |= (1<<URSEL);
	UCSRB |= (UCSRB & 0xFB) | (((Config_Ptr -> size)>>2) << 2); // size if the selected bit size is 9 bits
	UCSRC |= (UCSRC & 0xF9) | ((Config_Ptr -> size) << 1); // size from 5 to 7 bits
	UCSRC |= (UCSRC & 0xBF) | ((Config_Ptr -> mode) << 6); // Mode Select
	UCSRC |= (UCSRC & 0xCF) | ((Config_Ptr -> parity) << 4); // parity Select
	UCSRC |= (UCSRC & 0xF7) | ((Config_Ptr -> stopbit) << 3); //stop bit select
	UBRRH |= BAUD_PRESCALE>>8;
	UBRRL |= BAUD_PRESCALE;
}
void UART_sendByte(const uint8 data)
{
	while(BIT_IS_CLEAR(UCSRA,UDRE));
	UDR = data;
}
uint8 UART_receiveByte(void)
{
	while(BIT_IS_CLEAR(UCSRA,RXC));
	return UDR;
}
void UART_sendString(const uint8 *Str)
{
	int i = 0;
	while(Str[i] != '\0')
	{
		UART_sendByte(Str[i]);
		i++;
	}
}
void UART_receiveString(uint8 *Str)
{
	int i = 0;
	Str[i] = UART_receiveByte();
	while(Str[i] != '#')
	{
		Str[i] = UART_receiveByte();
		_delay_ms(100);
		i++;
	}
}
