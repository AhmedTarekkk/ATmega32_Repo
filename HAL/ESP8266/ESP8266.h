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

#define BUFFER_SIZE				20
#define MAX_ORDERS				10

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

/*******************************************************************************
*                      Functions Prototypes                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		ESP8266_ISRreceive
* Description:			Function to act as ISR for Uart so we can receive msgs from ESP
* Parameters (in):    	None
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

void ESP8266_ISRreceive(void);

/*******************************************************************************
* Function Name:		ESP8266_waitExpectedResponse
* Description:			Function to poll and wait the ESP to send the expected response
* 						For certain time
* Parameters (in):    	None
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

ESP_Response ESP8266_waitExpectedResponse(char * Expected_Response,uint16 MaxTimeout);

/*******************************************************************************
* Function Name:		ESP8266_resetBuffer
* Description:			Function to clear the receiver buffer so we can receive new msgs
* Parameters (in):    	None
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

void ESP8266_resetBuffer(void);

/*******************************************************************************
* Function Name:		ESP8266_init
* Description:			Function used to initialize the ESP
* Parameters (in):    	Pointer to two dimensional array to act as the receiver buffer
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

void ESP8266_init(char ordersBuffer[][BUFFER_SIZE]);

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
* Description:			Function used to Connect to Wi-Fi
* Parameters (in):    	Wi-Fi name and Password
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

void ESP8266_connectWifiAndServer(const char *SSID, const char *Pass,const char *IP,const char *Port);

/*******************************************************************************
* Function Name:		ESP8266_send
* Description:			Function used to get the IP address of the ESP
* Parameters (in):    	Server IP and Port and Data we want to send
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

void ESP8266_sendData(const char *IP,const char *Port,const char *ESP_Data);

/*******************************************************************************
* Function Name:		ESP8266_responseToServer
* Description:			Function used to so the ESP can communicate with the server in both directions
* Parameters (in):    	None
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

void ESP8266_responseToServer(void);

#endif /* HAL_ESP8266_ESP8266_H_ */
