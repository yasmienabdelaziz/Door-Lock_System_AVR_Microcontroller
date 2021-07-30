/******************************************************************************
 *
 * Module: LCD
 *
 * File Name: LCD.c
 *
 * Description: Source file for the LCD driver
 *
 * Author: Yasmien Abdelaziz Hamza
 *
 *******************************************************************************/

#include "LCD.h"

void LCD_init()
{
	LCD_CTRL_DIR |= (1<<Rs)|(1<<RW)|(1<<E);
	#if(DATA_BITS_MODE == 4)
	#ifdef UPPER_PORT_PINS
	LCD_DATA_DIR |= 0xF0;
	#else
	LCD_DATA_DIR |= 0x0F;
	#endif
	LCD_sendCommand(FOUR_BITS_DATA_MODE);
	LCD_sendCommand(TWO_LINE_LCD_FOUR_BIT_MODE);
	#elif(DATA_BITS_MODE==8)
	LCD_DATA_DIR = 0xFF;
	LCD_sendCommand(TWO_LINE_LCD_Eight_BIT_MODE); /* 2 lines + 8bit mode */
	#endif
	LCD_sendCommand(CURSOR_OFF); /* Cursor_OFF */
	LCD_sendCommand(CLEAR_COMMAND); /* Clear screen */
}

void LCD_sendCommand(uint8 command)
{
	CLEAR_BIT(LCD_CTRL_PORT,Rs);
	CLEAR_BIT(LCD_CTRL_PORT,RW);
	_delay_ms(1);
	SET_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);

	#if(DATA_BITS_MODE == 4)
	#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (command & 0xF0);
	#else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((command & 0xF0) >> 4);
	#endif

	_delay_ms(1);
	CLEAR_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);
	SET_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);

	#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((command & 0x0F) << 4);
	#else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | (command & 0x0F);
	#endif

	_delay_ms(1);
	CLEAR_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);

	#elif(DATA_BITS_MODE==8)
	LCD_DATA_PORT = command;
	_delay_ms(1);
	CLEAR_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);
	#endif
}

void LCD_displayCharacter(uint8 data)
{
	SET_BIT(LCD_CTRL_PORT,Rs);
	CLEAR_BIT(LCD_CTRL_PORT,RW);
	_delay_ms(1);
	SET_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);
	#if(DATA_BITS_MODE == 4)
	#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (data & 0xF0);
	#else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((data & 0xF0) >> 4);
	#endif
	_delay_ms(1);
	CLEAR_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);
	SET_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);
	#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((data & 0x0F) << 4);
	#else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | (data & 0x0F);
	#endif
	_delay_ms(1);
	CLEAR_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);
	#elif(DATA_BITS_MODE==8)
	LCD_DATA_PORT = data;
	_delay_ms(1);
	CLEAR_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);
	#endif
}

void LCD_displayString(const char * str)
{
	uint8 i = 0;
	while( str[i] != '\0')
	{
		LCD_displayCharacter(str[i]);
		i++;
	}
}

void LCD_goToRowColumn(uint8 row, uint8 col)
{
	uint8 address;
	switch(row)
	{
		case 0 : address = col;
		break;
		case 1 : address = col + 0x40;
		break;
		case 2 : address = col + 0x10;
		break;
		case 3 : address = col + 0x50;
		break;
	}
	LCD_sendCommand(address | SET_CURSOR_LOCATION);
}

void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str)
{
	LCD_goToRowColumn(row,col); /* go to to the required LCD position */
	LCD_displayString(Str); /* display the string */
}

void LCD_integertostring(int data)
{
	uint8 buffer[16];
	itoa(data,buffer,10);
	LCD_displayString(buffer);
}

void LCD_clearScreen()
{
	LCD_sendCommand(CLEAR_COMMAND);
}
