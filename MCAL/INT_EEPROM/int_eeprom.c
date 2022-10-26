/******************************************************************************
*  File name:		int_eeprom.c
*  Author:			Oct 22, 2022
*  Author:			Ahmed Tarek
*******************************************************************************/

/*******************************************************************************
*                        		Inclusions                                     *
*******************************************************************************/

#include "int_eeprom.h"
#include "avr/io.h"
#include "../../LIB/common_macros.h"

/*******************************************************************************
*                      Functions Definitions                                   *
*******************************************************************************/

void INT_EEPROM_writeByteOPT(uint16 address, uint8 byte)
{
	/* waiting the previous writing to be done */
	while( BIT_IS_SET(EECR,EEWE) ){}

	EEAR = address;
	EEDR = byte;

	SET_BIT(EECR,EEMWE); /* Set EEMWE then set EEWE within 4 clock cycles */
	SET_BIT(EECR,EEWE); /* Set EEWE to be able to write the byte */
}

void INT_EEPROM_writeBlock(uint16 address, uint8* array, uint8 size)
{
	uint8 counter = 0;
	while(counter < size)
	{
		INT_EEPROM_writeByte(address+counter, *(array+counter));
		counter++;
	}
}

uint8 INT_EEPROM_readByte(uint16 address)
{
	/* waiting the previous writing to be done */
	while( BIT_IS_SET(EECR,EEWE) ){}

	EEAR = address;

	SET_BIT(EECR,EERE); /* Set EERE to be able to read the value */

	return EEDR;
}

void INT_EEPROM_readBlock(uint16 address, uint8* array , uint8 size)
{
	uint8 counter = 0;
	while(counter < size)
	{
		array[counter] = INT_EEPROM_readByte(address+counter);
		counter++;
	}
}
