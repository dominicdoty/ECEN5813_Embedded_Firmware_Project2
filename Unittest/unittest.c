/*
 * ring_buffer_test.c
 *
 *  Created on: Nov 08, 2018
 *      Author: Dominic Doty
 *  Based on: http://cunit.sourceforge.net/example.html
 */

#include "Basic.h"			// CUnit Test Framework
#include "ring_buffer.h"

#define ZERO		0
#define SIXTEEN		16
#define SEVENTEEN	17

ring_buffer_struct ringo;
char buffer[SIXTEEN];


void test_ring_init()
{
	/* NULL POINTERS */
	CU_ASSERT_EQUAL(ring_init(NULL, buffer, SIXTEEN), RING_NULL_PTR);			// Test NULL struct ptr
	CU_ASSERT_EQUAL(ring_init(&ringo, NULL, SIXTEEN), RING_NULL_PTR);			// Test NULL buffer ptr

	/* BAD SIZES */
	CU_ASSERT_EQUAL(ring_init(&ringo, buffer, SEVENTEEN), RING_ILLEGAL_SIZE);	// Test non power 2 size
	CU_ASSERT_EQUAL(ring_init(&ringo, buffer, ZERO), RING_ILLEGAL_SIZE);		// Test zero size

	/* SUCCESS */
	CU_ASSERT_EQUAL(ring_init(&ringo, buffer, SIXTEEN), RING_SUCCESS);			// Good init

	/* CHECK STRUCTURE VALUES */
	CU_ASSERT_EQUAL(&ringo.buffer[0], &buffer[0]);									// Check values after init
	CU_ASSERT_EQUAL(ringo.head, 0);
	CU_ASSERT_EQUAL(ringo.tail, 0);
	CU_ASSERT_EQUAL(ringo.mask, SIXTEEN - 1);
}

void test_ring_add()
{
	/* NULL POINTERS */
	CU_ASSERT_EQUAL(ring_add(NULL, SIXTEEN), RING_NULL_PTR);					// Test NULL struct ptr
}

void test_ring_remove()
{
	/* NULL POINTERS */
	char temp = 0;
	CU_ASSERT_EQUAL(ring_remove(NULL, &temp), RING_NULL_PTR);					// Test NULL struct ptr
	CU_ASSERT_EQUAL(ring_remove(&ringo, NULL), RING_NULL_PTR);					// Test NULL return ptr
}

void test_ring_element_count()
{
	/* NULL POINTERS */
	uint16_t temp = 0;
	CU_ASSERT_EQUAL(ring_element_count(NULL, &temp), RING_NULL_PTR);			// Test NULL struct ptr
	CU_ASSERT_EQUAL(ring_element_count(&ringo, NULL), RING_NULL_PTR);			// Test NULL return ptr
}

void test_add_remove_count()
{
	/* CONFIRM A SINGLE ADDITION */
	CU_ASSERT_EQUAL(ring_add(&ringo, 'A'), RING_SUCCESS);
	CU_ASSERT_EQUAL(&ringo.buffer[0], &buffer[0]);
	CU_ASSERT_EQUAL(ringo.head, 1);
	CU_ASSERT_EQUAL(ringo.tail, 0);
	CU_ASSERT_EQUAL(ringo.mask, SIXTEEN - 1);

	/* ADD TILL FULL */
	for(char i = 'B'; i < 'B'+14; i++)
	{
		CU_ASSERT_EQUAL(ring_add(&ringo, i), RING_SUCCESS);
	}
	CU_ASSERT_EQUAL(ring_add(&ringo, 'X'), RING_FULL);

	/* CONFIRM A SINGLE REMOVAL */
	char remove = 0;
	CU_ASSERT_EQUAL(ring_remove(&ringo, &remove), RING_SUCCESS);
	CU_ASSERT_EQUAL(remove, 'A');
	CU_ASSERT_EQUAL(&ringo.buffer[0], &buffer[0]);
	CU_ASSERT_EQUAL(ringo.head, 15);
	CU_ASSERT_EQUAL(ringo.tail, 1);
	CU_ASSERT_EQUAL(ringo.mask, SIXTEEN - 1);

	/* ADD TO WRAP */
	CU_ASSERT_EQUAL(ring_add(&ringo, 'P'), RING_SUCCESS);
	CU_ASSERT_EQUAL(&ringo.buffer[0], &buffer[0]);
	CU_ASSERT_EQUAL(ringo.head, 0);
	CU_ASSERT_EQUAL(ringo.tail, 1);
	CU_ASSERT_EQUAL(ringo.mask, SIXTEEN - 1);

	/* ELEMENT COUNT WRAPPED FULL */
	uint16_t count = 0;
	CU_ASSERT_EQUAL(ring_element_count(&ringo, &count), RING_SUCCESS);
	CU_ASSERT_EQUAL(count, 15);

	/* REMOVE TILL EMPTY */
	for(uint8_t i = 'B'; i < 'B'+15; i++)
	{
		CU_ASSERT_EQUAL(ring_remove(&ringo, &remove), RING_SUCCESS);
		CU_ASSERT_EQUAL(remove, i);
	}
	CU_ASSERT_EQUAL(ring_remove(&ringo, &remove), RING_EMPTY);
	CU_ASSERT_EQUAL(ring_element_count(&ringo, &count), 0);
}

int main()
{
	CU_pSuite pSuite = NULL;

	/* initialize the CUnit test registry */
	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	/* add a suite to the registry */
	pSuite = CU_add_suite("Suite_1", NULL, NULL);
	if (NULL == pSuite)
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* add the tests to the suite */
	if ((NULL == CU_add_test(pSuite, "test of ring init", test_ring_init)) ||
	(NULL == CU_add_test(pSuite, "test of ring add args", test_ring_add)) ||
	(NULL == CU_add_test(pSuite, "test of ring remove args",test_ring_remove)) ||
	(NULL == CU_add_test(pSuite, "test of ring element args",test_ring_element_count)) ||
	(NULL == CU_add_test(pSuite, "test of ring add/remove/count",test_add_remove_count)))
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
