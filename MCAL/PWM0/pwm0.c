/******************************************************************************
*  File name:		pwm0.c
*  Author:			Oct 5, 2022
*  Author:			Ahmed Tarek
*******************************************************************************/

/*******************************************************************************
*                        		Inclusions                                     *
*******************************************************************************/

#include "pwm0.h"
#include "avr/io.h"
#include "../GPIO/gpio.h"

void PWM_Timer0_Start(uint8 duty_cycle)
{
	/* Configure the timer with
	 * Non inverting fast PWM Mode
	 * Clock frequency = F_CPU/8
	 */
	TCNT0 = 0;
	OCR0 = (uint8)((uint16)(duty_cycle*255)/100) ; /* casting the value so we don't get overflow */
	GPIO_setupPinDirection(PORTB_ID, PIN3_ID, PIN_OUTPUT); /* PWM pin as O/P */
	TCCR0 = (1<<WGM01) | (1<<WGM00) | (1<<COM01) | (1<<CS01);

}
