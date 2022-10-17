/******************************************************************************
*  File name:		gli.h
*  Author:			Oct 11, 2022
*  Author:			Ahmed Tarek
*******************************************************************************/

#ifndef MCAL_GLI_GLI_H_
#define MCAL_GLI_GLI_H_

/*******************************************************************************
*                        		Inclusions                                     *
*******************************************************************************/

#include "avr/interrupt.h"

/*******************************************************************************
*                      			Macros		                                   *
*******************************************************************************/

/* We are going to use macros instead of functions as sei() and cli() compiles
 * into a single line of assembly, so there is no function call overhead.
 */

/*******************************************************************************
* Macro Name:			GLI_Enable
* Description:			Global interrupt enable
* Parameters (in):    	None
********************************************************************************/

#define GLI_Enable()			sei()

/*******************************************************************************
* Macro Name:			GLI_Disable
* Description:			Global interrupt disable
* Parameters (in):    	None
********************************************************************************/

#define GLI_Disable()			cli()

#endif /* MCAL_GLI_GLI_H_ */
