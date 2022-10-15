/******************************************************************************
*  File name:		main.c
*  Author:			Oct 14, 2022
*  Author:			Ahmed Tarek
*******************************************************************************/

#ifndef MCAL_SPI_SPI_H_
#define MCAL_SPI_SPI_H_

/*******************************************************************************
*                        		Inclusions                                     *
*******************************************************************************/

#include "../../LIB/std_types.h"

/*******************************************************************************
*                        		Definitions                                    *
*******************************************************************************/

#define SPI_DEFAULT_DATA_VALUE			0xFF


/*******************************************************************************
*                      Functions Prototypes                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		SPI_initMaster
* Description:			Initialize the SPI device as Master.
* Parameters (in):    	None
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

void SPI_initMaster(void);

/*******************************************************************************
* Function Name:		SPI_initSlave
* Description:			Initialize the SPI device as Slave.
* Parameters (in):    	None
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

void SPI_initSlave(void);

/*******************************************************************************
* Function Name:		SPI_sendReceive
* Description:			Send the required data through SPI to the other SPI device.
*						In the same time data will be received from the other device.
* Parameters (in):    	data to be sent or it may be just a garbage so we can receive
* Parameters (out):   	None
* Return value:      	uint8
********************************************************************************/

uint8 SPI_sendReceiveByte(uint8 data);

/*******************************************************************************
* Function Name:		SPI_sendString
* Description:			Send the required string through SPI to the other SPI device.
* Parameters (in):    	String to send it
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

void SPI_sendString(const uint8 *str);

/*******************************************************************************
* Function Name:		SPI_receiveString
* Description:			 Receive the required string SPI from the other SPI device.
* Parameters (in):    	String to save the received string in it
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

void SPI_receiveString(uint8 *str);

/*******************************************************************************
* Function Name:		SPI_setEndStringChar
* Description:			Function to set the end string special character
* Parameters (in):    	Symbol to set the end string special char to,it is = # by default
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

void SPI_setEndStringChar(uint8 symbol);

#endif /* MCAL_SPI_SPI_H_ */
