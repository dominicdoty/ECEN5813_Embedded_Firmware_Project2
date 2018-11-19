/*
 * output_generator.c
 *
 *  Created on: Nov 14, 2018
 *      Author: Dominic Doty
 */


#include "output_generator.h"

output_error output_complete(char_counter char_count_array, ring_buffer_struct* output_ring)
{
	output_error ret = OUTPUT_SUCCESS;
	ring_error ring_ret = RING_SUCCESS;

	if(char_count_array == NULL)
	{
		ret = OUTPUT_NULL_PTR;
	}
	else if(output_ring == NULL)
	{
		ret = OUTPUT_NULL_PTR;
	}
	else
	{
		ring_ret = ring_add_unsafe(output_ring, (char)12);							// Print form feed

		for(uint16_t index = 0; index < 256; index++)
		{
			if(char_count_array[index] != 0)										// Skip any 0 characters
			{
				ring_ret = ring_add_unsafe(output_ring, (unsigned char)index);		// Print the character
				ring_ret = ring_add_unsafe(output_ring, ':');
				ring_ret = ring_add_unsafe(output_ring, char_count_array[index]);	// Print the count of character
				ring_ret = ring_add_unsafe(output_ring, '\r');						// Newline/CR
				ring_ret = ring_add_unsafe(output_ring, '\n');
			}
		}
	}

	if(ring_ret == RING_FULL){ret = OUTPUT_FULL;}

	return ret;
}

output_error output_single_char(char_counter char_count_array, ring_buffer_struct* output_ring)
{
	output_error ret = OUTPUT_SUCCESS;

	if(output_ring == NULL)
	{
		ret = OUTPUT_NULL_PTR;
	}
	else if(char_count_array == NULL)
	{
		ret = OUTPUT_NULL_PTR;
	}
	else
	{
		ret = output_single_char_unsafe(char_count_array, output_ring);
	}
	return ret; 
}

output_error output_single_char_unsafe(char_counter char_count_array, ring_buffer_struct* output_ring)
{
	output_error ret = OUTPUT_SUCCESS;
	ring_error ring_ret = RING_SUCCESS;
	static uint8_t index = 0;

	if(index == 0)
	{
		ring_ret = ring_add_unsafe(output_ring, (unsigned char)12);
	}

	if(char_count_array[index] != 0)										// Skip any 0 characters
	{
		ring_ret = ring_add_unsafe(output_ring, (unsigned char)index);		// Print the character
		ring_ret = ring_add_unsafe(output_ring, ':');
		ring_ret = ring_add_unsafe(output_ring, char_count_array[index]);	// Print the count of character
		ring_ret = ring_add_unsafe(output_ring, '\r');						// Newline/CR
		ring_ret = ring_add_unsafe(output_ring, '\n');
	}

	index++;

	if(ring_ret == RING_FULL){ret = OUTPUT_FULL;}

	return ret;
}