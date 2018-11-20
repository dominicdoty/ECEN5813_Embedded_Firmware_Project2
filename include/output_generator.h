/*
 * output_generator.h
 *
 *  Created on: Nov 14, 2018
 *      Author: Dominic Doty
 */

#ifndef INCLUDE_OUTPUT_GENERATOR_H_
#define INCLUDE_OUTPUT_GENERATOR_H_

#include "ring_buffer.h"
#include "char_counter.h"
#include "MKL25Z4.h"

typedef enum {OUTPUT_SUCCESS, OUTPUT_NULL_PTR, OUTPUT_FULL, OUTPUT_UNKNOWN_ERROR}output_error;

output_error output_complete(char_counter char_count_array, ring_buffer_struct* output_ring);

output_error output_single_char(char_counter char_count_array, ring_buffer_struct* output_ring);

output_error output_single_char_unsafe(char_counter char_count_array, ring_buffer_struct* output_ring);

#endif /* INCLUDE_OUTPUT_GENERATOR_H_ */
