/******************************************************************************
*  File name:		motor.c
*  Author:			Oct 5, 2022
*  Author:			Ahmed Tarek
*******************************************************************************/

/*******************************************************************************
*                        		Inclusions                                     *
*******************************************************************************/

#include "motor.h"
#include "../../MCAL/GPIO/gpio.h"
#include "../../LIB/common_macros.h"
#include "../../MCAL/PWM0/pwm0.h"


void DcMotor_Init(void)
{
	/* setting the direction of the motor pins */
	GPIO_setupPinDirection(DCMOTOR_PORT_ID, DCMOTOR_PIN_IN1, PIN_OUTPUT); /* Input1 */
	GPIO_setupPinDirection(DCMOTOR_PORT_ID, DCMOTOR_PIN_IN2, PIN_OUTPUT); /* Inupt2 */

	/* Stop the motor */
	GPIO_writePin(DCMOTOR_PORT_ID, DCMOTOR_PIN_IN1, LOGIC_LOW);
	GPIO_writePin(DCMOTOR_PORT_ID, DCMOTOR_PIN_IN2, LOGIC_LOW);
}

void DcMotor_Rotate(DcMotor_State state,uint8 speed)
{
	/* clearing the motor so we can change it state */
	GPIO_writePin(DCMOTOR_PORT_ID, DCMOTOR_PIN_IN1, LOGIC_LOW);
	GPIO_writePin(DCMOTOR_PORT_ID, DCMOTOR_PIN_IN2, LOGIC_LOW);

	GPIO_writePin(DCMOTOR_PORT_ID, DCMOTOR_PIN_IN1, GET_BIT(state,0));
	GPIO_writePin(DCMOTOR_PORT_ID, DCMOTOR_PIN_IN2, GET_BIT(state,1));

	PWM_Timer0_Start(speed);
}
