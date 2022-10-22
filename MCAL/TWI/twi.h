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
* Function Name:		ADC_init
* Description:			Function to dynamic configure the ADC module
* Parameters (in):    	Pointer to structure of type ADC_ConfigType
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/
void TWI_init();
void TWI_start();
void TWI_stop();
void TWI_writeByte(uint8 byte);
uint8 TWI_readByteWithACK(void);
uint8 TWI_readByteWithNACK(void);
uint8 TWI_getStatus(void);
#endif /* MCAL_TWI_TWI_H_ */
