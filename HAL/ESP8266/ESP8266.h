/******************************************************************************
*  File name:		ESP8266.h
*  Author:			Feb 2, 2023
*  Author:			Ahmed Tarek
*******************************************************************************/

#ifndef HAL_ESP8266_ESP8266_H_
#define HAL_ESP8266_ESP8266_H_

/*******************************************************************************
*                        		Inclusions                                     *
*******************************************************************************/

#include "../../LIB/std_types.h"

/*******************************************************************************
*                         Types Declaration                                   *
*******************************************************************************/

/*******************************************************************************
* Name: ESP_Response
* Type: Enumeration
* Description: Data type to get the response of the ESP
********************************************************************************/

typedef enum
{
	ESP_error,
	ESP_ok
}ESP_Response;

typedef enum
{
	Temperature,
	Humidity
}ESP_Data;

/*******************************************************************************
*                      Functions Prototypes                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		ESP8266_receive
* Description:			Functional to act as ISR for Uart so we can receive msgs from ESP
* Parameters (in):    	None
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

void ESP8266_receive(void);

/*******************************************************************************
* Function Name:		ESP8266_resetBuffer
* Description:			Functional to clear the receiver buffer so we can receive new msgs
* Parameters (in):    	None
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

void ESP8266_resetBuffer(void);

/*******************************************************************************
* Function Name:		ESP8266_init
* Description:			Functional used to initialize the ESP
* Parameters (in):    	None
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

void ESP8266_init(void);

/*******************************************************************************
* Function Name:		ESP8266_ping
* Description:			Send "AT" command to the ESP to know if it is working
* Parameters (in):    	None
* Parameters (out):   	OK or ERROR
* Return value:      	ESP_Response
********************************************************************************/

ESP_Response ESP8266_ping(void);

/*******************************************************************************
* Function Name:		ESP8266_connectWifi
* Description:			Functional used to Connect to Wi-Fi
* Parameters (in):    	Wi-Fi name and Password
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

void ESP8266_connectWifi(const char *SSID, const char *Pass);

/*******************************************************************************
* Function Name:		ESP8266_send
* Description:			Functional used to get the IP address of the ESP
* Parameters (in):    	Server IP and Port and Data we want to send
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

void ESP8266_sendData(const char *IP,const char *Port,ESP_Data Type,uint8 value);

#endif /* HAL_ESP8266_ESP8266_H_ */
