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

#include <errno.h>
#include <stdio.h>

#include <manchicken.h>
#include <CUnit/Basic.h>

#define ADD_TEST(X) do { if (!X) { CU_cleanup_registry();return CU_get_error(); } } while (0)

int init_dlist_suite(void) {
  return 0;
}

int clean_dlist_suite(void) {
  return 0;
}

int exited_with = 0;
extern int errno;

void my_exit(int code) {
  exited_with = code;
}

void t_allocation(void) {
  dynamic_list_t my_list;
  dynamic_list_t my_big_list;
  size_t dummy_size = 42;
  size_t dummy_count = 16;
  size_t dummy_bytes = (dummy_size * dummy_count);

  // Without capacity
  CU_ASSERT_PTR_NOT_NULL(dynamic_list_init(&my_list, dummy_size));
  CU_ASSERT_EQUAL(dynamic_list_item_size(&my_list), dummy_size);
  CU_ASSERT_EQUAL(dynamic_list_count(&my_list), 0);
  CU_ASSERT_EQUAL(dynamic_list_capacity(&my_list), 0);
  CU_ASSERT_EQUAL(dynamic_list_size(&my_list), 0);

  // With capacity
  CU_ASSERT_PTR_NOT_NULL(dynamic_list_init_with_capacity(&my_big_list, dummy_size, dummy_count));
  CU_ASSERT_EQUAL(dynamic_list_item_size(&my_big_list), dummy_size);
  CU_ASSERT_EQUAL(dynamic_list_count(&my_big_list), 0);
  CU_ASSERT_EQUAL(dynamic_list_capacity(&my_big_list), dummy_count);
  CU_ASSERT_EQUAL(dynamic_list_size(&my_big_list), dummy_bytes);

  CU_ASSERT_PTR_NOT_NULL(dynamic_list_resize(&my_list, dummy_count));
  CU_ASSERT_EQUAL(dynamic_list_item_size(&my_list), dummy_size);
  CU_ASSERT_EQUAL(dynamic_list_count(&my_list), 0);
  CU_ASSERT_EQUAL(dynamic_list_capacity(&my_list), dummy_count);
  CU_ASSERT_EQUAL(dynamic_list_size(&my_list), dummy_bytes);

  // Clean up
  dynamic_list_free(&my_list);
  CU_ASSERT_PTR_NULL(my_list.items);
  dynamic_list_free(&my_big_list);
  CU_ASSERT_PTR_NULL(my_big_list.items);
}

void printer_str(void *data) {
  char *foo = (char*)data;

  printf("%s\n", foo);
}

void t_append(void) {
  dynamic_list_t my_list;
  char foo1[10];
  char foo2[10];
  char foo3[10];

  dynamic_list_init(&my_list, sizeof(char[10]));

  strcpy(foo1, "foo1");
  dynamic_list_append(&my_list, (void*)foo1);

  strcpy(foo2, "foo2");
  dynamic_list_append(&my_list, (void*)foo2);

  strcpy(foo3, "foo3");
  dynamic_list_append(&my_list, (void*)foo3);

  dynamic_list_foreach(&my_list, printer_str);

  char *foo_out = dynamic_list_get_item(&my_list, 1);
  fprintf(stderr, "I got back '%s'\n", foo_out);
  CU_ASSERT_STRING_EQUAL(foo_out, "foo2");
  CU_ASSERT_EQUAL(dynamic_list_size(&my_list), (sizeof(char[10])*3));
 
  dynamic_list_free(&my_list);
}

/* MAIN */
int main(void) {
  CU_pSuite ste = NULL;

  if (CUE_SUCCESS != CU_initialize_registry()) {
    return CU_get_error();
  }

  ste = CU_add_suite("dlist_suite", init_dlist_suite, clean_dlist_suite);
  if (NULL == ste) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  ADD_TEST(CU_add_test(ste, "Verify memory allocation...", t_allocation));
  ADD_TEST(CU_add_test(ste, "Verify append...", t_append));

  // CU_console_run_tests();
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_suite(ste);
  CU_basic_show_failures(CU_get_failure_list());
  CU_cleanup_registry();

  printf("\n");

  return CU_get_error();
}
