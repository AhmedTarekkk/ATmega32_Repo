/******************************************************************************
*  File name:		ESP8266.c
*  Date:			Feb 2, 2023
*  Author:			Ahmed Tarek
*******************************************************************************/

/*******************************************************************************
*                        		Inclusions                                     *
*******************************************************************************/

#include "ESP8266.h"
#include "avr/io.h"
#include "avr/interrupt.h"
#include <string.h>
#include <stdio.h>
#include "../../LIB/common_macros.h"
#include "../../MCAL/UART/uart.h"
#include "../../MCAL/TIMER1/timer1.h"
#include "../LCD/lcd.h"

/*******************************************************************************
*                           Global Variables                                  *
*******************************************************************************/

uint8 temp[100] = { 0 }; /* buffer to store messages from ESP */
static uint8 counter = 0 ; /* counter to indicate the received chat location */
char (*P_Orders)[20] = NULL ; /* Gloabl variabl to store the pointer to the reciver buffer of the main */
extern uint8 OrdersWaiting;
static uint8 PushPointer = 0;

/*******************************************************************************
*                           Private Function                                  *
*******************************************************************************/

/*******************************************************************************
* Function Name:		ESP8266_sendATCommand
* Description:			Functional to send AT commands to the ESP
* Parameters (in):    	None
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

static void ESP8266_sendATCommand(char* AT_Command); /* can be used in this file only */

/*******************************************************************************
*                      Functions Definitions                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		ESP8266_receive
********************************************************************************/
void ESP8266_ISRreceive(void)
{
	temp[counter] = UDR;
	counter++;
	if(counter == 100){
		counter = 0; //pointer = 0;
	}
	if((strncmp((char*)temp,"\r\n+IPD",6) == 0) && temp[counter-1]=='\n')
	{
		ESP8266_responseToServer();
	}
}

/*******************************************************************************
* Function Name:		ESP8266_waitExpectedResponse
********************************************************************************/
ESP_Response ESP8266_waitExpectedResponse(char * Expected_Response,uint16 MaxTimeout)
{
	uint8 ResponseLength = strlen(Expected_Response);
	uint16 time = 0;
	/* Wait until we get the expected response from the ESP or timeout occur*/
	while((strncmp((char*)temp,Expected_Response,ResponseLength) != 0) && (time < MaxTimeout))
	{
		time++;
		Timer1_Delay_ms(1);
	}
	cli(); /* close the global interrupt so we don't get interrupted */

	if((strncmp((char*)temp,"ALREADY",7) == 0)) /* check if we sent command that already applied to ESP */
	{
		time = 0;
	}
	ESP8266_resetBuffer();  /* Clear the receive buffer */

	if(time >= MaxTimeout ) 	/* check if timeout occurred */
	{
		return ESP_error;
	}
	return ESP_ok;
}

/*******************************************************************************
* Function Name:		ESP8266_resetBuffer
********************************************************************************/
void ESP8266_resetBuffer()
{
	memset(temp, 0, sizeof temp); /* Clear the whole variable */
	counter = 0; /* reset counter to index 0 */
}

/*******************************************************************************
* Function Name:		ESP8266_sendATCommand
********************************************************************************/
void ESP8266_sendATCommand(char* AT_Command)
{
		char Expected_Response[60] = "\r\nOK\r\n";
		uint16 timeout = 2000; /* 2 seconds timeout */
		if(strcmp(AT_Command,"ATE0\r\n") == 0) /* printing on the LCD the command purpose */
		{
			LCD_displayString("Disabling Echo");
			strcpy(Expected_Response,"ATE0\r\r\n\r\nOK\r\n");
		}
		else if(strcmp(AT_Command,"AT+CWMODE=3\r\n") == 0)
		{
			LCD_displayString("ESP Station Mode");
		}
		else if(strcmp(AT_Command,"AT+CIPMUX=0\r\n") == 0)
		{
			LCD_displayString("Single Channel");
		}
		else if(strcmp(AT_Command,"AT+CIPMODE=0\r\n") == 0)
		{
			LCD_displayString("Normal Mode");
		}
		else if(strcmp(AT_Command,"AT\r\n") == 0)
		{
			LCD_displayString("AT");
		}
		else if(strncmp(AT_Command,"AT+CWJAP",8) == 0)
		{
			LCD_displayString("Connect to Wi-Fi");
			timeout = 10000; /* 10 seconds timeout */
			strcpy(Expected_Response,"WIFI DISCONNECT\r\nWIFI CONNECTED\r\nWIFI GOT IP\r\n\r\nOK\r\n");
		}
		else if(strncmp(AT_Command,"AT+CIPSTART",11) == 0)
		{
			LCD_displayString("Connect to Server");
			strcpy(Expected_Response,"CONNECT\r\n\r\nOK\r\n");
		}
		else if(strncmp(AT_Command,"AT+CIPCLOSE",11) == 0)
		{
			LCD_displayString("Complete Sending");
			strcpy(Expected_Response,"CLOSED\r\n\r\nOK\r\n");
		}
		else if(strncmp(AT_Command,"AT+CIPSEND",10) == 0)
		{
			LCD_displayString("Sending Data");
		}
		else
		{
			LCD_displayString("Unknown Command");
		}
		LCD_moveCursor(1, 0);
		ESP8266_resetBuffer();
		sei();
		UART_sendString(AT_Command); /* send the command over the UART */
		uint8 State = ESP8266_waitExpectedResponse(Expected_Response, timeout); /* wait to get the expected response */
		if(State == ESP_ok)
		{
			LCD_displayString("OK");
			Timer1_Delay_ms(1000);
			LCD_clearScreen();
		}
		else
		{
			LCD_displayString("ERROR");
			Timer1_Delay_ms(1000);
			LCD_clearScreen();
		}

}

/*******************************************************************************
* Function Name:		ESP8266_init
********************************************************************************/
void ESP8266_init(char ordersBuffer[][BUFFER_SIZE])
{
	LCD_clearScreen();

	P_Orders = ordersBuffer;
	uint8 oldsreg = SREG; /* Store the global interrupt status before closing it*/
	cli(); /* close the global interrupt so we don't get interrupted while initializing */
	UART_setCallBack(ESP8266_ISRreceive);

	char* AT_Command = NULL_PTR; /* to make it not wild pointer */

	AT_Command = "ATE0\r\n"; /* command to disable the echo */
	ESP8266_sendATCommand(AT_Command);

	AT_Command = "AT+CWMODE=3\r\n"; /* command to make the ESP in station mode */
	ESP8266_sendATCommand(AT_Command);

	AT_Command = "AT+CIPMUX=0\r\n"; /* Command to make the ESP has single connection */
	ESP8266_sendATCommand(AT_Command);

	AT_Command = "AT+CIPMODE=0\r\n"; /* Command to make the ESP has single connection */
	ESP8266_sendATCommand(AT_Command);

	SREG = oldsreg; /* Return SREG to its initial value */
	LCD_clearScreen();
}

/*******************************************************************************
* Function Name:		ESP8266_ping
********************************************************************************/
ESP_Response ESP8266_ping(void)
{
	LCD_clearScreen();
	uint8 oldsreg = SREG; /* Store the global interrupt status before closing it*/

	char* AT_Command = "AT\r\n";
	ESP8266_sendATCommand(AT_Command);

	SREG = oldsreg;
	return 	ESP_ok;
}

/*******************************************************************************
* Function Name:		ESP8266_connectWifi
********************************************************************************/
void ESP8266_connectWifiAndServer(const char *SSID, const char *Pass,const char *IP,const char *Port)
{
	char AT_Command[60] = {0};
	uint8 oldsreg = SREG; /* Store the global interrupt status before closing it*/

	/* Command to connect to Wi-fi with SSID and Password */
	sprintf((char*) AT_Command, (char*) "AT+CWJAP=\"%s\",\"%s\"\r\n", SSID, Pass);
	ESP8266_sendATCommand(AT_Command);

	/* Command to connect to TCP server with IP and Port */
	sprintf((char*) AT_Command, (char*) "AT+CIPSTART=\"TCP\",\"%s\",%s\r\n", IP, Port);
	ESP8266_sendATCommand(AT_Command);

	SREG = oldsreg;
	LCD_clearScreen();
}

/*******************************************************************************
* Function Name:		ESP8266_sendData
********************************************************************************/
void ESP8266_sendData(const char *IP,const char *Port,const char *ESP_Data)
{
	uint8 oldsreg = SREG;
	char AT_Command[60] = {0};
	LCD_clearScreen();

	uint8 length = strlen(ESP_Data);

	/* Command to send data server with defined length */
	sprintf((char*) AT_Command, (char*) "AT+CIPSEND=%d\r\n", length+2);
	ESP8266_sendATCommand(AT_Command);

	/* Sending the data starting with 0 then the length then that actual data */
	UART_sendByte(0x00); /* The first byte is zero */
	UART_sendByte(length); /* The second byte is the length of the data */
	UART_sendString(ESP_Data); /* The data */
	sei();
	Timer1_Delay_ms(3000);
	cli();
	ESP8266_resetBuffer();

	/* Command to close the connection so we can send the data */
	strcpy(AT_Command,"AT+CIPCLOSE\r\n");
	ESP8266_sendATCommand(AT_Command);

	/* Connecting to the server again so we can use it later */
	sprintf((char*) AT_Command, (char*) "AT+CIPSTART=\"TCP\",\"%s\",%s\r\n", IP, Port);
	ESP8266_sendATCommand(AT_Command);

	SREG = oldsreg;
	LCD_clearScreen();
}

/*******************************************************************************
* Functions Name:		ESP8266_responseToServer
********************************************************************************/
void ESP8266_responseToServer(void)
{
	if(OrdersWaiting <= MAX_ORDERS)
	{
		OrdersWaiting++;
		uint8 index = 0;
		while(temp[index++] != ':'); /* increment the index till it reach the order */
		index += 2; /* add two to skip the first two garbage characters */
		strcpy(P_Orders[PushPointer],(char *)(temp+index)); /* Save the order into the buffer */
		PushPointer++;
		if(PushPointer >= MAX_ORDERS)
		{
			PushPointer = 0;
		}
	}
	ESP8266_resetBuffer();
}
