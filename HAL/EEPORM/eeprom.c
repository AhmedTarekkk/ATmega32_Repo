/******************************************************************************
*  File name:		eeprom.c
*  Author:			Oct 22, 2022
*  Author:			Ahmed Tarek
*******************************************************************************/

/*******************************************************************************
*                        		Inclusions                                     *
*******************************************************************************/

#include "eeprom.h"
#include "../../MCAL/TWI/twi.h"

/*******************************************************************************
*                      Functions Definitions                                   *
*******************************************************************************/

uint8 EEPROM_writeBytr(uint16 address,uint8 byte)
{
	TWI_start();
	if(TWI_getStatus() != TWI_START)
		return ERROR;

	TWI_writeByte( (uint8)(((address&0x0700)>>7) | (0xA0)) );
	if(TWI_getStatus() != TWI_MT_SLA_W_ACK)
		return ERROR;

	TWI_writeByte((uint8)address);
	if(TWI_getStatus() != TWI_MT_DATA_ACK)
		return ERROR;

	TWI_writeByte(byte);
	if(TWI_getStatus() != TWI_MT_DATA_ACK)
		return ERROR;

	TWI_stop();

	return SUCCESS;
}

uint8 EEPROM_readByte(uint16 address,uint8 *value)
{
	TWI_start();
	if(TWI_getStatus() != TWI_START)
		return ERROR;

	TWI_writeByte( (uint8)((address&0x0700)>>7 | (0xA0)) );
	if(TWI_getStatus() != TWI_MT_SLA_W_ACK)
		return ERROR;

	TWI_writeByte((uint8)address);
	if(TWI_getStatus() != TWI_MT_DATA_ACK)
		return ERROR;

	TWI_start();
	if(TWI_getStatus() != TWI_REP_START)
		return ERROR;

    TWI_writeByte((uint8)((0xA0) | ((address & 0x0700)>>7) | 1));
    if (TWI_getStatus() != TWI_MT_SLA_R_ACK)
        return ERROR;

    *value = TWI_readByteWithNACK();
    if (TWI_getStatus() != TWI_MR_DATA_NACK)
        return ERROR;

    TWI_stop();
	return SUCCESS;
}
