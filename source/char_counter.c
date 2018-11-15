/*
 * char_counter.c
 *
 *  Created on: Nov 14, 2018
 *      Author: Dominic Doty
 */


#include "char_counter.h"

char_error char_reset(char_counter array)
{
	char_error ret = CHAR_SUCCESS;
	if(array == NULL)
	{
		ret = CHAR_NULL_PTR;
	}
	else
	{
		for(uint16_t i = 0; i < 256; i++)
		{
			array[i] = 0;
		}
	}
	return ret;
}

char_error char_add(char_counter array, unsigned char data)
{
	char_error ret = CHAR_SUCCESS;
	if(array == NULL)
	{
		ret = CHAR_NULL_PTR;
	}
	else
	{
		char_add_unsafe(array, data);
	}
	return ret;
}

char_error char_add_unsafe(char_counter array, unsigned char data)
{
	char_error ret = CHAR_SUCCESS;
	array[(uint8_t)data]++;
	return ret;
}