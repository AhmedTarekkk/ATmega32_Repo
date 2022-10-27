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

void TIMER1_COMP_setCallBack( void(*a_ptr)(void) )
{
	g_callBackPtr1 = a_ptr;
}

void TIMER1_OVF_setCallBack( void(*a_ptr)(void) )
{
	g_callBackPtr2 = a_ptr;
}
