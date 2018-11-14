/*
 * ring_buffer.h
 *
 *  Created on: Nov 08, 2018
 *      Author: Dominic Doty
 */

#ifndef RING_BUFFER_H_
#define RING_BUFFER_H_

#include "stdint.h"
#include "stddef.h"
#include "stdbool.h"

typedef struct
{
	char* buffer;
	uint16_t head;
	uint16_t tail;
	uint16_t mask;
}ring_buffer_struct;

enum ring_error {RING_SUCCESS, RING_NULL_PTR, RING_ILLEGAL_SIZE, RING_FULL, RING_EMPTY};

enum ring_error ring_init(ring_buffer_struct* rbs, char* buffer, uint16_t size);

enum ring_error ring_add(ring_buffer_struct* rbs, char addition);

enum ring_error ring_remove(ring_buffer_struct* rbs, char* removal);

enum ring_error ring_element_count(ring_buffer_struct* rbs, uint16_t* count);

#endif /* RING_BUFFER_H_ */
