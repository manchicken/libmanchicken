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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mutable_string.h>

#include <CUnit/Basic.h>
// #include <CUnit/Console.h>

#define TEST_STR_1              "This is a test"
#define TEST_STR_TRUNC          "This is"
#define TEST_STR_TRUNC_LEN      (strlen(TEST_STR_TRUNC)+1)
#define TEST_APPEND_HEAD        "AB"
#define TEST_APPEND_TAIL        "CD"
#define TEST_APPEND_WHOLE       "ABCD"

#define ADD_TEST(X) do { if (!X) { CU_cleanup_registry();return CU_get_error(); } } while (0)

int init_mutable_string_suite(void) {
  return 0;
}

int clean_mutable_string_suite(void) {
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

/* MAIN */
int main(void) {
  CU_pSuite ste = NULL;

  if (CUE_SUCCESS != CU_initialize_registry()) {
    return CU_get_error();
  }

  ste = CU_add_suite("mutable_string_suite", init_mutable_string_suite, clean_mutable_string_suite);
  if (NULL == ste) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  ADD_TEST(CU_add_test(ste, "Verify mutable_string_init()...", t_mutable_string_init));
  ADD_TEST(CU_add_test(ste, "Verify mutable_string_init_with_value()...", t_mutable_string_init_with_value));
  ADD_TEST(CU_add_test(ste, "Verify mutable_string_resize()...", t_mutable_string_resize));
  ADD_TEST(CU_add_test(ste, "Verify mutable_string_assign()...", t_mutable_string_assign));
  ADD_TEST(CU_add_test(ste, "Verify mutable_string_append()...", t_mutable_string_append));
  ADD_TEST(CU_add_test(ste, "Verify mutable_string_copy()...", t_mutable_string_copy));

  // CU_console_run_tests();
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_suite(ste);
  CU_basic_show_failures(CU_get_failure_list());
  CU_cleanup_registry();

  printf("\n");

  return CU_get_error();
}