/******************************************************************************
*  File name:		ultrasonic.c
*  Author:			Oct 15, 2022
*  Author:			Ahmed Tarek
*******************************************************************************/

/*******************************************************************************
*                        		Inclusions                                     *
*******************************************************************************/

#include "ultrasonic.h"
#include "../../MCAL/ICU/icu.h"
#include "../../MCAL/GPIO/gpio.h"
#include "util/delay.h"

/*******************************************************************************
*                           Global Variables                                  *
*******************************************************************************/

/* Global static to make it's scope in this file only */
static uint8 g_edgeCount = 0; /* Variable used to process the edge and calculate the high time of it */
static uint16 g_highTime = 0; /* Variable used to store the high time of the edge on it */

/*******************************************************************************
*                      Functions Definitions                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		ULTRASONIC_init
* Description:			Function to initialize the ULTRASONIC device and its pins
********************************************************************************/

void ULTRASONIC_init(void)
{
	GPIO_setupPinDirection(ULTRASONIC_TR_PORT_ID, ULTRASONIC_TR_PIN_ID, PIN_OUTPUT); /* TR is output pin */
	GPIO_writePin(ULTRASONIC_TR_PORT_ID, ULTRASONIC_TR_PIN_ID, LOGIC_HIGH); /* TR = 0 in idle case */
	GPIO_setupPinDirection(ULTRASONIC_EKKO_PORT_ID, ULTRASONIC_EKKO_PIN_ID, PIN_INPUT); /* EKKO is input pin */

	ICU_ConfigType Config = {F_CPU_8,RISING}; /* Structure that have configuration we want */

	ICU_setCallBack(ULTRASONIC_edgeProcessing); /* Setting the call back function to be ULTRASONIC_edgeProcessing */
	ICU_init(&Config);  /* configure the ICU to detect rising edge with frequency = F_CPU/8 */

}

/*******************************************************************************
* Function Name:		ULTRASONIC_Trigger
* Description:			Function to trigger the ULTRASONIC device to start measuring
********************************************************************************/

void ULTRASONIC_Trigger(void)
{
	_delay_ms(60); /* As we have to wait at least 50ms before sending the next trigger */

	/* Trigger the ULTRASONIC device by writing high voltage in TR pin for 10 us */
	GPIO_writePin(ULTRASONIC_TR_PORT_ID, ULTRASONIC_TR_PIN_ID, LOGIC_HIGH);
	_delay_us(10); /*sending high voltage in the pin for 10us to trigger the module */
	GPIO_writePin(ULTRASONIC_TR_PORT_ID, ULTRASONIC_TR_PIN_ID, LOGIC_LOW);
}

/*******************************************************************************
* Function Name:		ULTRASONIC_readDistance
* Description:			Function to calculate the distance from the high time of the edge
********************************************************************************/

uint16 ULTRASONIC_readDistance(void)
{
	uint16 distance;

	ULTRASONIC_Trigger(); /* Send trigger  pulse */

	while(g_edgeCount < 2){} /* Polling until ULTRASONIC_edgeProcessing function calculate the high time */

	distance = (uint16)(g_highTime*0.0173) ;

	return distance;
}

/*******************************************************************************
* Function Name:		ULTRASONIC_edgeProcessing
* Description:			Call back function for the ICU interrupt to calculate high time for the edge
********************************************************************************/

void ULTRASONIC_edgeProcessing(void)
{
	g_edgeCount++;
	if(g_edgeCount == 1)
	{
		ICU_clearTimerValue(); /* To start counting From zero */
		ICU_setEdgeDetectionType(FALLING); 	/* Detect falling edge */
	}
	else if(g_edgeCount == 2)
	{
		g_highTime = ICU_getInputCaptureValue(); /* ICR1 - 0 */
		ICU_setEdgeDetectionType(RISING); 	/* Detect Rising edge */
	}
	else
	{
		g_edgeCount = 0;
	}
}
