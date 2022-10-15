/******************************************************************************
*  File name:		ultrasonic.h
*  Author:			Oct 15, 2022
*  Author:			Ahmed Tarek
*******************************************************************************/

#ifndef HAL_ULTRASONIC_ULTRASONIC_H_
#define HAL_ULTRASONIC_ULTRASONIC_H_

/*******************************************************************************
*                        		Inclusions                                     *
*******************************************************************************/

#include "../../LIB/std_types.h"

/*******************************************************************************
*                        		Definitions                                    *
*******************************************************************************/

#define ULTRASONIC_TR_PORT_ID			PORTB_ID
#define ULTRASONIC_TR_PIN_ID			PIN5_ID

#define ULTRASONIC_EKKO_PORT_ID			PORTD_ID
#define ULTRASONIC_EKKO_PIN_ID			PIN6_ID

/*******************************************************************************
*                      Functions Prototypes                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		ULTRASONIC_init
* Description:			Function to initialize the ULTRASONIC device and its pins
* Parameters (in):    	None
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

void ULTRASONIC_init(void);

/*******************************************************************************
* Function Name:		ULTRASONIC_Trigger
* Description:			Function to trigger the ULTRASONIC device to start measuring
* Parameters (in):    	None
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

void ULTRASONIC_Trigger(void);

/*******************************************************************************
* Function Name:		ULTRASONIC_readDistance
* Description:			Function to calculate the distance from the high time of the edge
* Parameters (in):    	None
* Parameters (out):   	distance value
* Return value:      	uint16
********************************************************************************/

uint16 ULTRASONIC_readDistance(void);

/*******************************************************************************
* Function Name:		ULTRASONIC_edgeProcessing
* Description:			Call back function for the ICU interrupt to calculate high time for the edge
* Parameters (in):    	None
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

void ULTRASONIC_edgeProcessing(void);

#endif /* HAL_ULTRASONIC_ULTRASONIC_H_ */
