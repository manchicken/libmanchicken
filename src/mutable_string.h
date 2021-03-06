/*
 * Copyright (c) 2013-2020, Michael D. Stemle, Jr.
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

#ifndef __MUTABLE_STRING_H__
#define __MUTABLE_STRING_H__

#ifndef INITIAL_MUTABLE_STRING_ALLOCATION
#define INITIAL_MUTABLE_STRING_ALLOCATION 64
#endif

#ifndef MAXIMUM_MUTABLE_STRING_SIZE
// 10MiB is big enough
#define MAXIMUM_MUTABLE_STRING_SIZE     (10 * 1024 * 1024)
#endif

#include <string.h>

/* The structures */
typedef struct {
  char *data;
  size_t _data_size;
  int length;
} mutable_string_t;

typedef struct {
  mutable_string_t *target;
  char *ptr;
  int ptrlen;
} mutable_string_reference_t;

/* Error handling */
#define MUTABLE_STRING_ERROR_OK             ((char)0)
#define MUTABLE_STRING_ERROR_NAN            ((char)-1)
#define MUTABLE_STRING_ERROR_OUT_OF_RANGE   ((char)-2)
#define MUTABLE_STRING_ERROR_OUT_OF_MEMORY  ((char)-3)
#define MUTABLE_STRING_ERROR_TOO_BIG        ((char)-4)
#ifndef __IN_MUTABLE_STRING_C__
extern char mutable_string_error;
#endif
char mutable_string_get_error();

/* Shortcuts */
#define MUTSTR(X) mutable_string_get_data(X)
#define MUTLEN(X) mutable_string_get_length(X)

/* Init routines */
mutable_string_t* mutable_string_init(mutable_string_t *target);
mutable_string_t* mutable_string_init_with_value(mutable_string_t *target, const char *value);

/* Memory management routines */
mutable_string_t* mutable_string_resize(mutable_string_t* target, size_t new_size);
void mutable_string_free(mutable_string_t *target);

/* Get info about a string */
int mutable_string_get_length(mutable_string_t *var);
short mutable_string_is_empty(mutable_string_t *var);
char* mutable_string_get_data(mutable_string_t *var);

/* Putting data into the string */
mutable_string_t* mutable_string_assign(mutable_string_t *dest, const char *src);
mutable_string_t* mutable_string_append(mutable_string_t *dest, const char *src);
mutable_string_t* mutable_string_append_mutable_string(mutable_string_t *dest, mutable_string_t *src);
mutable_string_t* mutable_string_append_char(mutable_string_t *dest, char src);

/* Parsing into integers */
int mutable_string_parse_int(mutable_string_t *var);
long mutable_string_parse_long(mutable_string_t *var);
long long mutable_string_parse_long_long(mutable_string_t *var);
double mutable_string_parse_double(mutable_string_t *var);

/* Copy and such */
mutable_string_t* mutable_string_copy(mutable_string_t *dest, mutable_string_t *src);

/* Get bits and pieces of a string */
char mutable_string_char_at(mutable_string_t *subject, int position);
mutable_string_t* mutable_string_substring(
    mutable_string_t *subject,
    mutable_string_t *destination,
    int offset,
    size_t length
    );

/* Find a substring */
mutable_string_reference_t *mutable_string_find(
    mutable_string_t *haystack,
    mutable_string_t *needle,
    mutable_string_reference_t *ref
    );

/* Operate on references */
mutable_string_reference_t *mutable_string_reference_init(mutable_string_reference_t *ref);
void mutable_string_reference_free(mutable_string_reference_t *ref);
char *mutable_string_reference_get_data(mutable_string_reference_t *ref);
int mutable_string_reference_get_length(mutable_string_reference_t *ref);
#define MUTREFSTR(X) mutable_string_reference_get_data(X)

#endif

