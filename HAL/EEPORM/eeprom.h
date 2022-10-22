/******************************************************************************
*  File name:		eeprom.h
*  Author:			Oct 22, 2022
*  Author:			Ahmed Tarek
*******************************************************************************/

#ifndef HAL_EEPORM_EEPROM_H_
#define HAL_EEPORM_EEPROM_H_

#include "../../LIB/std_types.h"

#define ERROR 0
#define SUCCESS 1

uint8 EEPROM_writeBytr(uint16 address,uint8 byte);
uint8 EEPROM_readByte(uint16 address,uint8 *value);

#endif /* HAL_EEPORM_EEPROM_H_ */
