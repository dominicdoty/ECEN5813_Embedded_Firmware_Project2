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
	// NOTE THAT THIS IS HEAVILY INFLUENCED BY NXP UART DRIVER
	// IT HAS BEEN REWRITTEN, BUT IT WILL BEAR A MARKED SIMILARITY
	// CREDIT TO NXP, ORIGINAL @ fsl_uart.c
	uart_error ret = UART_SUCCESS;

	if(init == NULL)										//check for non-void init
	{
		ret = UART_NULL_PTR;
	}
	else if(!((init->port == (UART_Type*)UART0) ||			//check for valid port
			(init->port == (UART_Type*)UART1) 	||
			(init->port == (UART_Type*)UART2)))
	{
		ret = UART_ILLEGAL_PORT;
	}
	else if(!(	(init->parity_mode == UART_PARITY_DISABLED) ||	//check parity_mode valid
				(init->parity_mode == UART_PARITY_EVEN)		||
				(init->parity_mode == UART_PARITY_ODD )))
	{
		ret = UART_ILLEGAL_PARITY;
	}
	else if(init->clock_freq == 0)							//check clock frequency valid
	{
		ret = UART_ILLEGAL_FREQUENCY;
	}
	else if(init->clock_freq / (init->baudrate * 16) == 0)	//check baudrate valid
	{
		ret = UART_BAUDRATE_TOO_HIGH_FOR_CLOCK;
	}
	else
	{
		// Enable the UART Clock
		if(init->port == (UART_Type*)UART0)
		{
			CLOCK_SetLpsci0Clock(1);
			CLOCK_EnableClock(kCLOCK_Uart0);
		}
		else if(init->port == (UART_Type*)UART1)
		{
			CLOCK_EnableClock(kCLOCK_Uart1);
		}
		else if(init->port == (UART_Type*)UART2)
		{
			CLOCK_EnableClock(kCLOCK_Uart2);
		}

		// Disable TX/RX
		init->port->C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK);

		// Calculate the clock divisor to achieve the baud rate requested
		uint16_t baud_clock_div = init->clock_freq / (init->baudrate * 16);	//NOTE THIS IS THE SAME AS THE NXP UART DRIVER

		// Write baud divisor
	    init->port->BDH = (init->port->BDH & ~UART_BDH_SBR_MASK) | (uint8_t)(baud_clock_div >> 8);
	    init->port->BDL = (uint8_t)baud_clock_div;

	    // Set Bit Count and Parity Mode
	    uint8_t reg = init->port->C1 & ~(UART_C1_PE_MASK | UART_C1_PT_MASK | UART_C1_M_MASK);	//Pulls config register and clears all flags we want to mess with
		if(init->parity_mode != UART_PARITY_DISABLED)
		{
			reg |= UART_C1_M_MASK;							//Sets bits per char to 9 (parity enabled adds 1 bit)
			reg |= (init->parity_mode << UART_C1_PT_SHIFT);	//Sets parity enabled and parity mode
		}
		init->port->C1 = reg;

		// Set Enable RX/TX
		init->port->C2 |= UART_C2_TE_MASK;
		init->port->C2 |= UART_C2_RE_MASK;

		// Configure Interrupts (Lifted from NXP fsl_uart.c - not original)
		//kUART_TxDataRegEmptyInterruptEnable for txing
		uint32_t mask = (kUART_RxDataRegFullInterruptEnable) & kUART_AllInterruptsEnable;
	    init->port->BDH |= mask;
	    init->port->C2 |= (mask >> 8);
	    init->port->C3 |= (mask >> 16);
		NVIC_EnableIRQ(UART0_IRQn);
	}
	return ret;
}

uart_error uart_transmit(UART_Type* uart_reg, unsigned char data)
{
	uart_error ret = UART_SUCCESS;
	uart_reg->D = data;
	return ret;
}

bool uart_transmit_full(UART_Type* uart_reg)
{
	return !(uart_reg->S1 & UART_S1_TDRE_MASK);
}

uart_error uart_transmit_blocking(UART_Type* uart_reg, unsigned char data)
{
	while(uart_transmit_full(uart_reg));
	return uart_transmit(uart_reg, data);
}

uart_error uart_receive(UART_Type* uart_reg, unsigned char* data)
{
	uart_error ret = UART_SUCCESS;
	*data = uart_reg->D;
	return ret;
}

bool uart_receive_full(UART_Type* uart_reg)
{
	return uart_reg->S1 & UART_S1_RDRF_MASK;
}

uart_error uart_receive_blocking(UART_Type* uart_reg, unsigned char* data)
{
	while(!uart_receive_full(uart_reg));
	return uart_receive(uart_reg, data);
}
