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
	uart_error ret = UART_SUCCESS;

	if(init == NULL)							//check for non-void init
	{
		ret = UART_NULL_PTR;
	}
	else if(init->port_ptr == NULL)				//check for non-void port pointer
	{
		ret = UART_NULL_PORT;
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
			(init->clock_freq != EXTAL0)	||
			(init->clock_freq != XTAL0)		||
			(init->clock_freq != EXTAL0/2)	||
			(init->clock_freq != XTAL0/2))
	{
		ret = UART_ILLEGAL_FREQUENCY;
	}
	else if(init->clock_freq / (init->baudrate * 16) == 0)	//check baudrate valid
	{
		ret = UART_BAUDRATE_TOO_HIGH_FOR_CLOCK;
	}
	else
	{
		// Calculate the clock divisor to achieve the baud rate requested
		baud_clock_div = init->clock_freq / (init->baudrate * 16);	//NOTE THIS IS THE SAME AS THE NXP UART DRIVER


		// do some init tasks
	}
	return ret;
}

uart_error uart_transmit(int8_t* uart_reg, char data)
{
	uart_error ret = UART_SUCCESS;
	//needs to return some indicator if transmission was successful or not
}

uart_error uart_receive(int8_t* uart_reg, char* data)
{
	uart_error ret = UART_SUCCESS;
	//need to return some indicator if receive was successful or not
}
