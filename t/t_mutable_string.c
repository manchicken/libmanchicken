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
#include <string.h>
#include <stdlib.h>
#include <manchicken.h>

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
// #include <CUnit/Console.h>

#define TEST_STR_1              "This is a test"
#define TEST_STR_TRUNC          "This is"
#define TEST_STR_TRUNC_LEN      (strlen(TEST_STR_TRUNC)+1)
#define TEST_APPEND_HEAD        "AB"
#define TEST_APPEND_TAIL        "CD"
#define TEST_APPEND_WHOLE       "ABCD"
#define TEST_APPEND_CHAR        'C'
#define TEST_APPEND_CHAR_WHOLE  "ABC"

#define ADD_TEST(X) do { if (!X) { CU_cleanup_registry();return CU_get_error(); } } while (0)

int init_mutable_string_suite(void) {
  fprintf(stderr, "HERE!!! Suite Initted!\n");
  return 0;
}

int clean_mutable_string_suite(void) {
  fprintf(stderr, "HERE!!! Suite Cleaned!\n");
  return 0;
}

/* TESTS */
void t_mutable_string_init(void) {
  mutable_string_t a;

  CU_ASSERT_PTR_NOT_NULL(mutable_string_init(&a));
  mutable_string_free(&a);
}

void t_mutable_string_init_with_value(void) {
  mutable_string_t a;

  CU_ASSERT_PTR_NOT_NULL(
    mutable_string_init_with_value(
      &a, TEST_STR_1
    )
  );
  CU_ASSERT_STRING_EQUAL(
    MUTSTR(&a),
    TEST_STR_1
  );

  mutable_string_free(&a);
}

void t_mutable_string_resize(void) {
  mutable_string_t a;

  CU_ASSERT_PTR_NOT_NULL(
    mutable_string_init_with_value(
      &a, TEST_STR_1
    )
  );
  CU_ASSERT_STRING_EQUAL(
    MUTSTR(&a),
    TEST_STR_1
  );

  CU_ASSERT_PTR_NOT_NULL(
    mutable_string_resize(&a, TEST_STR_TRUNC_LEN));

  CU_ASSERT_STRING_EQUAL(
    MUTSTR(&a),
    TEST_STR_TRUNC
  );

  mutable_string_free(&a);  
}

void t_mutable_string_assign(void) {
  mutable_string_t a;

  CU_ASSERT_PTR_NOT_NULL(
    mutable_string_init(
      &a
    )
  );
  CU_ASSERT_EQUAL(
    mutable_string_get_length(&a),
    0
  );

  CU_ASSERT_PTR_NOT_NULL(
    mutable_string_assign(
      &a,
      TEST_STR_1
    )
  );

  CU_ASSERT_STRING_EQUAL(
    MUTSTR(&a),
    TEST_STR_1
  );

  CU_ASSERT_PTR_NOT_NULL(
    mutable_string_assign(
      &a,
      TEST_STR_TRUNC
    )
  );

  CU_ASSERT_STRING_EQUAL(
    MUTSTR(&a),
    TEST_STR_TRUNC
  );

  mutable_string_free(&a);  
}

void t_mutable_string_append(void) {
  mutable_string_t a;

  CU_ASSERT_PTR_NOT_NULL(
    mutable_string_init(
      &a
    )
  );

  CU_ASSERT_EQUAL(
    mutable_string_get_length(&a),
    0
  );

  CU_ASSERT_PTR_NOT_NULL(
    mutable_string_assign(
      &a,
      TEST_APPEND_HEAD
    )
  );

  CU_ASSERT_STRING_EQUAL(
    MUTSTR(&a),
    TEST_APPEND_HEAD
  );

  CU_ASSERT_PTR_NOT_NULL(
    mutable_string_append(
      &a,
      TEST_APPEND_TAIL
    )
  );

  CU_ASSERT_STRING_EQUAL(
    MUTSTR(&a),
    TEST_APPEND_WHOLE
  );

  mutable_string_free(&a);  
}

void t_mutable_string_copy(void) {
  mutable_string_t a;
  mutable_string_t b;

  CU_ASSERT_PTR_NOT_NULL(mutable_string_init(&a));
  CU_ASSERT_PTR_NOT_NULL(mutable_string_init(&b));

  CU_ASSERT_PTR_NOT_NULL(mutable_string_assign(&a, TEST_STR_1));
  CU_ASSERT_PTR_NOT_NULL(mutable_string_assign(&b, TEST_APPEND_WHOLE));

  CU_ASSERT_STRING_EQUAL(MUTSTR(&a), TEST_STR_1);
  CU_ASSERT_STRING_EQUAL(MUTSTR(&b), TEST_APPEND_WHOLE);

  CU_ASSERT_PTR_NOT_NULL(mutable_string_copy(&b, &a));

  CU_ASSERT_STRING_EQUAL(MUTSTR(&a), TEST_STR_1);
  CU_ASSERT_STRING_EQUAL(MUTSTR(&b), TEST_STR_1);

  mutable_string_free(&a);
  mutable_string_free(&b);
}

void t_mutable_string_append_mutable_string(void) {
  mutable_string_t a;
  mutable_string_t b;

  CU_ASSERT_PTR_NOT_NULL(
    mutable_string_init(
      &a
    )
  );

  CU_ASSERT_PTR_NOT_NULL(
    mutable_string_init_with_value(
      &b, TEST_APPEND_TAIL
    )
  );

  CU_ASSERT_EQUAL(
    mutable_string_get_length(&a),
    0
  );

  CU_ASSERT_PTR_NOT_NULL(
    mutable_string_assign(
      &a,
      TEST_APPEND_HEAD
    )
  );

  CU_ASSERT_STRING_EQUAL(
    MUTSTR(&a),
    TEST_APPEND_HEAD
  );

  CU_ASSERT_PTR_NOT_NULL(
    mutable_string_append_mutable_string(
      &a,
      &b
    )
  );

  CU_ASSERT_STRING_EQUAL(
    MUTSTR(&a),
    TEST_APPEND_WHOLE
  );

  mutable_string_free(&a);
  mutable_string_free(&b);
}

void t_mutable_string_append_char(void) {
  mutable_string_t a;

  CU_ASSERT_PTR_NOT_NULL(
    mutable_string_init(
      &a
    )
  );

  CU_ASSERT_EQUAL(
    mutable_string_get_length(&a),
    0
  );

  CU_ASSERT_PTR_NOT_NULL(
    mutable_string_assign(
      &a,
      TEST_APPEND_HEAD
    )
  );

  CU_ASSERT_STRING_EQUAL(
    MUTSTR(&a),
    TEST_APPEND_HEAD
  );

  CU_ASSERT_PTR_NOT_NULL(
    mutable_string_append_char(
      &a,
      TEST_APPEND_CHAR
    )
  );

  CU_ASSERT_STRING_EQUAL(
    MUTSTR(&a),
    TEST_APPEND_CHAR_WHOLE
  );

  mutable_string_free(&a);
}

void t_mutable_string_char_at(void) {
  fprintf(stderr, "t_mutable_string_char_at\n");
  mutable_string_t a;

  CU_ASSERT_PTR_NOT_NULL(
    mutable_string_init(
      &a
    )
  );

  CU_ASSERT_EQUAL(
    mutable_string_get_length(&a),
    0
  );

  CU_ASSERT_PTR_NOT_NULL(
    mutable_string_assign(
      &a,
      TEST_APPEND_WHOLE
    )
  );

  CU_ASSERT_EQUAL(
    mutable_string_char_at(&a, 2),
    'C'
  );

  CU_ASSERT_EQUAL(
    mutable_string_char_at(&a, -1),
    'D'
  );

  CU_ASSERT_EQUAL(
    mutable_string_char_at(&a, -4),
    'A'
  );

  CU_ASSERT_EQUAL(
    mutable_string_char_at(&a, -5),
    0
  );

  CU_ASSERT_EQUAL(
    mutable_string_get_error(),
    MUTABLE_STRING_ERROR_OUT_OF_RANGE
  );

  mutable_string_free(&a);
}

/* MAIN */
int main(void) {
  fprintf(stderr, "I'm here!\n");
  CU_pSuite ste = NULL;

  if (CUE_SUCCESS != CU_initialize_registry()) {
    return CU_get_error();
  }

  ste = CU_add_suite("mutable_string_suite", init_mutable_string_suite, clean_mutable_string_suite);
  if (NULL == ste) {
    CU_cleanup_registry();
    return CU_get_error();
  }
  if (CU_get_error() != CUE_SUCCESS) {
    fprintf(stderr, "Error creating suite: (%d)%s\n", CU_get_error(), CU_get_error_msg());
  }

  ADD_TEST(CU_add_test(ste, "Verify mutable_string_init()...", t_mutable_string_init));
  ADD_TEST(CU_add_test(ste, "Verify mutable_string_init_with_value()...", t_mutable_string_init_with_value));
  ADD_TEST(CU_add_test(ste, "Verify mutable_string_resize()...", t_mutable_string_resize));
  ADD_TEST(CU_add_test(ste, "Verify mutable_string_assign()...", t_mutable_string_assign));
  ADD_TEST(CU_add_test(ste, "Verify mutable_string_append()...", t_mutable_string_append));
  ADD_TEST(CU_add_test(ste, "Verify mutable_string_copy()...", t_mutable_string_copy));
  ADD_TEST(CU_add_test(ste, "Verify mutable_string_append_mutable_string()...", t_mutable_string_append_mutable_string));
  ADD_TEST(CU_add_test(ste, "Verify mutable_string_append_char()...", t_mutable_string_append_char));
  ADD_TEST(CU_add_test(ste, "Verify mutable_string_char_at()...", t_mutable_string_char_at));
  // if (CU_get_error() != CUE_SUCCESS) {
    fprintf(stderr, "Error creating suite: (%d)%s\n", CU_get_error(), CU_get_error_msg());
  // }

  // CU_console_run_tests();
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_ErrorCode run_errors = CU_basic_run_suite(ste);
  if (run_errors != CUE_SUCCESS) {
    fprintf(stderr, "Error running tests: (%d)%s\n", run_errors, CU_get_error_msg());
  }

  CU_basic_show_failures(CU_get_failure_list());
  CU_cleanup_registry();

  printf("\n");
  printf("I'm done!\n");

  return CU_get_error();
}
