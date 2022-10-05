/******************************************************************************
*  File name:		motor.h
*  Author:			Oct 5, 2022
*  Author:			Ahmed Tarek
*******************************************************************************/

#ifndef MOTOR_H_
#define MOTOR_H_

/*******************************************************************************
*                        		Inclusions                                     *
*******************************************************************************/

#include "../../LIB/std_types.h"

/*******************************************************************************
*                        		Definitions                                    *
*******************************************************************************/

#define DCMOTOR_PORT_ID			PORTB_ID
#define	DCMOTOR_PIN_IN1			PIN0_ID
#define	DCMOTOR_PIN_IN2			PIN1_ID
#define	DCMOTOR_PIN_E			PIN3_ID

/*******************************************************************************
*                         Types Declaration                                   *
*******************************************************************************/

/*******************************************************************************
* Name: DcMotor_State
* Type: Enumeration
* Description: Data type to represent the different states of the motor
********************************************************************************/

typedef enum
{
	DcMotor_STOP,
	DcMotor_CW,
	DcMotor_CCW
}DcMotor_State;

/*******************************************************************************
*                      Functions Prototypes                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		DcMotor_Init
* Description:			Function to initialize the motor
* Parameters (in):    	None
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

void DcMotor_Init(void);

/*******************************************************************************
* Function Name:		DcMotor_Rotate
* Description:			Function to control the motor direction and its speed
* Parameters (in):    	Required direction and speed
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

void DcMotor_Rotate(DcMotor_State state,uint8 speed);

#endif /* MOTOR_H_ */
