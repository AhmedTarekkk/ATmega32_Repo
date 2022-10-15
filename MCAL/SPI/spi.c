/******************************************************************************
*  File name:		main.c
*  Author:			Oct 14, 2022
*  Author:			Ahmed Tarek
*******************************************************************************/

/*******************************************************************************
*                        		Inclusions                                     *
*******************************************************************************/

#include "spi.h"
#include "avr/io.h"
#include "../GPIO/gpio.h"
#include "../../LIB/common_macros.h"

/*******************************************************************************
*                           Global Variables                                  *
*******************************************************************************/

/* to store the special char to end sting at and it has default value = # */
static uint8 g_endStringChar = '#';

/*******************************************************************************
*                      Functions Definitions                                   *
*******************************************************************************/

void SPI_initMaster(void)
{
	GPIO_setupPinDirection(PORTB_ID, PIN4_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(PORTB_ID, PIN5_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(PORTB_ID, PIN6_ID, PIN_INPUT);
	GPIO_setupPinDirection(PORTB_ID, PIN7_ID, PIN_OUTPUT);

	SPCR = (1<<SPE) | (1<<MSTR);

	SPSR &= ~(1<<SPI2X);
}

void SPI_initSlave(void)
{
	GPIO_setupPinDirection(PORTB_ID, PIN4_ID, PIN_INPUT);
	GPIO_setupPinDirection(PORTB_ID, PIN5_ID, PIN_INPUT);
	GPIO_setupPinDirection(PORTB_ID, PIN6_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(PORTB_ID, PIN7_ID, PIN_INPUT);

	SPCR = (1<<SPE) ;

	SPSR &= ~(1<<SPI2X);
}

uint8 SPI_sendReceiveByte(uint8 data)
{
	SPDR = data;

	while(BIT_IS_CLEAR(SPSR,SPIF)){}

	return SPDR;
}

void SPI_sendString(const uint8 *str)
{
	uint8 i = 0;
	uint8 received_data = 0;

	/* Send the whole string */
	while(str[i] != '\0')
	{
		/*
		 * received_data contains the received data from the other device.
		 * It is a dummy data variable as we just need to send the string to other device.
		 */
		received_data = SPI_sendReceiveByte(str[i]);
		i++;
	}
}

void SPI_receiveString(uint8 *str)
{
	uint8 i = 0;
	/* as 0xFF considered as garbage value is sent to just receive the string */
	str[i] = SPI_sendReceiveByte(SPI_DEFAULT_DATA_VALUE);

	while(str[i] != g_endStringChar)
	{
		i++;
		str[i] = SPI_sendReceiveByte(SPI_DEFAULT_DATA_VALUE);
	}
	str[i] = '\0' ;
}

void SPI_setEndStringChar(uint8 symbol)
{
	g_endStringChar = symbol ;
}
