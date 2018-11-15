/*
 * uart_handler.c
 *
 *  Created on: Nov 14, 2018
 *      Author: Dominic Doty
 */

#include "uart_handler.h"

void uart_handler(int8_t* uart_reg, char_counter in_buffer, ring_buffer_struct* out_buffer)
{
	//check for NULL pointers
	if(uart_reg == NULL)
	{
		return;
	}
	else if(out_buffer == NULL)
	{
		return;
	}
	else
	{
		// Transmit a Character

		// NEED TO CHECK IF TRANSMITTER IS BUSY BEFORE REMOVING/TRANSMITTING
		unsigned char temp = 0;
		if(ring_remove_unsafe(out_buffer, &temp))
		{
			uart_transmit(uart_reg, temp);
		}

		// Receive a Character
		// NEED TO CHECK IF VALID CHARACTER BEFORE RECEIVING/ADDING
		char_add_unsafe(in_buffer, uart_receive(uart_reg));
	}
}
