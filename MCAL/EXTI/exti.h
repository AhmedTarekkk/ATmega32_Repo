/******************************************************************************
*  File name:		exti.h
*  Author:			Oct 28, 2022
*  Author:			Ahmed Tarek
*******************************************************************************/

#ifndef MCAL_EXTI_EXTI_H_
#define MCAL_EXTI_EXTI_H_

/*******************************************************************************
*                        		Inclusions                                     *
*******************************************************************************/

#include "../../LIB/std_types.h"

/*******************************************************************************
*                         Types Declaration                                   *
*******************************************************************************/

/*******************************************************************************
* Name: EXTI_LEVEL
* Type: Enumeration
* Description: Data type to represent the EXTI trigger methode
********************************************************************************/

typedef enum
{
	LOW_LEVEL,
	LOGICAL_CHANGE,
	FALLING_EDGE,
	RISING_EDGE
}EXTI_LEVEL;

/*******************************************************************************
* Name: EXTI_NUMBER
* Type: Enumeration
* Description: Data type to represent the 3 external interrupts
********************************************************************************/

typedef enum
{
	EXTI_0,
	EXTI_1,
	EXTI_2
}EXTI_NUMBER;

/*******************************************************************************
* Name: EXTI_ConfigType
* Type: Structure
* Description: Data type to dynamic configure the external interrupt
********************************************************************************/

typedef struct
{
	EXTI_NUMBER INT;
	EXTI_LEVEL Level;
}EXTI_ConfigType;


/*******************************************************************************
*                      Functions Prototypes                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		EXTI_init
* Description:			Function to dynamic configure the EXTI module
* Parameters (in):    	Pointer to structure of type EXTI_ConfigType
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

void EXTI_init(EXTI_ConfigType * Config_Ptr);

/*******************************************************************************
* Function Name:		EXTI_x_setCallBack
* Description:			Function to set ISR to the EXTI x
* Parameters (in):    	Pointer to function to be the ISR
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

void EXTI_0_setCallBack( void(*a_ptr)(void) );
void EXTI_1_setCallBack( void(*a_ptr)(void) );
void EXTI_2_setCallBack( void(*a_ptr)(void) );

#endif /* MCAL_EXTI_EXTI_H_ */
