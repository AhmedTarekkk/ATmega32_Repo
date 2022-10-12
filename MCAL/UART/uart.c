/******************************************************************************
*  File name:		uart.h
*  Author:			Oct 12, 2022
*  Author:			Ahmed Tarek
*******************************************************************************/

/*******************************************************************************
*                        		Inclusions                                     *
*******************************************************************************/

#include "uart.h"
#include "avr/io.h"
#include "../../LIB/common_macros.h"

/*******************************************************************************
*                           Global Variables                                  *
*******************************************************************************/

static uint8 g_endStringChar; /* to store the special char to end sting at */

/*******************************************************************************
*                      Functions Definitions                                   *
*******************************************************************************/

void UART_init(const UART_ConfigType * Configptr)
{
	uint16 ubrr_value ;
	UCSRA = (1<<U2X); /* Double transmission speed */
	UCSRB = (1<<RXEN) | (1<<TXEN) ;	/* Transmission and receive enable */

	SET_BIT(UCSRC,URSEL); /* so we can write in UCSRC register */
	UCSRC = (UCSRC & CLEAR_CHAR_SIZE_MASK ) | ( (Configptr->CHAR_SIZE) ) ; /* setting the number of bits in UART frame */
	UCSRC = (UCSRC & CLEAR_STOP_BITS_MASK) | ( (Configptr->STOP_BIT)<<3 ) ; /* set the number of stop bits */
	UCSRC = (UCSRC & CLEAR_PARITY_MASK ) | ( (Configptr->parity)<<4 ) ; /* setting the parity */

	CLEAR_BIT(UBRRH,URSEL); /* to access UBRRH not UCSRC */
	ubrr_value = (uint16)(((F_CPU / (Configptr->BAUD_RATE * 8UL))) - 1);
	UBRRH = ubrr_value>>8;
	UBRRL = ubrr_value;

	g_endStringChar = Configptr->END_SRTING;
}

void UART_sendByte(const uint8 data)
{
	while(BIT_IS_CLEAR(UCSRA,UDRE)){}

	UDR = data;
}

uint8 UART_receiveByte()
{
	while(BIT_IS_CLEAR(UCSRA,RXC)){}

	return UDR;
}

void UART_sendString(const uint8 *Str)
{
	uint8 i ;
	for(i = 0 ; Str[i] != '\0' ; i++)
	{
		UART_sendByte(Str[i]);
	}
}

void UART_receiveString(uint8 *Str)
{
	uint8 i = 0;

	do
	{
		Str[i] = UART_receiveByte();
	}while(Str[i] != g_endStringChar);

	Str[i] = '\0';

}
