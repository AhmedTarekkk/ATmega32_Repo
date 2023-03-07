/******************************************************************************
*  File name:		dht11.h
*  Date:			Mar 4, 2022
*  Author:			Ahmed Tarek
*******************************************************************************/

/*******************************************************************************
*                        		Inclusions                                     *
*******************************************************************************/

#include "dht11.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "../../LIB/common_macros.h"
#include "../../MCAL/GPIO/gpio.h"
#include "../../MCAL/TIMER1/timer1.h"

/*******************************************************************************
*                            Global Variables       		                   *
*******************************************************************************/

uint8 DHT11_temp[2]; /* global variable to store the integral and decimal value of temperature */
uint8 DHT11_humi[2]; /* global variable to store the integral and decimal value of temperature */

/*******************************************************************************
*                           Private Function                                  *
*******************************************************************************/

/*******************************************************************************
* Function Name:		DHT11_Request
* Description:			Functional to send starting signal to the DHT11 and wake him up
* Parameters (in):    	None
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

static void DHT11_Request(void);

/*******************************************************************************
* Function Name:		DHT11_Response
* Description:			Functional to receive the response from the DHT11 before the data
* Parameters (in):    	None
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

static void DHT11_Response(void);

/*******************************************************************************
* Function Name:		DHT11_receiveData
* Description:			Functional to receive the data from the DHT11 sensor
* Parameters (in):    	None
* Parameters (out):   	The received value
* Return value:      	uint8
********************************************************************************/

static uint8 DHT11_receiveData(void);

/*******************************************************************************
* Function Name:		DHT11_modifyData
* Description:			Functional to modify the data to be compatible with the hardware
* Parameters (in):    	DHT11 reading values
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

static void DHT11_modifyData(uint8 Humi_I,uint8 Humi_D,uint8 Temp_I,uint8 Temp_D);

/*******************************************************************************
*                      Functions Definitions                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		DHT11_Request
********************************************************************************/

void DHT11_Request(void)
{
	GPIO_setupPinDirection(DHT11_PORT_ID, DHT11_PIN_ID, PIN_OUTPUT); /* set the DHT pin as output */
	GPIO_writePin(DHT11_PORT_ID, DHT11_PIN_ID, LOGIC_LOW); /* write high */
	Timer1_Delay_us(20000); /* wait for 20ms */
	GPIO_writePin(DHT11_PORT_ID, DHT11_PIN_ID, LOGIC_HIGH); /* write low */
}

/*******************************************************************************
* Function Name:		DHT11_Request
********************************************************************************/

void DHT11_Response(void)
{
	GPIO_setupPinDirection(DHT11_PORT_ID, DHT11_PIN_ID, PIN_INPUT); /* set the DHT pin as input to receive data */
	GPIO_writePin(DHT11_PORT_ID, DHT11_PIN_ID, LOGIC_HIGH); /* enable the internal pull up resistor */
	while( BIT_IS_SET(DHT11_PINx_REG,DHT11_PIN_ID) ); /* wait the zero in the initial response "01" */
	while( BIT_IS_CLEAR(DHT11_PINx_REG,DHT11_PIN_ID) ); /* wait the one in the initial response "01" */
	while( BIT_IS_SET(DHT11_PINx_REG,DHT11_PIN_ID) );
}

/*******************************************************************************
* Function Name:		DHT11_Request
********************************************************************************/

uint8 DHT11_receiveData(void)
{
	uint8 data=0;
	for (sint8 i = 7 ; i >= 0 ; i--)
	{
		while( BIT_IS_CLEAR(DHT11_PINx_REG,DHT11_PIN_ID) ) {} ;	/* check received bit 0 or 1 */
		Timer1_Delay_us(30); /* wait for 30 us as zero range from 26 to 28 */
		if( BIT_IS_SET(DHT11_PINx_REG,DHT11_PIN_ID) )	/* check if high pulse is greater than 30ms */
		{
			SET_BIT(data,i); /* if it is then the bit is logic high */
		}
		else
		{
			CLEAR_BIT(data,i); /* else it is logic low */
		}

		while( BIT_IS_SET(DHT11_PINx_REG,DHT11_PIN_ID) ); /* wait until the high value ends so we can read again */
	}
	return data;
}

/*******************************************************************************
* Function Name:		DHT11_Request
********************************************************************************/

DHT11_response DHT11_getData(void)
{
	uint8 old_sreg = SREG,Checksum; /* saving the SREG register */
	cli(); /* close the global interrupt as it is critical section */

	DHT11_Request(); /* sending starting signal to wake sensor up */
	DHT11_Response(); /* receiving the response signal  */
	DHT11_humi[0] = DHT11_receiveData(); /* receiving the integral part of humidity  */
	DHT11_humi[1] = DHT11_receiveData(); /* receiving the decimal  part of humidity  */
	DHT11_temp[0] = DHT11_receiveData(); /* receiving the integral part of temperature  */
	DHT11_temp[1] = DHT11_receiveData(); /* receiving the decimal  part of temperature  */
	Checksum = DHT11_receiveData(); /* receiving the checksum value  */

	if ((uint8)(DHT11_humi[0] + DHT11_humi[1] + DHT11_temp[0] + DHT11_temp[1] ) != Checksum)
	{
		return DHT11_ERROR; /* there was an error detected by the checksum */
	}

	DHT11_modifyData(DHT11_humi[0],DHT11_humi[1],DHT11_temp[0],DHT11_temp[1]);

	SREG = old_sreg; /* go back to the previous state after exiting the critical section */
	return DHT11_OK; /* there was no error and return OK */
}

/*******************************************************************************
* Function Name:		DHT11_Request
********************************************************************************/

void DHT11_modifyData(uint8 Humi_I,uint8 Humi_D,uint8 Temp_I,uint8 Temp_D){

	uint16 x; /* variable to do the calculation and save the result in */
	x = Humi_I*256 + Humi_D;
	DHT11_humi[0] = x/10; /* updating the integral part of humidity  */
	DHT11_humi[1] = x%10; /* updating the decimal  part of humidity  */

	x = Temp_I*256 + Temp_D;
	DHT11_temp[0] = x/10; /* updating the integral part of temperature  */
	DHT11_temp[1] = x%10; /* updating the decimal  part of temperature  */
}
