/*
 * Copyright 2016-2018 NXP Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    POE_Project_2_Project_2.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
//#include "fsl_debug_console.h"
/* APPLICATION HEADERS */
#include "char_counter.h"
#include "output_generator.h"
#include "ring_buffer.h"
#include "uart_adapter.h"
#include "uart_handler.h"

/* APPLCIATION DEFINES */
#define OUT_RING_SIZE	16
#define FATAL_ERROR_DEBUG

#ifdef FATAL_ERROR_DEBUG
	#define FATAL_ERROR __asm__("BKPT");
#else
	#define FATAL_ERROR	NVIC_SystemReset();
#endif

/* Declare Buffers */
char_counter input_array;
ring_buffer_struct output_ring;
unsigned char buffer[OUT_RING_SIZE];


int main(void) {

  	/* Init board hardware. */
    BOARD_InitBootPins();			//Configures UART pins
    BOARD_InitBootClocks();			//Configure system clocks

    /* Initialize UART0 */
    uart_config init_uart0 = UART_INIT_DEFAULT;
    if(uart_init(&init_uart0) != UART_SUCCESS)
    {
    	FATAL_ERROR;
    }

    /* Initialize Buffers */
    if(ring_init(&output_ring, buffer, OUT_RING_SIZE) !=  RING_SUCCESS)
    {
    	FATAL_ERROR;
    }
    if(char_reset(input_array) != CHAR_SUCCESS)
    {
    	FATAL_ERROR;
    }

    output_error output_ret = OUTPUT_SUCCESS;
    ring_error ring_ret = UART_SUCCESS;
	unsigned char data = 0;

    while(1)
    {
    	// Generate character count for one character (actually 5 chars->  "e:5\r\n" )
    	output_ret = output_single_char(input_array, &output_ring);
    	if(output_ret != OUTPUT_SUCCESS)
    	{
    		FATAL_ERROR;
    	}

		// TX/RX till transmit buffer is empty
    	ring_ret = RING_SUCCESS;
    	while(1)
    	{
    		// Receive a Character
    		if(uart_receive_full(init_uart0.port))
    		{
    			uart_receive(init_uart0.port, &data);
    			char_add(input_array, data);
    		}
    		// Transmit a Character if the buffer isn't full
    		if(!uart_transmit_full(init_uart0.port))
    		{
    			// Transmit a Character if one is successfully removed from the ring
    			ring_ret = ring_remove(&output_ring, &data);
    			if(ring_ret == RING_SUCCESS)
    			{
    				if(data == '\f'){for(uint32_t i = 0; i < 100000; i++){}}
    				uart_transmit(init_uart0.port, data);
    			}
    			else
    			{
    				// No characters to transmit, break while(1)
    				break;
    			}
    		}
    	}
    }


    return 0 ;
}
