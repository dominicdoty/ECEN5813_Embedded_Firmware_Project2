/*
 * uart_adapter.h
 *
 *  Created on: Nov 15, 2018
 *      Author: Dominic Doty
 */

#ifndef UART_ADAPTER_H_
#define UART_ADAPTER_H_

// UART INCLUDES
#include "stddef.h"
#include "stdbool.h"
#include "stdint.h"
#include "fsl_clock.h"

// UART DEFINES
#define UART_PARITY_DISABLED	0x0U
#define UART_PARITY_EVEN		0x2U
#define UART_PARITY_ODD			0x3U
#define UART_ONE_STOP_BIT		0x0U
#define UART_TWO_STOP_BIT		0x1U

// UART VARIABLES
typedef struct
{
	uint32_t* port_ptr;
	uint32_t clock_freq;
	clock_ip_name_t clock_name;
	uint32_t baudrate;
	uint8_t parity_mode;
	uint8_t stop_bit;
	bool enable_tx;
	bool enable_rx;
}uart_config;

// NEED REAL ERRORS
typedef enum {UART_SUCCESS, UART_NULL_PTR, UART_NULL_PORT, UART_ILLEGAL_PARITY, UART_ILLEGAL_STOPBIT, UART_ILLEGAL_FREQUENCY, UART_BAUDRATE_TOO_HIGH_FOR_CLOCK}uart_error;

// UART FUNCTIONS
uart_error uart_init(uart_config* init);

uart_error uart_transmit(int8_t* uart_reg, char data);

uart_error uart_receive(int8_t* uart_reg, char* data);

#endif /* UART_ADAPTER_H_ */
