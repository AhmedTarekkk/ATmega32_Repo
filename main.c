/******************************************************************************
*  File name:		main.c
*  Author:			Oct 10, 2022
*  Author:			Ahmed Tarek
*******************************************************************************/

#include "MCAL/GPIO/gpio.h"
#include "HAL/KEYPAD/keypad.h"

int main(void)
{
	uint8 key;

	/* Use a 7-segment to display the keypad button value */
	GPIO_setupPinDirection(PORTC_ID,PIN0_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTC_ID,PIN1_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTC_ID,PIN2_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTC_ID,PIN3_ID,PIN_OUTPUT);

	while(1)
	{
		/* Get the pressed button from keypad */
		key = KEYPAD_getPressedKey();

		if((key >= 0) && (key <= 9))
		{
			GPIO_writePort(PORTC_ID,key); /* display the key number on the 7-segment */
		}
	}
}
