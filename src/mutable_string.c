/*
 * Copyright (c) 2013-2015, Michael D. Stemle, Jr.
 * libmanchicken - All rights reserved.
	* 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * Redistributions of source code must retain the above copyright notice, this list
 * of conditions and the following disclaimer.
 * 
 * Redistributions in binary form must reproduce the above copyright notice, this
 * list of conditions and the following disclaimer in the documentation and/or other
 * materials provided with the distribution.
 * Neither the name of Michael D. Stemle, Jr., notsosoft.net, nor the names of its
 * contributors may be used to endorse or promote products derived from this software
 * without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
*/

#define __IN_MUTABLE_STRING_C__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mutable_string.h>

char mutable_string_error;

char mutable_string_get_error() {
	return mutable_string_error;
}

inline size_t _calculate_new_size(size_t str_length) {
	return ((str_length + 1) * sizeof(char));
}

mutable_string_t* mutable_string_init(mutable_string_t *target) {
	memset(target, 0, sizeof(mutable_string_t));

	target->data = NULL;
	target->_data_size = 0;
	target->length = 0;

	mutable_string_t *to_return = mutable_string_resize(
		target,
		(INITIAL_MUTABLE_STRING_ALLOCATION*sizeof(char))
	);

	memset(target->data, '\0', INITIAL_MUTABLE_STRING_ALLOCATION);

	return to_return;
}

mutable_string_t* mutable_string_init_with_value(
	mutable_string_t *target, 
	const char *value
) {
	if (!mutable_string_init(target)) {
		return NULL;
	}

	if (!mutable_string_assign(target, value)) {
		return NULL;
	}

	return target;
}

mutable_string_t* mutable_string_resize(mutable_string_t* target, size_t new_size)
{
	// this check is for security and memory management
	if (new_size > MAXIMUM_MUTABLE_STRING_SIZE ||
			new_size <= 0)
	{
		mutable_string_error = MUTABLE_STRING_ERROR_TOO_BIG;
		return NULL;
	}

	char *check_ptr = NULL;

	if (target->data == NULL) {
		check_ptr = (char*)malloc(new_size);
	} else {
		check_ptr = (char*)realloc(target->data, new_size);
	}

	// If we're out of memory, don't trash the existing value, let the caller handle it!
	if (check_ptr == NULL && new_size > 0) {
		mutable_string_error = MUTABLE_STRING_ERROR_OUT_OF_MEMORY;
		return NULL;
	}
	target->data = check_ptr;

	// Handle the string ending stuff...
	if (new_size < target->_data_size) {
		target->data[new_size-1] = '\0';

	} else if (target->length == 0) {
		target->data[0] = '\0';
	}

	target->_data_size = new_size;

	if (!mutable_string_is_empty(target)) {
		target->length = strlen(target->data);
	}

	return target;
}

void mutable_string_free(mutable_string_t *target) {
	// Sometimes you get garbage...
	if (!target)
		return;

	free(target->data);
	target->_data_size = 0;
	target->length = 0;

	return;
}

mutable_string_t* mutable_string_assign(mutable_string_t *dest, const char *src) {
	size_t src_length = strlen(src);
	size_t new_size = _calculate_new_size(src_length);

	// Grow the string if necessary
	if (new_size > dest->_data_size) {
		if (mutable_string_resize(dest,new_size) == NULL) {
			return NULL;
		}

	} // We don't shrink the string!

	strcpy(dest->data, src);
	dest->length = src_length;
	dest->_data_size = new_size;

	return dest;
}

mutable_string_t* mutable_string_append(mutable_string_t *dest, const char *src) {
	if (mutable_string_is_empty(dest)) {
		return mutable_string_assign(dest, src);
	}

	size_t new_len = strlen(src) + dest->length;
	size_t new_size = _calculate_new_size(new_len);

	// Grow if necessary.
	if (new_size > dest->_data_size) {
		if (mutable_string_resize(dest, new_size) == NULL) {
			return NULL;
		}

	}

	strncat(dest->data, src, MAXIMUM_MUTABLE_STRING_SIZE);
	dest->length = new_len;
	dest->_data_size = new_size;

	return dest;
}

int mutable_string_get_length(mutable_string_t *var) {
	
	// We keep the length of the string as we go along.
	return var->length;
	
}

short mutable_string_is_empty(mutable_string_t *var) {
	
	// A NULL data pointer is an empty string.
	if (var->data == NULL) {
		return 1;
	}
	
	// A null terminator at the beginning of the character array
	// is an empty string.
	if (var->data[0] == '\0') {
		return 1;
	}
	
	return 0;
	
}

char* mutable_string_get_data(mutable_string_t *var) {
	return var->data;
}

mutable_string_t* mutable_string_copy(mutable_string_t *dest, mutable_string_t *src)
{
	return mutable_string_assign(dest, mutable_string_get_data(src));
}

mutable_string_t* mutable_string_append_mutable_string(mutable_string_t *dest, mutable_string_t *src) {
	return mutable_string_append(dest, MUTSTR(src));
}

mutable_string_t* mutable_string_append_char(mutable_string_t *dest, char src) {
	char _src[2];
	sprintf(_src, "%c", src);

	return mutable_string_append(dest, _src);
}

char mutable_string_char_at(mutable_string_t *subject, int position) {
	if (position < 0) {
		position = MUTLEN(subject) + position; /* (X>0) + (Y<0) should = (Z>0) */
	}

	if (position < 0 || position > MUTLEN(subject)) {
		mutable_string_error = MUTABLE_STRING_ERROR_OUT_OF_RANGE;
		return 0;
	}

	return subject->data[position];
}

mutable_string_t* mutable_string_substring(
	mutable_string_t *subject,
	mutable_string_t *destination,
	int offset,
	size_t length
) {
	char *subject_ptr = NULL;
	char *destination_ptr = NULL;
	
	// See if our offset is valid.
	if (offset > MUTLEN(subject)) {
		mutable_string_error = MUTABLE_STRING_ERROR_OUT_OF_RANGE;
		return NULL;
	}
	
	// First, let's allocate our destination
	if (! mutable_string_resize(destination, _calculate_new_size(length))) {
		// Don't need to set the error since mutable_string_resize() does
		// that already
		return NULL;
	}
	
	// Now copy the substring
	subject_ptr = MUTSTR(subject) + offset;
	destination_ptr = MUTSTR(destination);
	memcpy(destination_ptr, subject_ptr, length);
	
	return destination;
}

/* These are a little lazy, but they're useful in a pinch. Needs error checking. */
int mutable_string_parse_int(mutable_string_t *var) {
	if (MUTLEN(var) == 0) {
		mutable_string_error = MUTABLE_STRING_ERROR_NAN;
		return 0;
	}
	return atoi(MUTSTR(var));
}

long mutable_string_parse_long(mutable_string_t *var) {
	if (MUTLEN(var) == 0) {
		mutable_string_error = MUTABLE_STRING_ERROR_NAN;
		return 0;
	}
	return atol(MUTSTR(var));
}

long long mutable_string_parse_long_long(mutable_string_t *var) {
	if (MUTLEN(var) == 0) {
		mutable_string_error = MUTABLE_STRING_ERROR_NAN;
		return 0;
	}
	return atoll(MUTSTR(var));
}

double mutable_string_parse_double(mutable_string_t *var) {
	if (MUTLEN(var) == 0) {
		mutable_string_error = MUTABLE_STRING_ERROR_NAN;
		return 0;
	}
	return atof(MUTSTR(var));
}
