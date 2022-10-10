/******************************************************************************
*  File name:		sevenseg.h
*  Author:			Oct 10, 2022
*  Author:			Ahmed Tarek
*******************************************************************************/

#ifndef HAL_SEVEN_SEGMENT_SEVENSEG_H_
#define HAL_SEVEN_SEGMENT_SEVENSEG_H_

/*******************************************************************************
*                        		Inclusions                                     *
*******************************************************************************/

#include "../../LIB/std_types.h"

/*******************************************************************************
*                        		Definitions                                    *
*******************************************************************************/

#define ANODE									0
#define CATHODE									1

/* Number of bits used by the seven segment in both cases using decoder or not */
#define WITH_BCD_DECODER						4
#define WITHOUT_BCD_DECODER						7

/* If we are using BCD number of bits will be 4 otherwise 7 */
#define SEVEN_SEGMENT_DECODER					WITHOUT_BCD_DECODER

/* First pin should be PIN0 or PIN1 as we consider they are on the same port */
#define SEVEN_SEGMENT_PORT_ID					PORTA_ID
#define SEVEN_SEGMENT_FIRST_PIN_ID				PIN1_ID

/* Enable bit can be in different port */
#define SEVEN_SEGMENT_E_PORT_ID					PORTC_ID
#define SEVEN_SEGMENT_E_PIN_ID					PIN6_ID

/* so we can select if the seven segment is common CATHODE or ANODE */
#define SEVEN_SEGMENT_TYPE						CATHODE


/*******************************************************************************
*                      Functions Prototypes                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		SEVEN_SEGMENT_INIT
* Description:			Function to initialize the seven segment
* Parameters (in):    	None
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

void SEVEN_SEGMENT_init(void);

/*******************************************************************************
* Function Name:		SEVEN_SEGMENT_INIT
* Description:			Function to enable the seven segment
* Parameters (in):    	None
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

void SEVEN_SEGMENT_enable(void);

/*******************************************************************************
* Function Name:		SEVEN_SEGMENT_INIT
* Description:			Function to disable the seven segment
* Parameters (in):    	None
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

void SEVEN_SEGMENT_disable(void);

/*******************************************************************************
* Function Name:		SEVEN_SEGMENT_displayNumber
* Description:			Function to display the number on the seven segment
* Parameters (in):    	number to be displayed
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

void SEVEN_SEGMENT_displayNumber(uint8 number);

#endif /* HAL_SEVEN_SEGMENT_SEVENSEG_H_ */
