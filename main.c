/*
 * main.c
 *
 *  Created on: Oct 4, 2022
 *      Author: Ahmed
 */

#include"HAL/LCD/lcd.h"
#include "MCAL/ADC/adc.h"
#include "HAL/LM35_SENSOR/lm35_sensor.h"

int main(void)
{
	uint8 res_value;
	LCD_init(); /* initialize LCD driver */
	//ADC_init(); /* initialize ADC driver */

	LCD_displayStringRowColumn(0, 5, "Temp = ");
	while(1)
	{
		res_value = LM35_getTemperature();
		if(res_value >= 100)
		{
			LCD_intgerToString(res_value);
		}
		else
		{
			LCD_intgerToString(res_value);
			LCD_displayCharacter(' ');
		}
	}
}
