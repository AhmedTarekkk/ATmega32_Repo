/******************************************************************************
*  File name:		adc.c
*  Author:			Oct 5, 2022
*  Author:			Ahmed Tarek
*******************************************************************************/

/*******************************************************************************
*                        		Inclusions                                     *
*******************************************************************************/

#include "adc.h"
#include "avr/io.h"
#include "../../LIB/common_macros.h"

void ADC_init(const ADC_ConfigType * Config_Ptr)
{
	/* Initially set the registers with zeros so we can insert their values as we want */
	ADMUX = 0;
	ADCSRA = 0;

	 /* left shift the value by 6 so we can insert it in the right place at REFS0 and REFS1 */
	ADMUX |= ( (Config_Ptr->ref_volt) << 6 ) ;

	/* same as the last step but this time ADPSX bits are the first 3 bits so no need to shift */
	ADCSRA |= (Config_Ptr->prescaler) ;

	/* Enable the ADC */
	SET_BIT(ADCSRA,ADEN);
}

uint16 ADC_readChannel(uint8 channel)
{
	/* clear the previous channel and insert the new one in only 3 bits ( 8 channels ) " */
	ADMUX = (ADMUX & ADC_CHANNEL_CLEAR_MASK) | (channel & 0x07) ;

	/* start conversion */
	SET_BIT(ADCSRA,ADSC);

	/* wait the ADC o/p with polling method */
	while(BIT_IS_CLEAR(ADCSRA,ADIF)){}

	/* clearing ADC flag */
	SET_BIT(ADCSRA,ADIF);

	return ADC;
}
