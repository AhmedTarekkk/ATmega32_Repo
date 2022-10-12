/******************************************************************************
*  File name:		uart.h
*  Author:			Oct 12, 2022
*  Author:			Ahmed Tarek
*******************************************************************************/

#ifndef MCAL_UART_UART_H_
#define MCAL_UART_UART_H_

/*******************************************************************************
*                        		Inclusions                                     *
*******************************************************************************/

#include "../../LIB/std_types.h"

/*******************************************************************************
*                        		Definitions                                    *
*******************************************************************************/

#define CLEAR_PARITY_MASK			0xCF
#define CLEAR_STOP_BITS_MASK		0xF7
#define CLEAR_CHAR_SIZE_MASK		0xF9

/*******************************************************************************
*                         Types Declaration                                   *
*******************************************************************************/

/*******************************************************************************
* Name: UART_Parity
* Type: Enumeration
* Description: Data type to represent different parities of UART
********************************************************************************/

typedef enum
{
	UART_DISABLED_PARTIY,
	UART_EVEN_PARITY=2,
	UART_ODD_PARITY
}UART_Parity;

/*******************************************************************************
* Name: UART_StopBits
* Type: Enumeration
* Description: Data type to represent number of stop bits in UART module
********************************************************************************/

typedef enum
{
	UART_1_STOP_BIT,
	UART_2_STOP_BITS
}UART_StopBits;

/*******************************************************************************
* Name: UART_CharSize
* Type: Enumeration
* Description: Data type to represent number of data bits in the UART frame
********************************************************************************/

typedef enum
{
	UART_5_BITS,
	UART_6_BITS,
	UART_7_BITS,
	UART_8_BITS
}UART_CharSize;

/*******************************************************************************
* Name: UART_ConfigType
* Type: Enumeration
* Description: Data type to dynamic configure the UART module
********************************************************************************/

typedef struct
{
	uint32 BAUD_RATE;
	uint8 END_SRTING; /* Receive the required string until the END_STRING char */
	UART_StopBits STOP_BIT ;
	UART_CharSize CHAR_SIZE ; /* max 8-bit not 9 */
	UART_Parity parity;
}UART_ConfigType;

/*******************************************************************************
*                      Functions Prototypes                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		UART_init
* Description:			Functional responsible for Initialize the UART
* Parameters (in):    	Pointer to structure of type UART_ConfigType
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

void UART_init(const UART_ConfigType * Configptr );

/*******************************************************************************
* Function Name:		UART_sendByte
* Description:			Functional responsible for send byte to another UART device
* Parameters (in):    	Byte to send it
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

void UART_sendByte(const uint8 data);

/*******************************************************************************
* Function Name:		UART_receiveByte
* Description:			Functional responsible for receive byte from another UART device.
* Parameters (in):    	None
* Parameters (out):   	None
* Return value:      	uint8
********************************************************************************/

uint8 UART_receiveByte();

/*******************************************************************************
* Function Name:		UART_sendString
* Description:			Send the required string through UART to the other UART device.
* Parameters (in):    	String
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

void UART_sendString(const uint8 *Str);

/*******************************************************************************
* Function Name:		UART_receiveString
* Description:			Receive the required string from the other UART device.
* Parameters (in):    	String to save the data in
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

void UART_receiveString(uint8 *Str);



#endif /* MCAL_UART_UART_H_ */
