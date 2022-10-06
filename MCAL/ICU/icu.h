/******************************************************************************
*  File name:		icu.h
*  Author:			Oct 5, 2022
*  Author:			Ahmed Tarek
*******************************************************************************/

#ifndef ICU_H_
#define ICU_H_

/*******************************************************************************
*                        		Inclusions                                     *
*******************************************************************************/

#include "../../LIB/std_types.h"


/*******************************************************************************
*                         Types Declaration                                   *
*******************************************************************************/

/*******************************************************************************
* Name: ICU_Clock
* Type: Enumeration
* Description: Data type to represent the Timer1 prescaler
********************************************************************************/

typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}ICU_Clock;

/*******************************************************************************
* Name: ICU_EdgeType
* Type: Enumeration
* Description: Data type to represent the Edge Type
********************************************************************************/

typedef enum
{
	FALLING,RISING
}ICU_EdgeType;

/*******************************************************************************
* Name: ICU_ConfigType
* Type: Structure
* Description: Data type to dynamic configure the ICU module
********************************************************************************/

typedef struct
{
	ICU_Clock clock;
	ICU_EdgeType edge;
}ICU_ConfigType;

/*******************************************************************************
*                      Functions Prototypes                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		ICU_init
* Description:			Function to initialize the ICU module
* Parameters (in):    	Pointer to structure of type ICU_ConfigType
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/
void ICU_init(const ICU_ConfigType * Config_Ptr);

/*******************************************************************************
* Function Name:		ICU_setCallBack
* Description:			Function to set the Call Back function address.
* Parameters (in):    	Pointer to function
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

void ICU_setCallBack(void(*a_ptr)(void));

/*******************************************************************************
* Function Name:		ICU_setEdgeDetectionType
* Description:			Function to set the required edge detection.
* Parameters (in):    	Required Edge
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

void ICU_setEdgeDetectionType(const ICU_EdgeType a_edgeType);

/*******************************************************************************
* Function Name:		ICU_getInputCaptureValue
* Description:			Function to get the Timer1 Value when the input is captured
 *              		The value stored at Input Capture Register ICR1.
* Parameters (in):    	None
* Parameters (out):   	ICR1
* Return value:      	uint16
********************************************************************************/

uint16 ICU_getInputCaptureValue(void);

/*******************************************************************************
* Function Name:		ICU_clearTimerValue
* Description:			Function to clear the Timer1 Value to start count from ZERO.
* Parameters (in):    	None
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

void ICU_clearTimerValue(void);

/*******************************************************************************
* Function Name:		ICU_DeInit
* Description:			Function to disable the Timer1 to stop the ICU Driver.
* Parameters (in):    	Required Edge
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

void ICU_DeInit(void);

#endif /* ICU_H_ */
