/******************************************************************************
*  File name:		twi.c
*  Author:			Oct 22, 2022
*  Author:			Ahmed Tarek
*******************************************************************************/

/*******************************************************************************
*                        		Inclusions                                     *
*******************************************************************************/

#include "twi.h"
#include "avr/io.h"
#include "../../LIB/common_macros.h"

/*******************************************************************************
*                      Functions Definitions                                   *
*******************************************************************************/

void TWI_init(const TWI_ConfigType * Config_Ptr)
{
	TWCR = (1<<TWEN);
	TWAR = Config_Ptr->address;
	TWSR = 0x00; /* assuming it is equal to 0 always and get TWBR based on that assumption */
	TWBR = (uint8)(((F_CPU/((Config_Ptr->bit_rate)*1000))-16) /2);

}

void TWI_start()
{
	TWCR = (1<<TWEN)| (1<<TWINT) | (1<<TWSTA) ;
	while( BIT_IS_CLEAR(TWCR,TWINT) ){}

}

void TWI_stop()
{
	TWCR = (1<<TWEN)| (1<<TWINT) | (1<<TWSTO) ;
}

void TWI_writeByte(uint8 byte)
{
	TWDR = byte;

	TWCR = (1<<TWEN)| (1<<TWINT) ;
	while( BIT_IS_CLEAR(TWCR,TWINT) ){}
}

uint8 TWI_readByteWithACK(void)
{
	TWCR = (1<<TWEN)| (1<<TWINT) | (1<<TWEA) ;
	while( BIT_IS_CLEAR(TWCR,TWINT) ){}
	return TWDR;
}

uint8 TWI_readByteWithNACK(void)
{
	TWCR = (1<<TWEN)| (1<<TWINT) ;
	while( BIT_IS_CLEAR(TWCR,TWINT) ){}
	return TWDR;
}

uint8 TWI_getStatus(void)
{
	uint8 status;
    status = TWSR & 0xF8;
	return status;
}
