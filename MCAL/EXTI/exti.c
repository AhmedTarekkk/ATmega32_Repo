/******************************************************************************
*  File name:		exti.c
*  Author:			Oct 28, 2022
*  Author:			Ahmed Tarek
*******************************************************************************/

/*******************************************************************************
*                        		Inclusions                                     *
*******************************************************************************/

#include "exti.h"
#include "avr/io.h"
#include "../../LIB/common_macros.h"
#include "../../MCAL/GPIO/gpio.h"
#include "avr/interrupt.h"

/*******************************************************************************
*                           Global Variables                                  *
*******************************************************************************/

static volatile void (*g_callBackPtr1)(void) = NULL_PTR; /* to store the address of the function */
static volatile void (*g_callBackPtr2)(void) = NULL_PTR; /* to store the address of the function */
static volatile void (*g_callBackPtr3)(void) = NULL_PTR; /* to store the address of the function */

/*******************************************************************************
*                      Functions Definitions                                   *
*******************************************************************************/

ISR(INT0_vect)
{
	if(g_callBackPtr1 != NULL_PTR)
	{
		(*g_callBackPtr1)();
	}
}

ISR(INT1_vect)
{
	if(g_callBackPtr2 != NULL_PTR)
	{
		(*g_callBackPtr2)();
	}
}

ISR(INT2_vect)
{
	if(g_callBackPtr3 != NULL_PTR)
	{
		(*g_callBackPtr3)();
	}
}

void EXTI_init(EXTI_ConfigType * Config_Ptr)
{
	switch(Config_Ptr->INT)
	{
	case EXTI_0:
		GPIO_setupPinDirection(PORTD_ID, PIN2_ID, PIN_INPUT); /* INT0 Input pin */
		switch(Config_Ptr->Level)
		{
		case LOW_LEVEL:
			CLEAR_BIT(MCUCR,ISC00);
			CLEAR_BIT(MCUCR,ISC01);
			break;
		case LOGICAL_CHANGE:
			SET_BIT(MCUCR,ISC00);
			CLEAR_BIT(MCUCR,ISC01);
			break;
		case FALLING_EDGE:
			CLEAR_BIT(MCUCR,ISC00);
			SET_BIT(MCUCR,ISC01);
			break;
		case RISING_EDGE:
			SET_BIT(MCUCR,ISC00);
			SET_BIT(MCUCR,ISC01);
			break;
		}
		SET_BIT(GICR,INT0); /* INT0 Enable */
		break;
	case EXTI_1:
		GPIO_setupPinDirection(PORTD_ID, PIN3_ID, PIN_INPUT); /* INT1 Input Pin */
		switch(Config_Ptr->Level)
		{
		case LOW_LEVEL:
			CLEAR_BIT(MCUCR,ISC10);
			CLEAR_BIT(MCUCR,ISC11);
			break;
		case LOGICAL_CHANGE:
			SET_BIT(MCUCR,ISC10);
			CLEAR_BIT(MCUCR,ISC11);
			break;
		case FALLING_EDGE:
			CLEAR_BIT(MCUCR,ISC10);
			SET_BIT(MCUCR,ISC11);
			break;
		case RISING_EDGE:
			SET_BIT(MCUCR,ISC10);
			SET_BIT(MCUCR,ISC11);
			break;
		}
		SET_BIT(GICR,INT1); /* INT1 Enable */
		break;
	case EXTI_2:
		GPIO_setupPinDirection(PORTB_ID, PIN2_ID, PIN_INPUT);  /* INT2 Input Pin */
		switch(Config_Ptr->Level)
		{
		default: /* Make default to be falling edge in case the user input invalid Trigger for EXTI 2 */
		case FALLING_EDGE:
			CLEAR_BIT(MCUCSR,ISC2);
			break;
		case RISING_EDGE:
			SET_BIT(MCUCSR,ISC2);
			break;
		}
		SET_BIT(GICR,INT2); /* INT2 Enable */
		break;
	}
}

void EXTI_0_setCallBack( void(*a_ptr)(void) )
{
	g_callBackPtr1 = a_ptr;
}

void EXTI_1_setCallBack( void(*a_ptr)(void) )
{
	g_callBackPtr2 = a_ptr;
}

void EXTI_2_setCallBack( void(*a_ptr)(void) )
{
	g_callBackPtr3 = a_ptr;
}
