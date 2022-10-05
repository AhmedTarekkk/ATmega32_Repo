/******************************************************************************
*  File name:		pwm.h
*  Author:			Oct 5, 2022
*  Author:			Ahmed Tarek
*******************************************************************************/

#ifndef PWM0_PWM0_H_
#define PWM0_PWM0_H_

/*******************************************************************************
*                        		Inclusions                                     *
*******************************************************************************/

#include "../../LIB/std_types.h"

/*******************************************************************************
*                      Functions Prototypes                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		PWM_Timer0_Start
* Description:			Function to control the PWM with timer 0 and set the duty cycle
* Parameters (in):    	The required duty cycle for the PWM
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

void PWM_Timer0_Start(uint8 duty_cycle);


#endif /* PWM0_PWM0_H_ */
