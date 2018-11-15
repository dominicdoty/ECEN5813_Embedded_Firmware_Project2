/*
 * uart_adapter.h
 *
 *  Created on: Nov 15, 2018
 *      Author: Dominic Doty
 */

#ifndef UART_ADAPTER_H_
#define UART_ADAPTER_H_

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

// UART FUNCTIONS
void uart_init(uart_error* ret, uart_config* init);

void uart_transmit(int8_t* uart_reg, char data);

char uart_receive(int8_t* uart_reg);

#endif /* UART_ADAPTER_H_ */
