/******************************************************************************
 *
 * Module: I2C
 *
 * File Name: I2C.c
 *
 * Description: Source file for the I2C driver
 *
 * Author: Yasmien Abdelaziz Hamza
 *
 *******************************************************************************/

#include"I2C.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
void TWI_Init(const I2C_ConfigType * Config_Ptr)
{
	TWCR = (1<<TWEN);
	TWAR = (Config_Ptr -> add); // slave address
	TWSR = 0;
	TWBR = (Config_Ptr -> bit_rate); // division factor that controls bit rate
}

void TWI_Start()
{
	TWCR = (1<<TWEN) | (1<<TWSTA) | (1<<TWINT); // Enable TWI Operation, sending start bit, clear TWINT flag before starting the operation
	while(BIT_IS_CLEAR(TWCR,TWINT)); //The bit is set by the hardware when The action has finished
}

void TWI_Stop()
{
	TWCR = (1<<TWEN) | (1<<TWSTO) | (1<<TWINT); //Enable TWI Operation, sending stop bit, clear TWINT flag before starting the operation
}

void TWI_Write(uint8 data)
{
	TWDR = data;
	TWCR = (1<<TWEN) | (1<<TWINT); // Enable TWI Operation, clear TWINT flag before starting the operation
	while(BIT_IS_CLEAR(TWCR,TWINT));
}

uint8 TWI_Read_With_ACK()
{
	TWCR = (1<<TWEN) | (1<<TWINT) | (1<<TWEA); // Enable TWI Operation, enabling Ack bit, clear TWINT flag beafore starting the operation
	while(BIT_IS_CLEAR(TWCR,TWINT));
	return TWDR;
}

uint8 TWI_Read_With_NACK()
{
	TWCR = (1<<TWEN) | (1<<TWINT);// Enable TWI Operation, clear TWINT flag beafore starting the operation
	while(BIT_IS_CLEAR(TWCR,TWINT));
	return TWDR;
}

uint8 TWI_Get_Status(void)
{
    uint8 status;
    status = TWSR & 0xF8;
    return status;
}
