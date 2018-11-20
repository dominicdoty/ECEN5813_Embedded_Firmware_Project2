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
#include "fsl_uart.h"

// UART DEFINES
#define UART_PARITY_DISABLED	0x0U
#define UART_PARITY_EVEN		0x2U
#define UART_PARITY_ODD			0x3U
#define XTAL0_F					8000000

#define UART_INIT_DEFAULT								\
			{.port = (UART_Type*)UART0,					\
			.clock_freq = CLOCK_GetPllFllSelClkFreq(),	\
			.baudrate = 115200,							\
			.parity_mode = UART_PARITY_DISABLED,		\
			.enable_tx = true,							\
			.enable_rx = true}

// UART VARIABLES
typedef struct
{
	UART_Type* port;
	uint32_t clock_freq;
	uint32_t baudrate;
	uint8_t parity_mode;
	bool enable_tx;
	bool enable_rx;
}uart_config;

typedef enum {UART_SUCCESS, UART_NULL_PTR, UART_ILLEGAL_PORT, UART_ILLEGAL_PARITY, UART_ILLEGAL_STOPBIT, UART_ILLEGAL_FREQUENCY, UART_BAUDRATE_TOO_HIGH_FOR_CLOCK, UART_FAILURE}uart_error;

// UART FUNCTIONS
uart_error uart_init(uart_config* init);

uart_error uart_transmit(UART_Type* uart_reg, unsigned char data);

bool uart_transmit_full(UART_Type* uart_reg);

uart_error uart_transmit_blocking(UART_Type* uart_reg, unsigned char data);

uart_error uart_receive(UART_Type* uart_reg, unsigned char* data);

bool uart_receive_full(UART_Type* uart_reg);

uart_error uart_receive_blocking(UART_Type* uart_reg, unsigned char* data);

#endif /* UART_ADAPTER_H_ */
