 /******************************************************************************
 *
 * Module: Micro - Configuration
 *
 * File Name: Micro_Config.h
 *
 * Description: File include all Microcontroller libraries
 *
 * Author: Yasmien Abdelaziz hamza
 *
 *******************************************************************************/

#ifndef MICRO_CONFIG_H_
#define MICRO_CONFIG_H_


#undef F_CPU 1000000UL
#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#endif /* MICRO_CONFIG_H_ */
