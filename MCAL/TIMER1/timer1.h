/******************************************************************************
*  File name:		timer1.c
*  Author:			Oct 26, 2022
*  Author:			Ahmed Tarek
*******************************************************************************/

#ifndef MCAL_TIMER1_TIMER1_H_
#define MCAL_TIMER1_TIMER1_H_

/*******************************************************************************
*                        		Inclusions                                     *
*******************************************************************************/
#include "../../LIB/std_types.h"

/*******************************************************************************
*                         Types Declaration                                   *
*******************************************************************************/

/*******************************************************************************
* Name: Timer1_Mode
* Type: Enumeration
* Description: Data type to represent the timer mode
********************************************************************************/
typedef enum
{
	NORMAL,
	COMPARE
}Timer1_Mode;

/*******************************************************************************
* Name: Timer1_Prescaler
* Type: Enumeration
* Description: Data type to represent the timer prescaler
********************************************************************************/
typedef enum
{
	TIMER1_OFF,
	TIMER1_FCPU_1,
	TIMER1_FCPU_8,
	TIMER1_FCPU_64,
	TIMER1_FCPU_256,
	TIMER1_FCPU_1024
}Timer1_Prescaler;

/*******************************************************************************
* Name: Timer1_ConfigType
* Type: Structure
* Description: Data type to dynamic configure the timer module
********************************************************************************/
typedef struct {
 uint16 initial_value;
 uint16 compare_value; // it will be used in compare mode only.
 Timer1_Prescaler prescaler;
 Timer1_Mode mode;
} Timer1_ConfigType;

/*******************************************************************************
*                      Functions Prototypes                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		TIMER1_init
* Description:			Function to dynamic configure the timer module
* Parameters (in):    	Pointer to structure of type Timer1_ConfigType
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/
void TIMER1_init(Timer1_ConfigType * Config_Ptr);

/*******************************************************************************
* Function Name:		TIMER1_deInit
* Description:			Function to de-initialize the timer module and stop it
* Parameters (in):    	None
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/
void TIMER1_deInit();

/*******************************************************************************
* Function Name:		TIMER1_COMP_setCallBack
* Description:			Function to set the ISR for timer in case using compare mode
* Parameters (in):    	Pointer to function to be the ISR
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/
void TIMER1_COMP_setCallBack( void(*a_ptr)(void) );

/*******************************************************************************
* Function Name:		TIMER1_OVF_setCallBack
* Description:			Function to set the ISR for timer in case using overflow mode
* Parameters (in):    	Pointer to function to be the ISR
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/
void TIMER1_OVF_setCallBack( void(*a_ptr)(void) );

#endif /* MCAL_TIMER1_TIMER1_H_ */
