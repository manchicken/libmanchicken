/*
 * Copyright (c) 2013, Michael D. Stemle, Jr.
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

#ifndef __DYNAMIC_LIST_H__
#define __DYNAMIC_LIST_H__

#include <stddef.h>

typedef struct {
  void **items;
  size_t item_size;
  size_t count_allocated;
  size_t count;
  size_t size_in_bytes;
} dynamic_list_t;

typedef void(*dynamic_list_foreach_func_t)(void*);

void assert_valid_dynamic_list(dynamic_list_t *list, exitfunc_t result);

dynamic_list_t* dynamic_list_init(dynamic_list_t *list, size_t item_size);
dynamic_list_t* dynamic_list_init_with_capacity(dynamic_list_t *list, size_t item_size, size_t num_items);
void dynamic_list_free(dynamic_list_t *list);

dynamic_list_t* dynamic_list_resize(dynamic_list_t *list, size_t num_items);
dynamic_list_t* dynamic_list_append(dynamic_list_t *list, void *item);
void* dynamic_list_get_item(dynamic_list_t *list, unsigned int index);
void dynamic_list_foreach(dynamic_list_t *list, dynamic_list_foreach_func_t foreach);

/* Sorting! */
void dynamic_list_swap(dynamic_list_t *list, unsigned int first, unsigned int second);
void dynamic_list_bubble_sort(dynamic_list_t *list, short(*compare)(void*,void*));
void dynamic_list_insertion_sort(dynamic_list_t *list, short(*compare)(void*,void*));

#define dynamic_list_count(DLIST_PTR)     ((DLIST_PTR)->count)
#define dynamic_list_size(DLIST_PTR)      ((DLIST_PTR)->size_in_bytes)
#define dynamic_list_capacity(DLIST_PTR)  ((DLIST_PTR)->count_allocated)
#define dynamic_list_item_size(DLIST_PTR) ((DLIST_PTR)->item_size)

#endif /* __DYNAMIC_LIST_H__ */

