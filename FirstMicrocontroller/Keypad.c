 /******************************************************************************
 *
 * Module: KEYPAD
 *
 * File Name: keypad.c
 *
 * Description: Source file for the Keypad driver
 *
 * Author: Yasmien Abdelaziz
 *
 *******************************************************************************/

#include "Keypad.h"

/*******************************************************************************
 *                      Functions Prototypes(Private)                          *
 *******************************************************************************/

#if(N_col==3)
static uint8 Keypad_4x3_adjustSwitchNumber(uint8 Button_number);

#elif(N_col==4)
static uint8 Keypad_4x4_adjustSwitchNumber(uint8 Button_number);
#endif

uint8 Keypad_getPressedKey()
{
	uint8 row, col;

	while(1)
	{
		for(col = 0 ; col < N_col ; col++)
			{
				KEYPAD_PORT_DIR = (0b00010000<<col);
				KEYPAD_PORT_OUT = (~(0b00010000<<col));
				for(row = 0 ; row < N_row ; row++)
				{
					if(BIT_IS_CLEAR(KEYPAD_PORT_IN,row))
					{
						#if(N_col==3)
						return Keypad_4x3_adjustSwitchNumber((row*N_col)+col+1);
						#elif(N_col==4)
						return Keypad_4x4_adjustSwitchNumber((row*N_col)+col+1);
						#endif
					}
				}
			}
	}
}

#if(N_col==3)
uint8 Keypad_4x3_adjustSwitchNumber(uint8 Button_number)
{
	switch(Button_number)
		{
			case 1: return 1;
					break;
			case 2: return 2;
					break;
			case 3: return 3;
					break;
			case 4: return 4;
					break;
			case 5: return 5;
					break;
			case 6: return 6;
					break;
			case 7: return 7;
					break;
			case 8: return 8;
					break;
			case 9: return 9;
					break;
			case 10: return '*'; // ASCII Code of *
					 break;
			case 11: return 0;
					 break;
			case 12: return '#'; // ASCII Code of #
					 break;
			default: return Button_number;
		}
}

#elif(N_col==4)
uint8 Keypad_4x4_adjustSwitchNumber(uint8 Button_number)
{
	switch(Button_number)
		{
			case 1: return '7';
					break;
			case 2: return '8';
					break;
			case 3: return '9';
					break;
			case 4: return '/';
					break;
			case 5: return '4';
				    break;
			case 6:	return '5';
				    break;
			case 7: return '6';
					break;
			case 8: return '*';
				    break;
			case 9: return '1';
				    break;
			case 10: return '2';
				     break;
			case 11: return '3';
					 break;
			case 12: return '-';
				   	 break;
			case 13: return '13';  /* ASCII of Enter */
					 break;
			case 14: return '0';
		  			 break;
			case 15: return '=';
					 break;
			case 16: return '+';
					 break;
			default: return Button_number;
		}
}
#endif
