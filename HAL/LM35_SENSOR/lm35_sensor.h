/******************************************************************************
*  File name:		lm35_sensor.h
*  Author:			Oct 5, 2022
*  Author:			Ahmed Tarek
*******************************************************************************/

#ifndef HAL_LM35_SENSOR_LM35_SENSOR_H_
#define HAL_LM35_SENSOR_LM35_SENSOR_H_

/*******************************************************************************
*                        		Inclusions                                     *
*******************************************************************************/

#include "../../LIB/std_types.h"

/*******************************************************************************
*                        		Definitions                                    *
*******************************************************************************/

#define LM35_MAX_VOLT_VALUE		1.5
#define LM35_MAX_TEMPERATURE	150
#define	LM35_CHANNEL_ID			2

/*******************************************************************************
*                      Functions Prototypes                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		LM35_getTemperature
* Description:			Function to read the temperature sensor and return it
* Parameters (in):    	None
* Parameters (out):   	Temperature Value
* Return value:      	uint8
********************************************************************************/

uint8 LM35_getTemperature(void);

#endif /* HAL_LM35_SENSOR_LM35_SENSOR_H_ */
