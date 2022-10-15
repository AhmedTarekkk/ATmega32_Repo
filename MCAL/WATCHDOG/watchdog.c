/******************************************************************************
*  File name:		watchdog.c
*  Author:			Oct 15, 2022
*  Author:			Ahmed Tarek
*******************************************************************************/

/*******************************************************************************
*                        		Inclusions                                     *
*******************************************************************************/

#include "watchdog.h"
#include "avr/io.h"

/*******************************************************************************
*                      Functions Definitions                                   *
*******************************************************************************/

void WDT_ON(void)
{
	/* WATCHDOG timer enables with timeout period 2.1 second. */
	WDTCR = (1<<WDE)|(1<<WDP2)|(1<<WDP1)|(1<<WDP0);
}

void WDT_OFF(void)
{
	/* Set the WDTOE & WDE bits in the same operation */
	WDTCR = (1<<WDTOE)|(1<<WDE);
	/* Wait 4 cycles before clear the WDE bit */
	_delay_us(4);
	WDTCR = 0x00;
}
