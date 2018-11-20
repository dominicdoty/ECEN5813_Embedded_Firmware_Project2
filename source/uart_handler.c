/*
 * uart_handler.c
 *
 *  Created on: Nov 14, 2018
 *      Author: Dominic Doty
 */

#include "uart_handler.h"

void uart_handler(UART_Type* uart_reg, char_counter in_buffer, ring_buffer_struct* out_buffer)
{
	NVIC_DisableIRQ(UART0_IRQn);
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
		unsigned char data = 0;

		// Receive a Character
		if(uart_receive_full(uart_reg))
		{
			uart_receive(uart_reg, &data);
			char_add_unsafe(in_buffer, data);
			schedule_flags = 1;					// Flag tells main we need to generate new output
		}

		// Transmit a Character
		//&& (UART0->C2 & UART_C2_TIE_MASK)
		if(!uart_transmit_full(uart_reg))
		{
			ring_error ring_ret = ring_remove_unsafe(out_buffer, &data);
			if(ring_ret == RING_SUCCESS)
			{
				uart_transmit(uart_reg, data);
			}
			else if(ring_ret == RING_EMPTY)
			{
				// No more transmits needed, disable interrupt
				UART0->C2 &= ~UART_C2_TIE_MASK;
			}
		}
	}

	NVIC_EnableIRQ(UART0_IRQn);
}
