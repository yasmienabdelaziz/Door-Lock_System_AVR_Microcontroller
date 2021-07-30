/******************************************************************************
 *
 * Module: EEPROM
 *
 * File Name: EEPROM.c
 *
 * Description: Source file for the external EEPROM
 *
 * Author: Yasmien Abdelaziz Hamza
 *
 *******************************************************************************/

#include "EEPROM.h"
#include "I2C.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/


void EEPROM_init(void)
{
	I2C_ConfigType Config = {0b00000010,2};
	TWI_Init(&Config);
}

uint8 EEPROM_writeByte(uint16 u16addr,uint8 u8data)
{
	TWI_Start();
	if((TWI_Get_Status()) != TW_START )
	{
		return ERROR;
	}

	TWI_Write((uint8)((0xA0) | ((u16addr & 0x0700)>>7)));
	if((TWI_Get_Status()) != TW_MT_SLA_W_ACK )
	{
		return ERROR;
	}

	TWI_Write((uint8)u16addr);
	if((TWI_Get_Status()) != TW_MT_DATA_ACK )
	{
		return ERROR;
	}

	TWI_Write(u8data);
	if((TWI_Get_Status()) != TW_MT_DATA_ACK )
	{
		return ERROR;
	}

	TWI_Stop();

	return SUCCESS;
}

uint8 EEPROM_readByte(uint16 u16addr,uint8 *u8data)
{
	TWI_Start();
	if((TWI_Get_Status()) != TW_START )
	{
		return ERROR;
	}

	TWI_Write((uint8)((0xA0) | ((u16addr & 0x0700)>>7)));
	if((TWI_Get_Status()) != TW_MT_SLA_W_ACK )
	{
		return ERROR;
	}

	TWI_Write((uint8)u16addr);
	if((TWI_Get_Status()) != TW_MT_DATA_ACK )
	{
		return ERROR;
	}

	TWI_Start();
	if((TWI_Get_Status()) != TW_REP_START )
	{
		return ERROR;
	}

	TWI_Write((uint8)((u16addr & 0x700)>>7) | 0xA0 | 1);
	if((TWI_Get_Status()) != TW_MT_SLA_R_ACK )
	{
		return ERROR;
	}

	*u8data = TWI_Read_With_NACK();
	if (TWI_Get_Status() != TW_MR_DATA_NACK)
	{
		return ERROR;
	}

	TWI_Stop();
	return SUCCESS;

}

uint8 EEPROM_readstring(uint16 u16addr,uint8 * str)
{
	TWI_Start();
	if((TWI_Get_Status()) != TW_START )
	{
		return ERROR;
	}

	TWI_Write((uint8)((0xA0) | ((u16addr & 0x0700)>>7)));
	if((TWI_Get_Status()) != TW_MT_SLA_W_ACK )
	{
		return ERROR;
	}

	TWI_Write((uint8)u16addr);
	if((TWI_Get_Status()) != TW_MT_DATA_ACK )
	{
		return ERROR;
	}

	TWI_Start();
	if((TWI_Get_Status()) != TW_REP_START )
	{
		return ERROR;
	}

	TWI_Write((uint8)((u16addr & 0x700)>>7) | 0xA0 | 1);
	if((TWI_Get_Status()) != TW_MT_SLA_R_ACK )
	{
		return ERROR;
	}

	str[0] = TWI_Read_With_ACK();
	if (TWI_Get_Status() != TW_MR_DATA_ACK)
	{
		return ERROR;
	}

	str[1] = TWI_Read_With_ACK();
	if (TWI_Get_Status() != TW_MR_DATA_ACK)
	{
		return ERROR;
	}

	str[2] = TWI_Read_With_ACK();
	if (TWI_Get_Status() != TW_MR_DATA_ACK)
	{
		return ERROR;
	}

	str[3] = TWI_Read_With_ACK();
	if (TWI_Get_Status() != TW_MR_DATA_ACK)
	{
		return ERROR;
	}

	str[4] = TWI_Read_With_NACK();
	if (TWI_Get_Status() != TW_MR_DATA_NACK)
	{
		return ERROR;
	}

	TWI_Stop();
	return SUCCESS;
}
