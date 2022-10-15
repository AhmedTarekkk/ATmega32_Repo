/******************************************************************************
*  File name:		icu.c
*  Author:			Oct 5, 2022
*  Author:			Ahmed Tarek
*******************************************************************************/

/*******************************************************************************
*                        		Inclusions                                     *
*******************************************************************************/

#include "icu.h"
#include "../../MCAL/GPIO/gpio.h"
#include "avr/io.h"
#include "avr/interrupt.h"
#include "../../LIB/common_macros.h"

/*******************************************************************************
*                           Global Variables                                  *
*******************************************************************************/

static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
*                       Interrupt Service Routines                            *
*******************************************************************************/

ISR(TIMER1_CAPT_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

/*******************************************************************************
*                      Functions Definitions                                   *
*******************************************************************************/

void ICU_init(const ICU_ConfigType * Config_Ptr)
{
	GPIO_setupPinDirection(PORTD_ID, PIN6_ID, PIN_INPUT);

	TCCR1A = (1<<FOC1A) | (1<<FOC1B);
	TCCR1B = (TCCR1B & 0xF8) | (Config_Ptr->clock);
	TCCR1B = (TCCR1B & 0xBF) | ((Config_Ptr->edge)<<6);
	TCNT1 = 0;
	ICR1 = 0;
	SET_BIT(TIMSK,TICIE1);
}

void ICU_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr;
}

void ICU_setEdgeDetectionType(const ICU_EdgeType a_edgeType)
{
	TCCR1B = (TCCR1B & 0xBF) | ((a_edgeType)<<6);
}

uint16 ICU_getInputCaptureValue(void)
{
	return ICR1;
}

void ICU_clearTimerValue(void)
{
	TCNT1 = 0;
}

void ICU_DeInit(void)
{
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	ICR1 = 0;

	CLEAR_BIT(TIMSK,TICIE1);
}
