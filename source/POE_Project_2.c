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
#define OUT_RING_SIZE	256
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

/* Declare Flags */
volatile uint8_t schedule_flags = 0;

int main(void) {

  	/* Init board hardware. */
    BOARD_InitBootPins();			//Configures UART pins
    BOARD_InitBootClocks();			//Configure system clocks

    /* Initialize Buffers */
    if(ring_init(&output_ring, buffer, OUT_RING_SIZE) !=  RING_SUCCESS)
    {
    	FATAL_ERROR;
    }
    if(char_reset(input_array) != CHAR_SUCCESS)
    {
    	FATAL_ERROR;
    }

    /* Initialize UART0 */
    uart_config init_uart0 = UART_INIT_DEFAULT;
    if(uart_init(&init_uart0) != UART_SUCCESS)
    {
    	FATAL_ERROR;
    }

//    output_error output_ret = OUTPUT_SUCCESS;

    while(1)
    {
    	GPIO_TogglePinsOutput(GPIOB, (1 << 8));
//    	if(schedule_flags == 1)
//    	{
//    		output_ret = output_complete(input_array, &output_ring);
//    		if(output_ret != OUTPUT_SUCCESS)
//			{
//				FATAL_ERROR;
//			}
//    		NVIC_DisableIRQ(UART0_IRQn);
//    		schedule_flags = 0;
//    		NVIC_DisableIRQ(UART0_IRQn);
//    	}
    }

    return 0;
}

void UART0_IRQHandler(void)
{
	unsigned char data = 0;

	// Receive a Character
	if(uart_receive_full((UART_Type*)UART0))
	{
		uart_receive((UART_Type*)UART0, &data);
	}

	// Transmit a Character
	if(!uart_transmit_full((UART_Type*)UART0))
	{
		uart_transmit((UART_Type*)UART0, data);
	}
}
