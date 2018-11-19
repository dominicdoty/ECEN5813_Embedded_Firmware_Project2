/*
 * uart_adapter.c
 *
 *  Created on: Nov 15, 2018
 *      Author: Dominic Doty
 */

#include "uart_adapter.h"

/*
// UART DEFINES
#define UART_PARITY_DISABLED	0x0U
#define UART_PARITY_EVEN		0x2U
#define UART_PARITY_ODD			0x3U
#define UART_ONE_STOP_BIT		0x0U
#define UART_TWO_STOP_BIT		0x1U


// UART VARIABLES
typedef struct
{
	uint8_t* port_ptr;
	uint32_t clock_freq;
	uint32_t baudrate;
	uint8_t parity_mode;
	uint8_t stop_bit;
	bool enable_tx;
	bool enable_rx;
}uart_config;

// NEED REAL ERRORS
typedef enum {UART_SUCCESS, UART_FAILURE}uart_error;
*/
// UART FUNCTIONS
uart_error uart_init(uart_config* init)
{
	uart_error ret = UART_SUCCESS;
	if( (init == NULL) ||					//check for non-void init
		(init->port_ptr == NULL) ||			//check for non-void port pointer
		(init->clock_freq != badnumber) ||	//check clock frequency valid
		(init->baudrate == badnumber) ||	//check baudrate valid
		(init->parity_mode <=  ) ||	//check parity_mode valid
		(init->stop_bit <= UART_TWO_STOP_BIT) ) 	//check stop_bit valid
	{
		ret = UART_FAILURE;
	}
	else
	{
		// do some init tasks
	}
	return ret;
}

void uart_transmit(int8_t* uart_reg, char data)
{

}

char uart_receive(int8_t* uart_reg)
{

}
