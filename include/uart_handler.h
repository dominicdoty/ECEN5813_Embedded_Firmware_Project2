/*
 * uart_handler.h
 *
 *  Created on: Nov 14, 2018
 *      Author: Dominic Doty
 *
 *      Functions that poll/handle UART interfaces
 */

#ifndef INCLUDE_UART_HANDLER_H_
#define INCLUDE_UART_HANDLER_H_

#include "ring_buffer.h"
#include "uart_adapter.h"
#include "char_counter.h"

// Takes pointers to the UART tx/rx buffer, pointer to input buffer (char classification buffer), pointer to output buffer (ring buffer of output chars)
void uart_handler(int8_t* uart_reg, char_counter in_buffer, ring_buffer_struct* out_buffer);

#endif /* INCLUDE_UART_HANDLER_H_ */
