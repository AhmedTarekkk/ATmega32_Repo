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
#include "avr/interrupt.h"

/*******************************************************************************
*                           Global Variables                                  *
*******************************************************************************/

static uint8 g_endStringChar; /* to store the special char to end sting at */
static volatile void (*g_callBackPtr)(void) = NULL_PTR; /* to store the address of the function */

/*******************************************************************************
*                       Interrupt Service Routines                            *
*******************************************************************************/

ISR(USART_RXC_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}
}
/*
 * if you want to receive string a_ptr can be:
 *
	uint8 String[20]; // Global variable to store the char received
	uint8 row = 0; // so we can

	void a_ptr(void)
	{
		static uint8 counter ;
		String[counter] = UDR;
		if(String[counter] == UART_configuration1 -> END_STRING)
		{
			String[counter] = '\0';
			LCD_displayStringRowColumn(row, 0, String); // display the string in LCD
			counter = 0 ; // to receive new string in the same buffer
			row++; //to display the next string the next row in the LCD screen
		}
		else
		{
			counter++;
		}
	}

 */

/*******************************************************************************
*                      Functions Definitions                                   *
*******************************************************************************/

void UART_init(const UART_ConfigType * Configptr)
{
	uint16 ubrr_value ;
	UCSRA = (1<<U2X); /* Double transmission speed */
	UCSRB = (1<<RXEN) | (1<<TXEN) ;	/* Transmission and receive enable */
	UCSRB = (UCSRB & CLEAR_RECEIVE_METHOD_MASK ) | ( (Configptr->RECEVIE_METHOD<<7) ) ; /* To configure the UART with interrupt or polling */

	SET_BIT(UCSRC,URSEL); /* so we can write in UCSRC register */
	UCSRC = (UCSRC & CLEAR_CHAR_SIZE_MASK ) | ( (Configptr->CHAR_SIZE)<<1) ; /* setting the number of bits in UART frame */
	UCSRC = (UCSRC & CLEAR_STOP_BITS_MASK) | ( (Configptr->STOP_BIT)<<3) ; /* set the number of stop bits */
	UCSRC = (UCSRC & CLEAR_PARITY_MASK ) | ( (Configptr->PARITY)<<4) ; /* setting the PARITY */

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

	/* Receive the first byte */
	Str[i] = UART_receiveByte();

	/* Receive the whole string until the '#' */
	while(Str[i] != g_endStringChar)
	{
		i++;
		Str[i] = UART_receiveByte();
	}

	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	Str[i] = '\0';

}

void UART_setCallBack( void(*a_ptr)(void) )
{
	g_callBackPtr = a_ptr;
}
