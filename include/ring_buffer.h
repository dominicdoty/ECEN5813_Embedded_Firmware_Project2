/*
 * ring_buffer.h
 *
 *  Created on: Nov 08, 2018
 *      Author: Dominic Doty
 *
 *	Ring buffer functions. "unsafe" versions don't check for null pointers on input
 *	It is assumed that these will only be used in functions where the input has already been confirmed non null
 */

#ifndef RING_BUFFER_H_
#define RING_BUFFER_H_

#include "stdint.h"
#include "stddef.h"
#include "stdbool.h"

typedef struct
{
	unsigned char* buffer;
	uint16_t head;
	uint16_t tail;
	uint16_t mask;
}ring_buffer_struct;

typedef enum {RING_SUCCESS, RING_NULL_PTR, RING_ILLEGAL_SIZE, RING_FULL, RING_EMPTY}ring_error;

ring_error ring_init(ring_buffer_struct* rbs, unsigned char* buffer, uint16_t size);

ring_error ring_add(ring_buffer_struct* rbs, unsigned char addition);

ring_error ring_add_unsafe(ring_buffer_struct* rbs, unsigned char addition);

ring_error ring_remove(ring_buffer_struct* rbs, unsigned char* removal);

ring_error ring_remove_unsafe(ring_buffer_struct* rbs, unsigned char* removal);

ring_error ring_element_count(ring_buffer_struct* rbs, uint16_t* count);

ring_error ring_element_count_unsafe(ring_buffer_struct* rbs, uint16_t* count);

#endif /* RING_BUFFER_H_ */
