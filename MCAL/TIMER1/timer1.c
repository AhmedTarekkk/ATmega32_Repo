/******************************************************************************
*  File name:		timer1.c
*  Author:			Oct 26, 2022
*  Author:			Ahmed Tarek
*******************************************************************************/

/*******************************************************************************
*                        		Inclusions                                     *
*******************************************************************************/
#include "timer1.h"
#include "avr/interrupt.h"
#include "avr/io.h"
#include "../../LIB/common_macros.h"

/*******************************************************************************
*                           Global Variables                                  *
*******************************************************************************/
static volatile void (*g_callBackPtr1)(void) = NULL_PTR; /* to store the address of the function */
static volatile void (*g_callBackPtr2)(void) = NULL_PTR; /* to store the address of the function */

/*******************************************************************************
*                      Functions Definitions                                   *
*******************************************************************************/
ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr1 != NULL_PTR)
	{
		(*g_callBackPtr1)();
	}
}

ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr2 != NULL_PTR)
	{
		(*g_callBackPtr2)();
	}
}

void TIMER1_init(Timer1_ConfigType * Config_Ptr)
{
	TCCR1A = (1<<FOC1A) | (1<<FOC1B);
	TCCR1B = (Config_Ptr->mode << WGM12);
	TCCR1B = (TCCR1B & 0xF8) | (Config_Ptr->prescaler);

	TCNT1 = Config_Ptr->initial_value;
	if(Config_Ptr->mode == COMPARE)
	{
		OCR1A = Config_Ptr->compare_value;
	}
	TIMSK |= (1<<OCIE1A) ;
}

void TIMER1_deInit()
{
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	OCR1A = 0;
}

/*******************************************************************************
* Function Name:		Timer1_Delay_us
********************************************************************************/

void Timer1_Delay_us(uint16 time)
{
	TCNT1 = 0;
	TCCR1A = (1<<FOC1A) | (1<<FOC1B);
	TCCR1B = (1<<WGM12) | (1<<CS11) ;
	OCR1A = time/2;
	while(BIT_IS_CLEAR(TIFR,OCF1A)){}
	TIFR |= (1<<OCF1A);
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	OCR1A = 0;
}

/*******************************************************************************
* Function Name:		Timer1_Delay_ms
********************************************************************************/

void Timer1_Delay_ms(uint16 time)
{
	uint16 count = 0;
	while(count < time)
	{
		Timer1_Delay_us(1000); /* wait 1000 us seconds */
		count++; /* then increase count by 1 */
	}
}


void TIMER1_COMP_setCallBack( void(*a_ptr)(void) )
{
	g_callBackPtr1 = a_ptr;
}

void TIMER1_OVF_setCallBack( void(*a_ptr)(void) )
{
	g_callBackPtr2 = a_ptr;
}
