/******************************************************************************
*  File name:		adc.h
*  Author:			Oct 5, 2022
*  Author:			Ahmed Tarek
*******************************************************************************/

#ifndef ADC_ADC_H_
#define ADC_ADC_H_

/*******************************************************************************
*                        		Inclusions                                     *
*******************************************************************************/

#include "../../LIB/std_types.h"

/*******************************************************************************
*                        		Definitions                                    *
*******************************************************************************/

#define ADC_CHANNEL_CLEAR_MASK 	0xE0 /* Mask used to clear the channel before inserting new one */
#define ADC_MAXIMUM_VALUE		1023 /* 10 bits ADC = 2^10-1 = 1023 */
#define ADC_REF_VOLT_VALUE		5

/*******************************************************************************
*                         Types Declaration                                   *
*******************************************************************************/

/*******************************************************************************
* Name: ADC_Prescaler
* Type: Enumeration
* Description: Data type to represent the ADC prescaler
********************************************************************************/
typedef enum
{
	ADC_F_CPU_2 = 1,
	ADC_F_CPU_4,
	ADC_F_CPU_8,
	ADC_F_CPU_16,
	ADC_F_CPU_32,
	ADC_F_CPU_64,
	ADC_F_CPU_128
}ADC_Prescaler;

/*******************************************************************************
* Name: ADC_ReferenceVolatge
* Type: Enumeration
* Description: Data type to represent the ADC reference voltage
********************************************************************************/
typedef enum
{
	ADC_AREF,
	ADC_AVCC,
	ADC_INTERNAL_VREF = 3
}ADC_ReferenceVolatge;

typedef struct{

 ADC_ReferenceVolatge ref_volt;
 ADC_Prescaler prescaler;

}ADC_ConfigType;

/*******************************************************************************
*                      Functions Prototypes                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		ADC_init
* Description:			Function to dynamic configure the ADC module
* Parameters (in):    	Pointer to structure of type ADC_ConfigType
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/
void ADC_init(const ADC_ConfigType * Config_Ptr);

/*******************************************************************************
* Function Name:		ADC_readChannel
* Description:			Function to read the ADC output value
* Parameters (in):    	required channel to be sensed
* Parameters (out):   	Digital output value
* Return value:      	uint16
********************************************************************************/
uint16 ADC_readChannel(uint8 channel);

#endif /* ADC_ADC_H_ */
