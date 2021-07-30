/******************************************************************************
 *
 * Module: UART
 *
 * File Name: UART.h
 *
 * Description: Header file for the UART driver
 *
 * Author: Yasmien Abdelaziz Hamza
 *
 *******************************************************************************/


#ifndef UART_H_
#define UART_H_

#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/


#define USART_BAUDRATE 9600

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum

{
	five,six,seven,eight,x,xx,xxx,nine
}UART_Charsize;

typedef enum
{
	Asynchronous,Synchronous
}UART_Mode;

typedef enum
{
	Disabled,Reserved,Even,Odd
}UART_Parity;

typedef enum
{
	one,two
}UART_Stopbit;

typedef struct
{
	UART_Charsize size;
	UART_Mode mode;
	UART_Parity parity;
	UART_Stopbit stopbit;
}UART_ConfigType;




/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void UART_init(const UART_ConfigType * Config_Ptr );
void UART_sendByte(const uint8 data);
uint8 UART_receiveByte(void);
void UART_sendString(const uint8 *Str);
void UART_receiveString(uint8 *Str);


#endif /* UART_H_ */
