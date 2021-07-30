/******************************************************************************
 *
 * Module: Microcontroller 2
 *
 * File Name: MC_two.c
 *
 * Description: source file of the second Microcontroller
 *
 * Author: Yasmien Abdelaziz Hamza
 *
 *******************************************************************************/
#include"UART.h"
#include"EEPROM.h"
#include"Timer.h"
/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define M2_READY 0x10
/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
uint8 data; // to know what should happen
uint8 str3[6]; //string that is used for setting password in EEPROM
uint8 str4[6];// both str4 and str arre used to compare tha entered password with the password saved in EEPROM
uint8 str[6];
volatile uint8 count = 0; //used in tha call back function of timer
volatile uint16 address = 0x0002;
volatile uint8 s = 0; // to check if the two strings are equal or not
volatile uint8 y = 0; //to count the number of wrong enters
int seconds = 0; // to count the number of secods for opening/closing the door
Timer_ConfigType config2 = {F_CPU_CLOCK,RISING,Normal,0,65500};

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void setting_password(); //function that saves the password in the EEPROM
void checking_password(); //function to compare the entered password with the saved password in the EEPROM
void Door_opening(void); //Call back function of the Timer
//the next three functions are for opening/closing the door
void motor_clockwise();
void motor_stop();
void motor_anti_clockwise();

/*******************************************************************************
 *                      Main Function                                  *
 *******************************************************************************/
int main()
{
	UART_ConfigType config1 = {eight,Asynchronous,Disabled,one};
	DDRC |= (1<<2);
	DDRC |= (1<<3);
	DDRD |= (1<<PD2);
	DDRD |= (1<<PD3);
	SREG |= (1<<7);
	Timer1_setCallBack(Door_opening);
	EEPROM_init();
	UART_init(&config1);
	_delay_ms(100);

	while(1)
	{
		data = UART_receiveByte(); // we used it to determine which action would the second ECU take
		if(data == '0')
		{
			setting_password();
		}
		else if(data == '1')
		{
			checking_password();
		}
	}
}
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
void setting_password()
{
	_delay_ms(100);
	for ( int i = 0 ; i < 5 ; i++ ) // receiving and saving the entered password
	{
		str3[i] = UART_receiveByte();
		EEPROM_writeByte((address+i),str3[i]);
	}
}

void checking_password()
{
	_delay_ms(100);
	for(int i = 0 ; i < 5 ; i++ ) //comparing between the entered password and the password inside the EEPROM
	{
		str[i] = UART_receiveByte();
		_delay_ms(100);
		EEPROM_readByte((address+i),str4 + i );
		_delay_ms(100);
		if(str[i] == str4[i])
		{
			s++;
		}
		_delay_ms(100);
	}
	_delay_ms(100);
	if ( s == 5 ) //checking if the password matches
	{
		UART_sendByte('1'); //sending this byte to confirm the password matching to the first ECU
		_delay_ms(600);
		Timer1_init(&config2);
		while(seconds >= 0 && seconds <= 15)
		{
			motor_clockwise();
		}
		while(seconds >= 16 && seconds <= 18)
		{
			motor_stop();
		}
		while(seconds >= 19 && seconds <= 33)
		{
			motor_anti_clockwise();
		}
		if (seconds == 34 )
		{
			seconds = 0;
			motor_stop();
			Timer1_deinit();
		}
		s = 0;
	}
	else
	{
		y++;
		if (y < 3 )
		{
			UART_sendByte('0'); //sending this byte to tell the first ECU that the entered password is wrong
			_delay_ms(100);
			s = 0;
			checking_password();
		}
		else if ( y == 3 )
		{
			UART_sendByte('3');//sending this byte to tell the first ECU that the user entered the password wrongly for three times
			_delay_ms(100);
			PORTD |= (1<<PD2); // the buzzer activation
			Timer1_init(&config2);
			while (seconds != 60);
			seconds = 0;
			PORTD &=~ (1<<PD2);
			y = 0;
			s = 0;
		}
	}

}

void Door_opening(void)
{
	count++;
	if (count == 123 )
	{
		seconds++;
		count = 0;
	}
}

void motor_clockwise()
{
	PORTC &= (~(1<<PC2));
	PORTC |= (1<<PC3);
}

void motor_stop()
{
	PORTC &=~ (1<<3);
	PORTC &=~ (1<<2);
}

void motor_anti_clockwise()
{
	PORTC |= (1<<PC2);
	PORTC &= (~(1<<PC3));
}
