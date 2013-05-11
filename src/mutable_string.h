/*
 * libmanchicken - Copyright (C) 2012 Michael D. Stemle, Jr.
 *
 * This file is part of libmanchicken.
 *
 * libmanchicken is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libmanchicken is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libmanchicken. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __MUTABLE_STRING_H__
#define __MUTABLE_STRING_H__

#ifndef INITIAL_MUTABLE_STRING_ALLOCATION
	#define INITIAL_MUTABLE_STRING_ALLOCATION	64
#endif

#ifndef MAXIMUM_MUTABLE_STRING_SIZE
// 10MiB is big enough
	#define MAXIMUM_MUTABLE_STRING_SIZE			(10 * 1024 * 1024)
#endif

#include <string.h>

typedef struct {
	char *data;
	size_t _data_size;
	int length;
	char is_empty;
} mutable_string_t;
#define MUTSTR(X) mutable_string_get_data(X)
#define MUTLEN(X) mutable_string_get_length(X)

mutable_string_t* mutable_string_init(mutable_string_t *target);
mutable_string_t* mutable_string_init_with_value(mutable_string_t *target, const char *value);
mutable_string_t* mutable_string_resize(mutable_string_t* target, size_t new_size);
void mutable_string_free(mutable_string_t *target);

mutable_string_t* mutable_string_assign(mutable_string_t *dest, const char *src);
mutable_string_t* mutable_string_append(mutable_string_t *dest, const char *src);

int mutable_string_get_length(mutable_string_t *var);
short mutable_string_is_empty(mutable_string_t *var);
char* mutable_string_get_data(mutable_string_t *var);
mutable_string_t* mutable_string_copy(mutable_string_t *dest, mutable_string_t *src);

#endif