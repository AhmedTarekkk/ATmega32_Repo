/******************************************************************************
*  File name:		keypad.h
*  Author:			Oct 10, 2022
*  Author:			Ahmed Tarek
*******************************************************************************/

#ifndef HAL_KEYPAD_KEYPAD_H_
#define HAL_KEYPAD_KEYPAD_H_

/*******************************************************************************
*                        		Inclusions                                     *
*******************************************************************************/

#include "../../LIB/std_types.h"

/*******************************************************************************
*                        		Definitions                                    *
*******************************************************************************/

#define STANDARD_KEYPAD				FALSE

#define KEYPAD_NUM_COLS				4
#define	KEYPAD_NUM_ROWS				4

#define	KEYPAD_ROW_PORT_ID			PORTB_ID
#define	KEYPAD_FIRST_ROW_PIN_ID		PIN0_ID

#define	KEYPAD_COL_PORT_ID			PORTB_ID
#define	KEYPAD_FIRST_COL_PIN_ID		PIN4_ID

#define KEYPAD_BUTTON_PRESSED            LOGIC_LOW
#define KEYPAD_BUTTON_RELEASED           LOGIC_HIGH

/*******************************************************************************
*                      Functions Prototypes                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		KEYPAD_getPressedKey
* Description:			Get the Keypad pressed button
* Parameters (in):    	None
* Parameters (out):   	The pressed key on the keypad
* Return value:      	uint8
********************************************************************************/

uint8 KEYPAD_getPressedKey();

#endif /* HAL_KEYPAD_KEYPAD_H_ */
