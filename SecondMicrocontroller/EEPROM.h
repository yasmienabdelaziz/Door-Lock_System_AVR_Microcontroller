/******************************************************************************
 *
 * Module: EEPROM
 *
 * File Name: EEPROM.h
 *
 * Description: header file for the external EEPROM
 *
 * Author: Yasmien Abdelaziz Hamza
 *
 *******************************************************************************/

#ifndef EEPROM_H_
#define EEPROM_H_

#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define ERROR 0
#define SUCCESS 1

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void EEPROM_init(void);
uint8 EEPROM_writeByte(uint16 u16addr,uint8 u8data);
uint8 EEPROM_readByte(uint16 u16addr,uint8 *u8data);
uint8 EEPROM_readstring(uint16 u16addr,uint8 * str);

#endif /* EEPROM_H_ */
