/******************************************************************************
*  File name:		watchdog.h
*  Author:			Oct 15, 2022
*  Author:			Ahmed Tarek
*******************************************************************************/

#ifndef MCAL_WATCHDOG_WATCHDOG_H_
#define MCAL_WATCHDOG_WATCHDOG_H_

/*******************************************************************************
*                      Functions Prototypes                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		WDT_ON
* Description:			Function to Turn on the WATCHDOG timer
* Parameters (in):    	None
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

void WDT_ON(void);

/*******************************************************************************
* Function Name:		WDT_OFF
* Description:			Function to Turn off the WATCHDOG timer
* Parameters (in):    	None
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

void WDT_OFF(void);

#endif /* MCAL_WATCHDOG_WATCHDOG_H_ */
