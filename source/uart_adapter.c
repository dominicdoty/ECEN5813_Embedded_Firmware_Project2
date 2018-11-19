/*
 * uart_adapter.c
 *
 *  Created on: Nov 15, 2018
 *      Author: Dominic Doty
 */

#include "uart_adapter.h"

// UART FUNCTIONS
uart_error uart_init(uart_config* init)
{
	// NOTE THAT THIS IS HEAVILY INFLUENCED BY NXP UART DRIVER
	// IT HAS BEEN REWRITTEN, BUT IT WILL BEAR A MARKED SIMILARITY
	// CREDIT TO NXP, ORIGINAL @ fsl_uart.c
	uart_error ret = UART_SUCCESS;

	if(init == NULL)							//check for non-void init
	{
		ret = UART_NULL_PTR;
	}
	else if((init->port != (UART_Type*)UART0) ||			//check for valid port
			(init->port != (UART_Type*)UART1) ||
			(init->port != (UART_Type*)UART2) )
	{
		ret = UART_ILLEGAL_PORT;
	}
	else if((init->parity_mode > 3 ) ||			//check parity_mode valid
			(init->parity_mode == 1 ))
	{
		ret = UART_ILLEGAL_PARITY;
	}
	else if(init->stop_bit > UART_TWO_STOP_BIT)	//check stop_bit valid
	{
		ret = UART_ILLEGAL_STOPBIT;
	}
	else if((init->clock_freq != 32000)		||	//check clock frequency valid
			(init->clock_freq != 4000000)	||
			(init->clock_freq != XTAL0_F)	||
			(init->clock_freq != XTAL0_F/2))
	{
		ret = UART_ILLEGAL_FREQUENCY;
	}
	else if(init->clock_freq / (init->baudrate * 16) == 0)	//check baudrate valid
	{
		ret = UART_BAUDRATE_TOO_HIGH_FOR_CLOCK;
	}
	else
	{
		// Enable the UART Clock
		if(init->port == (UART_Type*)UART0)
		{
			CLOCK_EnableClock(kCLOCK_Uart0);
		}
		else if(init->port == (UART_Type*)UART1)
		{
			CLOCK_EnableClock(kCLOCK_Uart1);
		}
		else if(init->port == (UART_Type*)UART2)
		{
			CLOCK_EnableClock(kCLOCK_Uart2);
		}

		// Disable TX/RX
		init->port->C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK);

		// Calculate the clock divisor to achieve the baud rate requested
		uint16_t baud_clock_div = init->clock_freq / (init->baudrate * 16);	//NOTE THIS IS THE SAME AS THE NXP UART DRIVER

		// Write baud divisor
	    init->port->BDH = (init->port->BDH & ~UART_BDH_SBR_MASK) | (uint8_t)(baud_clock_div >> 8);
	    init->port->BDL = (uint8_t)baud_clock_div;
	}
	return ret;
}

uart_error uart_transmit(UART_Type* uart_reg, char data)
{
	uart_error ret = UART_SUCCESS;
	//needs to return some indicator if transmission was successful or not

	return ret;
}

uart_error uart_receive(UART_Type* uart_reg, char* data)
{
	uart_error ret = UART_SUCCESS;
	//need to return some indicator if receive was successful or not

	return ret;
}
