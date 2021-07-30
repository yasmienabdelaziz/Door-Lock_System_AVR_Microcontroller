/******************************************************************************
 *
 * Module: TIMER
 *
 * File Name: Timer.c
 *
 * Description: Source file for the Keypad driver
 *
 * Author: Yasmien Abdelaziz Hamza
 *
 *******************************************************************************/

#include "Timer.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}
}

ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}
}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void Timer1_init(const Timer_ConfigType * Config_Ptr)
{
	SREG |= (1<<7);
	TCCR1A = (1<<FOC1A);
	TCCR1B |= (TCCR1B & 0xF8) | ((Config_Ptr -> clock)); //zabat el clock bta3 el timer
	TCCR1B |= (TCCR1B & 0xF7) | ((Config_Ptr -> mode) << 3); // mode
	// condition for checking the mode of the timer for enabling the Timer interrupt mask register (TIMSK)
	if((Config_Ptr -> mode) == CTC)
	{
		TIMSK = (1<<OCIE1A);
	}
	else if((Config_Ptr -> mode) == Normal)
	{
		TIMSK = (1<<TOIE1);
	}
	TCNT1 = (Config_Ptr -> initial); // initial value
	//condition for checking if the mode is compare mode it will insert Final value in Output compare register 1A
	if((Config_Ptr -> mode) == CTC )
	{
		OCR1A = (Config_Ptr -> final);
	}
}

void Timer1_setCallBack(void(*a_ptr)(void))
{
	g_callBackPtr = a_ptr;
}

void Timer1_deinit()
{
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	OCR1A = 0;
	TIMSK = 0;
}
