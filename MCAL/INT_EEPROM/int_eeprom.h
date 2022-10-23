/******************************************************************************
*  File name:		int_eeprom.c
*  Author:			Oct 22, 2022
*  Author:			Ahmed Tarek
*******************************************************************************/

#ifndef MCAL_INT_EEPROM_INT_EEPROM_H_
#define MCAL_INT_EEPROM_INT_EEPROM_H_

/*******************************************************************************
*                        		Inclusions                                     *
*******************************************************************************/

#include "../../LIB/std_types.h"
#include <avr/eeprom.h> /* to solve AVR GCC Optimization problem */

/*******************************************************************************
*                        		Macros		                                   *
*******************************************************************************/

/*******************************************************************************
* Macro Name:			INT_EEPROM_writeByte
* Description:			As there is a problem with WINAVR due to optimization setting using writeByteOPT
*						won't work so we have to use assembly code to make the function work.
* Parameters (in):    	Location address and data to save it on it.
********************************************************************************/

#define INT_EEPROM_writeByte(addressPtr,byte)	eeprom_write_byte((uint8 *)addressPtr, byte)

/*******************************************************************************
*                      Functions Prototypes                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		INT_EEPROM_writeByteOPT
* Description:			Function to write byte into certain location
* Parameters (in):    	Location address and required byte
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

void INT_EEPROM_writeByteOPT(uint16 address, uint8 byte);

/*******************************************************************************
* Function Name:		INT_EEPROM_writeBlock
* Description:			Function to write more than one byte into certain locations
* Parameters (in):    	Location address, array with the required bytes, array size
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

void INT_EEPROM_writeBlock(uint16 address, uint8* array, uint8 size);

/*******************************************************************************
* Function Name:		INT_EEPROM_readByte
* Description:			Function to return value stored in given location
* Parameters (in):    	Location address
* Parameters (out):   	None
* Return value:      	uint8
********************************************************************************/

uint8 INT_EEPROM_readByte(uint16 address);

/*******************************************************************************
* Function Name:		INT_EEPROM_readBlock
* Description:			Function to return value stored in given sequential locations
* Parameters (in):    	Location address, array to save the data in it, array size
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

void INT_EEPROM_readBlock(uint16 address, uint8* array , uint8 size);

#endif /* MCAL_INT_EEPROM_INT_EEPROM_H_ */
