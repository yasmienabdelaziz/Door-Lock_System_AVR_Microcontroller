 /******************************************************************************
 *
 * Module: TIMER
 *
 * File Name: Timer.h
 *
 * Description: Header file for the Keypad driver
 *
 * Author: Yasmien Abdelaziz Hamza
 *
 *******************************************************************************/


#ifndef TIMER_H_
#define TIMER_H_

#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}Timer_Clock;

typedef enum
{
	FALLING,RISING
}Timer_EdgeType;

typedef enum
{
	Normal,CTC
}Timer_mode;

typedef int Timer_initial_value;

typedef int Timer_final_value;

typedef struct
{
	Timer_Clock clock;
	Timer_EdgeType edge;
	Timer_mode mode;
	Timer_initial_value initial;
	Timer_final_value final;
}Timer_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void Timer1_init(const Timer_ConfigType * Config_Ptr);
void Timer1_setCallBack(void(*a_ptr)(void));
void Timer1_deinit();
#endif /* TIMER_H_ */
