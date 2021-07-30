/******************************************************************************
 *
 * Module: Microcontroller 1
 *
 * File Name: MC_one.c
 *
 * Description: source file of the first Microcontroller
 *
 * Author: Yasmien Abdelaziz Hamza
 *
 *******************************************************************************/

#include"UART.h"
#include"LCD.h"
#include"Keypad.h"
#include"Timer.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define M2_READY 0x10
/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
uint8 data;
uint8 str1[6];
uint8 str2[6];
uint8 n = 0;
uint8 check;
uint8 door;
volatile int count = 0;
volatile int seconds = 0;
int y = 0;
Timer_ConfigType config2 = {F_CPU_CLOCK,RISING,Normal,0,65500};
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void Set_Password(); // function to set the password
void Door(); // function for opening/closinng the door
void Change_Password(); //function for changing password
void Door_opening(void); //callback function of Timer driver

/*******************************************************************************
 *                      Main Function                                  *
 *******************************************************************************/
int main()
{
	UART_ConfigType config = {eight,Asynchronous,Disabled,one};
	UART_init(&config);
	LCD_init();
	Set_Password();
	Timer1_setCallBack(Door_opening);
	for(int i = 0 ; i < 5 ; i++) // sending the password to ECU 2 in order to be saved in the EEPROM
	{
		UART_sendByte(str1[i]);
		_delay_ms(100);
	}
	while(1)
	{
		LCD_displayString(" - : Open Door");
		LCD_goToRowColumn(2,0);
		LCD_displayString(" + : Change Pass");
		data = Keypad_getPressedKey(); // we used it to determine which action would the first ECU take
		if (data == '-')
		{
			Door();
		}
		else if(data == '+')
		{
			Change_Password();
		}
	}
}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
void Set_Password()		//setting the new password function
{
	UART_sendByte('0'); // this byte is sent in order to call the setting password function in ECU2
	_delay_ms(100);
	LCD_displayString(" Enter New Pass:");
	LCD_goToRowColumn(2,4);
	for(int i = 0 ; i < 5 ; i++)
	{
		str1[i] =  Keypad_getPressedKey();
		LCD_displayCharacter('*');
		_delay_ms(300);
	}
	_delay_ms(100);
	LCD_clearScreen();
	LCD_displayString(" Re-enter Pass:");
	LCD_goToRowColumn(2,4);
	for(int i = 0 ; i < 5 ; i++)
	{

		str2[i] =  Keypad_getPressedKey();
		LCD_displayCharacter('*');
		_delay_ms(300);
	}
	_delay_ms(100);
	for(int i = 0; i < 5 ; i++ )
	{
		if(str1[i] == str2[i])
		{
			n++;
		}
	}
	if(n==5) // checking if the two strings are equal before sending  the password to the second microcontroller
	{
		LCD_clearScreen();
		LCD_displayString(" Matches");
	}
	else
	{
		LCD_clearScreen();
		LCD_displayString(" Not Match");
		_delay_ms(300);
		LCD_clearScreen();
		for(int i = 0; i < 5 ; i++ )
		{
			str1[i] = 0;
			str2[i] = 0;
		}
		n = 0;
		Set_Password(); //repeating the steps again
	}
	n = 0;
	_delay_ms(300);
	LCD_clearScreen();
}

void Door()
{
	UART_sendByte('1'); // this byte is sent in order to call the checking password function in ECU2 in order to open the door
	LCD_clearScreen();
	_delay_ms(300);
	LCD_displayString(" Enter Pass :");
	LCD_goToRowColumn(2,4);

	for (int i = 0 ; i < 5 ; i++)
	{
		str2[i] = Keypad_getPressedKey();
		LCD_displayCharacter('*');
		_delay_ms(300);
	}

	for(int i = 0 ; i < 5 ; i++) // sending the entered password to the second ECU to be checked
	{
		UART_sendByte(str2[i]);
		_delay_ms(100);
	}
	LCD_clearScreen();

	check = UART_receiveByte(); // a received byte from microcontroller 2 to display if the password is correct or not
	_delay_ms(100);
	LCD_goToRowColumn(2,4);
	if(check == '1') //password is correct
	{
		LCD_displayString("CORRECT!");
		_delay_ms(500);
		Timer1_init(&config2);
		LCD_clearScreen();
		while(seconds >= 0 && seconds <= 15) // door is opening
		{
			LCD_goToRowColumn(2,0);
			LCD_displayString("Door is Opening");
		}
		LCD_clearScreen();
		while(seconds >= 16 && seconds <= 18)
		{
			LCD_goToRowColumn(2,0);
			LCD_displayString("Door is Opened");
		}
		LCD_clearScreen();
		while(seconds >= 19 && seconds <= 33) //door is closing
		{
			LCD_goToRowColumn(2,0);
			LCD_displayString("Door is Closing");
		}
		if (seconds == 34 )
		{
			seconds = 0;
			Timer1_deinit();
		}
	}
	else if (check == '0')// the user entered a wrong password
	{
		LCD_displayString("WRONG!!");
		_delay_ms(500);
		Door();
	}
	else if(check == '3') //the user entered the wrong password for three times
	{
		LCD_displayString("ERROR!!");
		Timer1_init(&config2);
		while (seconds != 60);
		seconds = 0;
		Timer1_deinit();
	}
	_delay_ms(500);
	LCD_clearScreen();
}

void Change_Password()
{
	LCD_clearScreen();
	_delay_ms(250);
	Set_Password();
	for(int i = 0 ; i < 5 ; i++)
	{
		UART_sendByte(str1[i]);
		_delay_ms(100);
	}
}

void Door_opening(void)
{
	count++;
	if (count == 123 ) // (8000000 / 65500) = 123
	{
		seconds++;
		count = 0;
	}
}

