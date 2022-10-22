/******************************************************************************
*  File name:		eeprom.h
*  Author:			Oct 22, 2022
*  Author:			Ahmed Tarek
*******************************************************************************/

#ifndef HAL_EXT_EEPORM_EEPROM_H_
#define HAL_EXT_EEPORM_EEPROM_H_

/*******************************************************************************
*                        		Inclusions                                     *
*******************************************************************************/

#include "../../LIB/std_types.h"

/*******************************************************************************
*                        		Definitions                                    *
*******************************************************************************/

#define ERROR 0
#define SUCCESS 1

/*******************************************************************************
*                      Functions Prototypes                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		EEPROM_writeBytr
* Description:			Function to initialize the I2C.
* Parameters (in):    	Required address and the data.
* Parameters (out):   	SUCCESS or ERROR
* Return value:      	uint8
********************************************************************************/

uint8 EEPROM_writeBytr(uint16 address,uint8 byte);

/*******************************************************************************
* Function Name:		EEPROM_readByte
* Description:			Function to write byte in specific location.
* Parameters (in):    	Required address and variable to store the data in it.
* Parameters (out):   	SUCCESS or ERROR
* Return value:      	uint8
********************************************************************************/

uint8 EEPROM_readByte(uint16 address,uint8 *value);

#endif /* HAL_EXT_EEPORM_EEPROM_H_ */
