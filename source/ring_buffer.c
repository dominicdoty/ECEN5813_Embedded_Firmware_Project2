/*
 * ring_buffer.c
 *
 *  Created on: Nov 08, 2018
 *      Author: Dominic Doty
 */

#include "ring_buffer.h"

static bool is_pow_two(uint16_t number)
{
	// NOTE: This is "Brian Kernighan Method"
	// http://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetTable

	uint16_t ret; 					// ret accumulates the total bits set in v
	for (ret = 0; number; ret++)
	{
		number &= number - 1;		// clear the least significant bit set
	}
	return (ret == 1);
}


ring_error ring_init(ring_buffer_struct* rbs, unsigned char* buffer, uint16_t size)
{
	ring_error ret = RING_SUCCESS;

	if(rbs == NULL)
	{
		// Check for NULL ring ptr
		ret = RING_NULL_PTR;
	}
	else if(buffer == NULL)
	{
		// Check for NULL buffer ptr
		ret = RING_NULL_PTR;
	}
	else if(!is_pow_two(size))
	{
		ret = RING_ILLEGAL_SIZE;
	}
	else
	{
		rbs->buffer = buffer;
		rbs->head = 0;
		rbs->tail = 0;
		rbs->mask = size - 1;
	}

	return ret;
}


ring_error ring_add(ring_buffer_struct* rbs, unsigned char addition)
{
	ring_error ret = RING_SUCCESS;

	if(rbs == NULL)
	{
		// Check for NULL ring ptr
		ret = RING_NULL_PTR;
	}
	else
	{
		ret = ring_add_unsafe(rbs, addition);
	}

	return ret;
}

ring_error ring_add_unsafe(ring_buffer_struct* rbs, unsigned char addition)
{
	ring_error ret = RING_SUCCESS;

	rbs->buffer[rbs->head] = addition;			// Add thing to buffer
	rbs->head = (rbs->head + 1) & rbs->mask;	// Increment the head / wrap
	if(rbs->head == rbs->tail)					// Check for full buffer
	{
		rbs->head = (rbs->head - 1) & rbs->mask;
		ret = RING_FULL;
	}

	return ret;
}


ring_error ring_remove(ring_buffer_struct* rbs, unsigned char* removal)
{
	ring_error ret = RING_SUCCESS;

	if(rbs == NULL)
	{
		// Check for NULL ring ptr
		ret = RING_NULL_PTR;
	}
	else if(removal == NULL)
	{
		// Check for NULL return ptr
		ret = RING_NULL_PTR;
	}
	else
	{
		ret = ring_remove_unsafe(rbs, removal);
	}

	return ret;
}

ring_error ring_remove_unsafe(ring_buffer_struct* rbs, unsigned char* removal)
{
	ring_error ret = RING_SUCCESS;

	if(rbs->head == rbs->tail)					// Check if the buffer is empty
	{
		ret = RING_EMPTY;
	}
	else
	{
		*removal = rbs->buffer[rbs->tail];			// Remove the thing
		rbs->tail = (rbs->tail + 1) & rbs->mask; 	// Increment the tail and wrap
	}

	return ret;
}

ring_error ring_element_count(ring_buffer_struct* rbs, uint16_t* count)
{
	ring_error ret = RING_SUCCESS;

	if(rbs == NULL)
	{
		// Check for NULL ring ptr
		ret = RING_NULL_PTR;
	}
	else if(count == NULL)
	{
		// Check for NULL return ptr
		ret = RING_NULL_PTR;
	}
	else
	{
		ring_element_count_unsafe(rbs, count);
	}

	return ret;
}

ring_error ring_element_count_unsafe(ring_buffer_struct* rbs, uint16_t* count)
{
	ring_error ret = RING_SUCCESS;

	// Calculate the number of elements
	// head - tail, if negative, add size of ring (mask+1)
	// need to check that this doesn't have over/underflow issues
	uint32_t temp = (rbs->head - rbs->tail) < 0 ?
					rbs->head - rbs->tail + rbs->mask + 1 :
					rbs->head - rbs->tail;
	*count = (uint16_t)temp;

	if(rbs->head == (rbs->tail - 1))
	{
		ret = RING_FULL;
	}

	return ret;
}
