/*
 * output_test.c
 *
 *  Created on: Nov 08, 2018
 *      Author: Dominic Doty
 *  Based on: http://cunit.sourceforge.net/example.html
 */

#include "Basic.h"			// CUnit Test Framework
#include "output_generator.h"
#include "ring_buffer.h"
#include "char_counter.h"

#define RING_SIZE 32

char_counter count;
ring_buffer_struct ring;
unsigned char buffer[RING_SIZE];

static bool check_ring(ring_buffer_struct* rbs, unsigned char character, uint8_t quant)
{
	bool ret = false;
	uint32_t i = 0;

	// Find the index of the char in question
	for(; i < 65537; i++)
	{
		if(rbs->buffer[i] == character)
		{
			break;
		}
	}

	// Couldn't find the character in the output
	if(i >= 65536)
	{
		ret = false;
	}

	// Confirm the formatting and count is correct
	bool test = (	(rbs->buffer[i] == character) &&
					(rbs->buffer[i+1] == ':') &&
					(rbs->buffer[i+2] == quant) &&
					(rbs->buffer[i+3] == '\r') &&
					(rbs->buffer[i+4] == '\n') );
	// If we find the right formatted string with the right count return true
	if(test)
	{
		ret = true;
	}

	return ret;
}

void test_output_single_char()
{
	/* NULL POINTERS */
	CU_ASSERT_EQUAL(output_single_char(NULL, &ring), OUTPUT_NULL_PTR);
	CU_ASSERT_EQUAL(output_single_char(count, NULL), OUTPUT_NULL_PTR);
}

void test_output_complete()
{
	/* NULL POINTERS */
	CU_ASSERT_EQUAL(output_complete(NULL, &ring), OUTPUT_NULL_PTR);
	CU_ASSERT_EQUAL(output_complete(count, NULL), OUTPUT_NULL_PTR);

	/* SET SOME THINGS IN THE COUNT */
	char_add(count, 'd');
	char_add(count, 'd');
	char_add(count, 'd');
	char_add(count, '?');
	char_add(count, '?');
	char_add(count, 'f');
	char_add(count, 'a');

	/* GENERATE THE OUTPUT */
	CU_ASSERT_EQUAL(output_complete(count, &ring), OUTPUT_SUCCESS);

	/* CHECK THE OUTPUT */
	CU_ASSERT_EQUAL(ring.buffer[0], (unsigned char)12);
	CU_ASSERT_EQUAL(check_ring(&ring, 'd', 3), true);
	CU_ASSERT_EQUAL(check_ring(&ring, '?', 2), true);
	CU_ASSERT_EQUAL(check_ring(&ring, 'f', 1), true);
	CU_ASSERT_EQUAL(check_ring(&ring, 'a', 1), true);

	/* GENERATE OUTPUT TILL FULL BUFFER */
	CU_ASSERT_EQUAL(output_complete(count, &ring), OUTPUT_FULL);
}


int main()
{
	ring_init(&ring, buffer, RING_SIZE);
	char_reset(count);

	CU_pSuite pSuite = NULL;

	/* initialize the CUnit test registry */
	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	/* add a suite to the registry */
	pSuite = CU_add_suite("Char Counter Tests", NULL, NULL);
	if (NULL == pSuite)
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* add the tests to the suite */
	if ((NULL == CU_add_test(pSuite, "test of single char output", test_output_single_char)) ||
	(NULL == CU_add_test(pSuite, "test of full char output", test_output_complete)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* Run all tests using the CUnit Basic interface */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}
