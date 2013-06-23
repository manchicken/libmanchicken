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

void assert_valid_dynamic_list(dynamic_list_t *list, exitfunc_t* result) {
  if (list->items != NULL && items->item_size == 0) {
    swansong()
  }
}

dynamic_list_t* dynamic_list_init(dynamic_list_t *list, size_t item_size) {
  list->items = (void*)NULL;
  list->item_size = item_size;
  list->count = 0;
  list->size_in_bytes = 0;

  return list;
}

void dynamic_list_free(dynamic_list_t *list) {
  if (list->items != NULL) {
    free(list->items);
  }
  list->item_size = 0;
  list->count = 0;
  list->size_in_bytes = 0;

  return;
}

dynamic_list_t* dynamic_list_resize(dynamic_list_t *list, size_t item_size, size_t num_items);
