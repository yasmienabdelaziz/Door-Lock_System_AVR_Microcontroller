/******************************************************************************
 *
 * Module: I2C
 *
 * File Name: I2C.h
 *
 * Description: header file for the I2C driver
 *
 * Author: Yasmien Abdelaziz Hamza
 *
 *******************************************************************************/

#ifndef I2C_H_
#define I2C_H_

#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

#define TW_START         0x08
#define TW_REP_START     0x10
#define TW_MT_SLA_W_ACK  0x18
#define TW_MT_SLA_R_ACK  0x40
#define TW_MT_DATA_ACK   0x28
#define TW_MR_DATA_ACK   0x50
#define TW_MR_DATA_NACK  0x58

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef uint8 Address;

typedef uint8 Bit_rate;

typedef struct
{
	Address add; // slave address
	Bit_rate bit_rate; // division factor that controls bit rate
}I2C_ConfigType;
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void TWI_Init(const I2C_ConfigType * Config_Ptr);
void TWI_Start();
void TWI_Stop();
void TWI_Write(uint8 data);
uint8 TWI_Read_With_ACK();
uint8 TWI_Read_With_NACK();
uint8 TWI_Get_Status();

#endif /* I2C_H_ */
