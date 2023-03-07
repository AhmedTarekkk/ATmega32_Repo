/******************************************************************************
*  File name:		keypad.c
*  Author:			Oct 10, 2022
*  Author:			Ahmed Tarek
*******************************************************************************/

/*******************************************************************************
*                        		Inclusions                                     *
*******************************************************************************/

#include "keypad.h"
#include "../../MCAL/GPIO/gpio.h"

/*******************************************************************************
*                      Functions Prototypes(Private)                          *
*******************************************************************************/

/*******************************************************************************
*                      Functions Definitions                                  *
*******************************************************************************/
void KEYPAD_init()
{
	GPIO_setupPinDirection(KEYPAD_ROWS_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID, LOGIC_HIGH);
	GPIO_setupPinDirection(KEYPAD_ROWS_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+1, LOGIC_HIGH);
	GPIO_setupPinDirection(KEYPAD_ROWS_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+2, LOGIC_HIGH);
	GPIO_setupPinDirection(KEYPAD_ROWS_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+3, LOGIC_HIGH);
	GPIO_setupPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID, LOGIC_LOW);
	GPIO_setupPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+1, LOGIC_LOW);
	GPIO_setupPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+2, LOGIC_LOW);
	GPIO_setupPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+3, LOGIC_LOW);
	GPIO_writePin(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID, LOGIC_HIGH);
	GPIO_writePin(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+1, LOGIC_HIGH);
	GPIO_writePin(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+2, LOGIC_HIGH);
	GPIO_writePin(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+3, LOGIC_HIGH);
}

uint8 KEYPAD_getPressedKey()
{
//	 char arr[4][4]={{'D','C','B','A'},{'#','9','6','3'},{'0','8','5','2'},{'*','7','4','1'}}; /* Hardware */
	 char arr[4][4]={{'1','2','3','A'},{'4','5','6','B'},{'7','8','9','C'},{'*','0','#','D'}}; /* Software */
	 char row,coloumn,x;
	 char returnval=NOTPRESSED;
	 while(returnval == NOTPRESSED)
	 {
		 for(row=0;row<4;row++)
		 {
			 GPIO_writePin(KEYPAD_ROWS_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID, LOGIC_HIGH);
			 GPIO_writePin(KEYPAD_ROWS_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+1, LOGIC_HIGH);
			 GPIO_writePin(KEYPAD_ROWS_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+2, LOGIC_HIGH);
			 GPIO_writePin(KEYPAD_ROWS_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+3, LOGIC_HIGH);
			 GPIO_writePin(KEYPAD_ROWS_PORT_ID, row+KEYPAD_FIRST_ROW_PIN_ID, LOGIC_LOW);

			for(coloumn=0;coloumn<4;coloumn++)
			{
				x= GPIO_readPin(KEYPAD_COL_PORT_ID, coloumn+4);
				if(x==0)
				 {
					 returnval=arr[row][coloumn];
					 break;
				 }
			}
			if(x==0)
			{
				break;
			}
		}
		 if(returnval != NOTPRESSED)
		 return returnval ;
	 }
}
