/******************************************************************************
*  File name:		twi.h
*  Author:			Oct 22, 2022
*  Author:			Ahmed Tarek
*******************************************************************************/

#ifndef MCAL_TWI_TWI_H_
#define MCAL_TWI_TWI_H_

/*******************************************************************************
*                        		Inclusions                                     *
*******************************************************************************/

#include "../../LIB/std_types.h"

/*******************************************************************************
*                        		Definitions                                    *
*******************************************************************************/

/* I2C Status Bits in the TWSR Register */
#define TWI_START         0x08 /* start has been sent */
#define TWI_REP_START     0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */

/*******************************************************************************
*                      Functions Prototypes                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		TWI_init
* Description:			Function to initialize the I2C.
* Parameters (in):    	None
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

void TWI_init();

/*******************************************************************************
* Function Name:		TWI_start
* Description:			Function to send start bit.
* Parameters (in):    	None
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

void TWI_start();

/*******************************************************************************
* Function Name:		TWI_stop
* Description:			Function to send stop bit.
* Parameters (in):    	None
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

void TWI_stop();

/*******************************************************************************
* Function Name:		TWI_writeByte
* Description:			Function to send byte on the bus.
* Parameters (in):    	Byte to send it.
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

void TWI_writeByte(uint8 byte);

/*******************************************************************************
* Function Name:		TWI_readByteWithACK
* Description:			Function to receive byte and send ACK.
* Parameters (in):    	None
* Parameters (out):   	The received byte.
* Return value:      	uint8
********************************************************************************/

uint8 TWI_readByteWithACK(void);

/*******************************************************************************
* Function Name:		TWI_readByteWithNACK
* Description:			Function to receive byte and send NACK.
* Parameters (in):    	None
* Parameters (out):   	The received byte.
* Return value:      	uint8
********************************************************************************/


uint8 TWI_readByteWithNACK(void);

/*******************************************************************************
* Function Name:		TWI_getStatus
* Description:			Function to check the I2C bus status.
* Parameters (in):    	None
* Parameters (out):   	Bus status
* Return value:      	uint8
********************************************************************************/

uint8 TWI_getStatus(void);

#endif /* MCAL_TWI_TWI_H_ */
