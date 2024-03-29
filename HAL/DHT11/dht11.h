/******************************************************************************
*  File name:		dht11.h
*  Date:			Mar 4, 2022
*  Author:			Ahmed Tarek
*******************************************************************************/

#ifndef HAL_DHT11_DHT11_H_
#define HAL_DHT11_DHT11_H_

/*******************************************************************************
*                        		Inclusions                                     *
*******************************************************************************/

#include "../../LIB/std_types.h"

/*******************************************************************************
*                           Extern Global Variables                            *
*******************************************************************************/

extern uint8 DHT11_temp[2];
extern uint8 DHT11_humi[2];

/*******************************************************************************
*                        		Definitions                                    *
*******************************************************************************/

#define DHT11_PORT_ID		PORTD_ID
#define DHT11_PIN_ID		PIN6_ID
#define DHT11_PINx_REG		PIND

/*******************************************************************************
*                         Types Declaration                                   *
*******************************************************************************/

/*******************************************************************************
* Name: DHT11_response
* Type: Enumeration
* Description: Data type to indicate if there was an error on the DHT values
********************************************************************************/

typedef enum
{
	DHT11_ERROR,
	DHT11_OK
}DHT11_response;

/*******************************************************************************
*                      Functions Prototypes                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		DHT11_getData
* Description:			Function to read the humidity and temperature from the dht sensor
* Parameters (in):    	void
* Parameters (out):   	OK or Error
* Return value:      	DHT11_response
********************************************************************************/

DHT11_response DHT11_getData(void) ;

#endif /* HAL_DHT11_DHT11_H_ */
