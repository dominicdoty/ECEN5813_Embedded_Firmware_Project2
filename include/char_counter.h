/*
 * char_counter.h
 *
 *  Created on: Nov 14, 2018
 *      Author: Dominic Doty
 *
 *      Functions to add characters to an array that keeps track of all received chars
 *      Array must be of size 256 (0-255)
 */

#ifndef INCLUDE_CHAR_COUNTER_H_
#define INCLUDE_CHAR_COUNTER_H_

#include "stdint.h"
#include "stddef.h"

typedef volatile uint16_t char_counter[256];

typedef enum {CHAR_SUCCESS, CHAR_NULL_PTR}char_error;

char_error char_reset(char_counter array);

char_error char_add(char_counter array, unsigned char data);

char_error char_add_unsafe(char_counter array, unsigned char data);

#endif /* INCLUDE_CHAR_COUNTER_H_ */
