/******************************************************************************
*  File name:		lm35_sensor.c
*  Author:			Oct 5, 2022
*  Author:			Ahmed Tarek
*******************************************************************************/

/*******************************************************************************
*                        		Inclusions                                     *
*******************************************************************************/

#include "lm35_sensor.h"
#include "../../MCAL/ADC/adc.h"


uint8 LM35_getTemperature(void)
{
	uint8 lm35_value;

	uint16 adc_value;

	adc_value = ADC_readChannel(LM35_CHANNEL_ID);

	lm35_value = (uint8)(((uint32)adc_value*ADC_REF_VOLT_VALUE*LM35_MAX_TEMPERATURE)/(ADC_MAXIMUM_VALUE*LM35_MAX_VOLT_VALUE));

	return lm35_value;
}
