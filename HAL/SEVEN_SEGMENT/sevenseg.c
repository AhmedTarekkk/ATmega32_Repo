/******************************************************************************
*  File name:		sevenseg.c
*  Author:			Oct 10, 2022
*  Author:			Ahmed Tarek
*******************************************************************************/

/*******************************************************************************
*                        		Inclusions                                     *
*******************************************************************************/

#include "sevenseg.h"
#include "../../MCAL/GPIO/gpio.h"
#include "../../LIB/common_macros.h"
#include "avr/io.h"

/*******************************************************************************
*                      Functions Prototypes(Private)                          *
*******************************************************************************/

#if (SEVEN_SEGMENT_DECODER == WITHOUT_BCD_DECODER)

#if (SEVEN_SEGMENT_TYPE == CATHODE)

static void SEVEN_SEGMENT_CATHODE(uint8 number);

#elif (SEVEN_SEGMENT_TYPE == ANODE)

static void SEVEN_SEGMENT_ANODE(uint8 number);

#endif


/* so we can write in the port directly  */
#if (SEVEN_SEGMENT_PORT_ID == PORTA_ID)
#define MYPORT	PORTA

#elif (SEVEN_SEGMENT_PORT_ID == PORTB_ID)
#define MYPORT	PORTB

#elif (SEVEN_SEGMENT_PORT_ID == PORTB_ID)
#define MYPORT	PORTC

#elif (SEVEN_SEGMENT_PORT_ID == PORTB_ID)
#define MYPORT	PORTD

#endif

#endif

/*******************************************************************************
*                      Functions Definitions                                  *
*******************************************************************************/

void SEVEN_SEGMENT_init(void)
{
	/* Enable bit is output */
	GPIO_setupPinDirection(SEVEN_SEGMENT_E_PORT_ID, SEVEN_SEGMENT_E_PIN_ID, PIN_OUTPUT);

	/* Seven segment pins is output */
	for(uint8 counter = 0 ; counter < SEVEN_SEGMENT_DECODER ; counter++)
	{
		GPIO_setupPinDirection(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_FIRST_PIN_ID+counter, PIN_OUTPUT);
	}
}

void SEVEN_SEGMENT_enable(void)
{
	#if (SEVEN_SEGMENT_TYPE == ANODE)
		GPIO_writePin(SEVEN_SEGMENT_E_PORT_ID, SEVEN_SEGMENT_E_PIN_ID, LOGIC_HIGH);
	#elif (SEVEN_SEGMENT_TYPE == CATHODE)
		GPIO_writePin(SEVEN_SEGMENT_E_PORT_ID, SEVEN_SEGMENT_E_PIN_ID, LOGIC_LOW);
	#endif
}

void SEVEN_SEGMENT_disable(void)
{
	#if (SEVEN_SEGMENT_TYPE == ANODE)
		GPIO_writePin(SEVEN_SEGMENT_E_PORT_ID, SEVEN_SEGMENT_E_PIN_ID, LOGIC_LOW);
	#elif (SEVEN_SEGMENT_TYPE == CATHODE)
		GPIO_writePin(SEVEN_SEGMENT_E_PORT_ID, SEVEN_SEGMENT_E_PIN_ID, LOGIC_HIGH);
	#endif
}

void SEVEN_SEGMENT_displayNumber(uint8 number)
{
	/* in case that we are using decoder */
	#if (SEVEN_SEGMENT_DECODER == WITH_BCD_DECODER)

	for(uint8 i = 0 ; i < SEVEN_SEGMENT_DECODER ; i++)
	{
		/* Clear the bit first then insert the new bit value */
		GPIO_writePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_FIRST_PIN_ID+i, LOGIC_LOW);
		GPIO_writePin(SEVEN_SEGMENT_PORT_ID, SEVEN_SEGMENT_FIRST_PIN_ID+i, GET_BIT(number,i));
	}

	/* in case that we don't use decoder */
	#elif (SEVEN_SEGMENT_DECODER == WITHOUT_BCD_DECODER)

		/* No decoder --> Anode 7 Segment */
		#if (SEVEN_SEGMENT_TYPE == ANODE)
			SEVEN_SEGMENT_ANODE(number);

		/* No decoder --> Cathode 7 Segment */
		#elif (SEVEN_SEGMENT_TYPE == CATHODE)
			SEVEN_SEGMENT_CATHODE(number);

		#endif /* ANODE or CATHODE condition */

	#endif /* With Decoder or Without condition */
}

#if (SEVEN_SEGMENT_DECODER == WITHOUT_BCD_DECODER)

#if (SEVEN_SEGMENT_TYPE == CATHODE)

static void SEVEN_SEGMENT_CATHODE(uint8 number)
{

	switch(number)
	{
	case 0:
		MYPORT |= (1<<SEVEN_SEGMENT_FIRST_PIN_ID);
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+1));
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+2));
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+3));
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+4));
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+5));
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+6));
		break;
	case 1:
		MYPORT &= ~(1<<SEVEN_SEGMENT_FIRST_PIN_ID);
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+1));
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+2));
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+3));
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+4));
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+5));
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+6));
		break;
	case 2:
		MYPORT |= (1<<SEVEN_SEGMENT_FIRST_PIN_ID);
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+1));
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+2));
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+3));
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+4));
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+5));
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+6));
		break;
	case 3:
		MYPORT |= (1<<SEVEN_SEGMENT_FIRST_PIN_ID);
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+1));
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+2));
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+3));
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+4));
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+5));
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+6));
		break;
	case 4:
		MYPORT &= ~(1<<SEVEN_SEGMENT_FIRST_PIN_ID);
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+1));
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+2));
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+3));
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+4));
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+5));
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+6));
		break;
	case 5:
		MYPORT |= (1<<SEVEN_SEGMENT_FIRST_PIN_ID);
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+1));
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+2));
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+3));
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+4));
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+5));
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+6));
		break;
	case 6:
		MYPORT |= (1<<SEVEN_SEGMENT_FIRST_PIN_ID);
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+1));
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+2));
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+3));
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+4));
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+5));
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+6));
		break;
	case 7:
		MYPORT |= (1<<SEVEN_SEGMENT_FIRST_PIN_ID);
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+1));
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+2));
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+3));
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+4));
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+5));
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+6));
		break;
	case 8:
		MYPORT |= (1<<SEVEN_SEGMENT_FIRST_PIN_ID);
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+1));
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+2));
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+3));
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+4));
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+5));
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+6));
		break;
	case 9:
		MYPORT |= (1<<SEVEN_SEGMENT_FIRST_PIN_ID);
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+1));
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+2));
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+3));
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+4));
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+5));
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+6));
		break;
	}
}

#elif (SEVEN_SEGMENT_TYPE == ANODE)

static void SEVEN_SEGMENT_ANODE(uint8 number)
{

	switch(number)
	{
	case 0:
		MYPORT &= ~(1<<SEVEN_SEGMENT_FIRST_PIN_ID);
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+1));
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+2));
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+3));
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+4));
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+5));
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+6));
		break;
	case 1:
		MYPORT |= (1<<SEVEN_SEGMENT_FIRST_PIN_ID);
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+1));
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+2));
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+3));
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+4));
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+5));
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+6));
		break;
	case 2:
		MYPORT &= ~(1<<SEVEN_SEGMENT_FIRST_PIN_ID);
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+1));
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+2));
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+3));
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+4));
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+5));
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+6));
		break;
	case 3:
		MYPORT &= ~(1<<SEVEN_SEGMENT_FIRST_PIN_ID);
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+1));
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+2));
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+3));
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+4));
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+5));
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+6));
		break;
	case 4:
		MYPORT |= (1<<SEVEN_SEGMENT_FIRST_PIN_ID);
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+1));
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+2));
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+3));
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+4));
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+5));
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+6));
		break;
	case 5:
		MYPORT &= ~(1<<SEVEN_SEGMENT_FIRST_PIN_ID);
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+1));
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+2));
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+3));
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+4));
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+5));
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+6));
		break;
	case 6:
		MYPORT &= ~(1<<SEVEN_SEGMENT_FIRST_PIN_ID);
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+1));
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+2));
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+3));
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+4));
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+5));
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+6));
		break;
	case 7:
		MYPORT &= ~(1<<SEVEN_SEGMENT_FIRST_PIN_ID);
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+1));
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+2));
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+3));
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+4));
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+5));
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+6));
		break;
	case 8:
		MYPORT &= ~(1<<SEVEN_SEGMENT_FIRST_PIN_ID);
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+1));
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+2));
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+3));
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+4));
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+5));
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+6));
		break;
	case 9:
		MYPORT &= ~(1<<SEVEN_SEGMENT_FIRST_PIN_ID);
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+1));
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+2));
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+3));
		MYPORT |= (1<<(SEVEN_SEGMENT_FIRST_PIN_ID+4));
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+5));
		MYPORT &= ~(1<<(SEVEN_SEGMENT_FIRST_PIN_ID+6));
		break;
	}
}

#endif

#endif
