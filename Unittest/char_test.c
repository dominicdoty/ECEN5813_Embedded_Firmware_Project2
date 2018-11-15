/*
 * char_test.c
 *
 *  Created on: Nov 08, 2018
 *      Author: Dominic Doty
 *  Based on: http://cunit.sourceforge.net/example.html
 */

#include "Basic.h"			// CUnit Test Framework
#include "char_counter.h"

char_counter count;

void test_char_reset()
{
	/* NULL POINTERS */
	CU_ASSERT_EQUAL(char_reset(NULL), CHAR_NULL_PTR);

	/* INTRODUCE VALUES TO TEST RESET */
	count[50] = 'b';
	count[195] = 'f';
	count[255] = 'g';

	/* SUCCESS */
	CU_ASSERT_EQUAL(char_reset(count), CHAR_SUCCESS);

	/* CHECK ARRAY VALUES */
	CU_ASSERT_EQUAL(count[50], 0);
	CU_ASSERT_EQUAL(count[195], 0);
	CU_ASSERT_EQUAL(count[255], 0);
}

void test_char_add()
{
	/* NULL POINTERS */
	CU_ASSERT_EQUAL(char_add(NULL, 'b'), CHAR_NULL_PTR);

	/* TEST SUCCESSFUL ADDS */
	CU_ASSERT_EQUAL(char_add(count, 'a'), CHAR_SUCCESS);
	CU_ASSERT_EQUAL(char_add(count, 'a'), CHAR_SUCCESS);
	CU_ASSERT_EQUAL(char_add(count, 'f'), CHAR_SUCCESS);
	CU_ASSERT_EQUAL(char_add(count, '!'), CHAR_SUCCESS);

	/* CHECK ARRAY VALUES */
	CU_ASSERT_EQUAL(count[(uint8_t)'a'], 2);
	CU_ASSERT_EQUAL(count[(uint8_t)'f'], 1);
	CU_ASSERT_EQUAL(count[(uint8_t)'!'], 1);
	CU_ASSERT_EQUAL(count[(uint8_t)'b'], 0);
}


int main()
{
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
	if ((NULL == CU_add_test(pSuite, "test of char reset", test_char_reset)) ||
	(NULL == CU_add_test(pSuite, "test of char add", test_char_add)))
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
