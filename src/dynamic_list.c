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

#include <stdio.h>
#include <stdlib.h>

#include <swansong.h>
#include <dynamic_list.h>

/*
typedef struct {
  void *items;
  size_t item_size;
  size_t count;
  size_t size_in_bytes;
} dynamic_list_t;
*/

void assert_valid_dynamic_list(dynamic_list_t *list, exitfunc_t result) {
  if (list->items != NULL && list->item_size == 0) {
    swansong("Invalid dynamic_list instance, has not-NULL items, but has size. Did you init?", result);
  }

  return;
}

dynamic_list_t* dynamic_list_init(dynamic_list_t *list, size_t item_size) {
  list->items = (void**)NULL;
  list->item_size = item_size;
  list->count_allocated = 0;
  list->count = 0;
  list->size_in_bytes = 0;

  return list;
}

dynamic_list_t* dynamic_list_init_with_capacity(dynamic_list_t *list, size_t item_size, size_t num_items) {
  if (dynamic_list_init(list, item_size) == NULL) {
    return NULL;
  }

  return dynamic_list_resize(list, num_items);
}

void dynamic_list_free(dynamic_list_t *list) {
  if (list->items != NULL) {
    free(list->items);
    list->items = NULL;
  }
  list->item_size = 0;
  list->count_allocated = 0;
  list->count = 0;
  list->size_in_bytes = 0;

  return;
}

dynamic_list_t* dynamic_list_resize(dynamic_list_t *list, size_t num_items) {
  assert_valid_dynamic_list(list, SWANSONG_FATAL);

  if (list->count_allocated == num_items) {
    return list;
  }

  size_t to_allocate = (list->item_size * num_items);
  // Wheels fell off if the sizes still match but item counts don't...
  if (list->item_size == 0) {
    swansong("Cannot have zero-length item sizes!", SWANSONG_FATAL);
  }
  if (list->size_in_bytes == to_allocate) {
    fprintf(stderr, "Item size == %ld and to_allocate == %ld\n", list->item_size, to_allocate);
    swansong("Allocated size is the same as calculated allocated size, but item counts are mismatched!", SWANSONG_FATAL);
  }

  // Allocate
  list->items = (void**)realloc(list->items, to_allocate);

  // Handle failed allocation...
  if (!list->items) {
    swansong_err("Failed to reallocate items list", SWANSONG_FATAL);
    dynamic_list_free(list);
  }

  list->count_allocated = num_items;
  list->size_in_bytes = to_allocate;

  return list;
}

dynamic_list_t* dynamic_list_append(dynamic_list_t *list, void *item) {
  size_t new_count = dynamic_list_count(list) + 1;
  fprintf(stderr, "allocating from %ld to %ld!\n", dynamic_list_count(list), new_count);
  if (!dynamic_list_resize(list, new_count)) {
    return NULL;
  }
  fprintf(stderr, "Done allocating!");

  list->items[new_count-1] = item;
  list->count += 1;
  
  return list;
}

void* dynamic_list_get_item(dynamic_list_t *list, unsigned int index) {
  if (index > dynamic_list_count(list)) {
    swansong("Warning: Went outside of boundaries in dynamic_list_get_item()", SWANSONG_NONFATAL);
    return NULL;
  }

  return list->items[index];
}

void dynamic_list_foreach(dynamic_list_t *list, dynamic_list_foreach_func_t foreach) {
  size_t idx = 0;

  for (idx = 0; idx < dynamic_list_count(list); idx += 1) {
    (*foreach)(list->items[idx]);
  }
}