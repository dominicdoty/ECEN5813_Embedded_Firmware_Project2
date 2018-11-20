/*
 * output_generator.c
 *
 *  Created on: Nov 14, 2018
 *      Author: Dominic Doty
 */


#include "output_generator.h"

// STATIC FUNCTIONS
static void stringify(uint16_t input, unsigned char* output_array);
static ring_error stringify_output(uint16_t input, ring_buffer_struct* output_ring);

// GLOBAL FUNCTIONS
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
		ring_ret = ring_add_unsafe(output_ring, '\f');								// Print form feed

		for(uint16_t index = 0; index < 256; index++)
		{
			if(char_count_array[index] != 0)										// Skip any 0 characters
			{
				ring_ret = ring_add_unsafe(output_ring, (unsigned char)index);		// Print the character
				ring_ret = ring_add_unsafe(output_ring, ':');
				ring_ret = stringify_output(char_count_array[index], output_ring);
				ring_ret = ring_add_unsafe(output_ring, '\r');						// Newline/CR
				ring_ret = ring_add_unsafe(output_ring, '\n');
			}
		}
	}

	if(ring_ret == RING_FULL)
	{
		ret = OUTPUT_FULL;
	}

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
	static uint8_t last_index = 0;

	last_index = index;
	index++;

	while((char_count_array[index] == 0) && (index != last_index))		// Skip any 0 characters
	{
		// Increment index as long as it points at a char with 0 count
		// If we increment all the way back to the start, break out of the loop
		index++;
	}

	// If we've wrapped around back to zero index, print a new page character
	if(last_index >= index)
	{
		ring_ret = ring_add_unsafe(output_ring, '\f');
	}
	// If we've found a nonzero character, print it
	if(char_count_array[index] != 0)
	{
		ring_ret = ring_add_unsafe(output_ring, (unsigned char)index);		// Print the character
		ring_ret = ring_add_unsafe(output_ring, ':');						// Print semicolon divider
		ring_ret = stringify_output(char_count_array[index], output_ring);
		ring_ret = ring_add_unsafe(output_ring, '\r');						// Newline/CR
		ring_ret = ring_add_unsafe(output_ring, '\n');
	}

	if(ring_ret == RING_FULL){ret = OUTPUT_FULL;}

	return ret;
}

static void stringify(uint16_t input, unsigned char* output_array)
{
	uint16_t temp = 10000;	//10k used here since we are using a uint16, the highest it gets is 65,535
	// this is fixed with the current implementation of the function, hence not using a #define for this

	// divide by powers of ten starting at 10k till you find a non-zero result (leave off leading 0's)
	while(input/temp == 0)
	{
		temp /= 10;
	}

	uint8_t index = 0;
	uint8_t result = 0;
	while(temp != 0)
	{
		result = input/temp;									// Find what the number in the ten power place is (eg 100s, 10s place)
		input = input - (result*temp);							// Remove that from the input number
		output_array[index] = (unsigned char)(result + 48);	// Add the number in the ten power place to output string
		temp /= 10;												// Move down to the next power place
		index++;												// Move over to the next spot in output array
	}
	output_array[index] = '\0';								// End of string null
}

static ring_error stringify_output(uint16_t input, ring_buffer_struct* output_ring)
{
	unsigned char num_string_buffer[6];
	uint8_t num_string_index = 0;
	ring_error ring_ret = RING_SUCCESS;

	stringify(input, num_string_buffer);
	while(num_string_buffer[num_string_index] != '\0')
	{
		ring_ret = ring_add_unsafe(output_ring, num_string_buffer[num_string_index]);	// Print the count of character
		num_string_index++;
	}

	return ring_ret;
}
