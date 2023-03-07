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
#include "util/delay.h"
#include "avr/interrupt.h"
#include "string.h"
#include "stdio.h"
#include "../../LIB/common_macros.h"
#include "../../MCAL/UART/uart.h"
#include "../LCD/lcd.h"
#include "avr/eeprom.h"

/*******************************************************************************
*                           Global Variables                                  *
*******************************************************************************/

uint8 temp[255] = { 0 }; /* buffer to store messages from ESP */
char ESP_OK[20] = { 0 };
char ESP_ERROR[20] = { 0 };
static uint8 counter = 0 ; /* counter to indicate the received chat location */

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

void ESP8266_receive(void)
{
	uint8_t oldsrg = SREG;
	cli();
	temp[counter] = UDR;
	counter++;
	if(counter == 255){
		counter = 0; //pointer = 0;
	}
	SREG = oldsrg;
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
		LCD_clearScreen();
		if(strcmp(AT_Command,"ATE0\r\n") == 0) /* printing on the LCD the command purpose */
		{
			LCD_displayString("Disabling Echo");
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
		LCD_moveCursor(1, 0);
		UART_sendString(AT_Command); /* send the command over the UART */
		sei(); /* Enabling the global interrupt for 2 seconds so ESP can response in the temp buffer */
		_delay_ms(2000);
		cli(); /* close the global interrupt so we don't get interrupted while initializing */
		LCD_displayString("Done");
		_delay_ms(1000);
		LCD_clearScreen();
}

/*******************************************************************************
* Function Name:		ESP8266_init
********************************************************************************/

void ESP8266_init(void)
{
	LCD_clearScreen();

	uint8 oldsreg = SREG; /* Store the global interrupt status before closing it*/
	cli(); /* close the global interrupt so we don't get interrupted while initializing */
	UART_setCallBack(ESP8266_receive);

	char* AT_Command = "AT\r\n"; /* Sending AT command to get the ESP response "OK" and Save it */

	AT_Command = "ATE0\r\n"; /* command to disable the echo */
	ESP8266_sendATCommand(AT_Command);
	ESP8266_resetBuffer();

	AT_Command = "AT+CWMODE=3\r\n"; /* command to make the ESP in station mode */
	ESP8266_sendATCommand(AT_Command);
	ESP8266_resetBuffer();

	AT_Command = "AT+CIPMUX=0\r\n"; /* Command to make the ESP has single connection */
	ESP8266_sendATCommand(AT_Command);
	ESP8266_resetBuffer();

	AT_Command = "AT+CIPMODE=0\r\n"; /* Command to make the ESP has single connection */
	ESP8266_sendATCommand(AT_Command);
	ESP8266_resetBuffer();

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

	LCD_displayString("AT");
	LCD_moveCursor(1, 0);
	char* AT_Command = "AT\r\n";
	sei();
	ESP8266_resetBuffer();
	UART_sendString(AT_Command);
	while(strncmp((char*)temp,"\r\nOK\r\n",6) != 0)
	{
		_delay_ms(1);
	}
	ESP8266_resetBuffer(); /* clear the buffer again */
	LCD_displayString("OK");
	_delay_ms(1500);

	SREG = oldsreg;
	return 	ESP_ok;
}

/*******************************************************************************
* Function Name:		ESP8266_connectWifi
********************************************************************************/

void ESP8266_connectWifi(const char *SSID, const char *Pass)
{
	char AT_Command[100] = {0};
	uint8 oldsreg = SREG; /* Store the global interrupt status before closing it*/

	sprintf((char*) AT_Command, (char*) "AT+CWJAP=\"%s\",\"%s\"\r\n", SSID, Pass);
	LCD_clearScreen();
	LCD_displayString("Connect to Wi-Fi");
	LCD_moveCursor(1, 0);
	UART_sendString(AT_Command); /* send the command over the UART */
	sei();
	_delay_ms(6000);
	_delay_ms(4000);
	LCD_displayString("Done");
	_delay_ms(1000);
	cli(); /* close the global interrupt so we don't get interrupted while initializing */
	ESP8266_resetBuffer();

	SREG = oldsreg;
	LCD_clearScreen();
}

/*******************************************************************************
* Function Name:		ESP8266_sendData
********************************************************************************/

void ESP8266_sendData(const char *IP,const char *Port,ESP_Data Type ,uint8 value)
{
	uint8 oldsreg = SREG;
	char AT_Command[100] = {0};
	char ESP_Data[100] = {0};
	LCD_clearScreen();

	switch(Type)
	{
	case Temperature:
		LCD_displayString("Sending Temp");
		LCD_moveCursor(1, 0);
		sprintf((char*) ESP_Data, (char*) "ENVIRTEMPERAT%d", value);
		break;
	case Humidity:
		LCD_displayString("Sending Humidity");
		LCD_moveCursor(1, 0);
		sprintf((char*) ESP_Data, (char*) "ENVIRHUMIDITY%d", value);
		break;
	}
	uint8 length = strlen(ESP_Data);

	/* Command to connect to TCP server with IP and Port */
	sprintf((char*) AT_Command, (char*) "AT+CIPSTART=\"TCP\",\"%s\",%s\r\n", IP, Port);
	UART_sendString(AT_Command);
	sei();
	_delay_ms(3000);
	cli();
	ESP8266_resetBuffer();

	/* Command to send data server with defined length */
	sprintf((char*) AT_Command, (char*) "AT+CIPSEND=%d\r\n", length+2);
	UART_sendString(AT_Command);
	sei();
	_delay_ms(3000);
	cli();
	ESP8266_resetBuffer();

	/* Sending the data starting with 0 then the length then that actual data */
	UART_sendByte(0x00);
	UART_sendByte(length);
	UART_sendString(ESP_Data);
	sei();
	_delay_ms(3000);
	cli();

	/* Command to close the connection so we can send the data */
	strcpy(AT_Command,"AT+CIPCLOSE\r\n");
	UART_sendString(AT_Command);
	sei();
	_delay_ms(1000);
	cli();
	ESP8266_resetBuffer();

	LCD_displayString("Done"); /* printing done msg on the LCD */
	_delay_ms(1000);

	/* Connecting to the server again so we can use it later */
	sprintf((char*) AT_Command, (char*) "AT+CIPSTART=\"TCP\",\"%s\",%s\r\n", IP, Port);
	UART_sendString(AT_Command);
	sei();
	_delay_ms(3000);
	cli();
	ESP8266_resetBuffer();

	SREG = oldsreg;
	LCD_clearScreen();
}
