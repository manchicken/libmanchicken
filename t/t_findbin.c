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
#include <findbin.h>
#include <mutable_string.h>
#include <CUnit/Basic.h>

#define ADD_TEST(X) do { if (!X) { CU_cleanup_registry();return CU_get_error(); } } while (0)

int init_findbin_suite(void) {
  return 0;
}

int clean_findbin_suite(void) {
  return 0;
}

void t_findbin(void) {
  mutable_string_t subject;
  mutable_string_init(&subject);

  CU_ASSERT_PTR_NOT_NULL(findbin(&subject));
  // fprintf(stderr, "I got output: %s\n", MUTSTR(&subject));
  CU_ASSERT_PTR_NOT_NULL(strstr(MUTSTR(&subject), "t_findbin"));

  mutable_string_free(&subject);
}

/* MAIN */
int main(void) {
  CU_pSuite ste = NULL;

  if (CUE_SUCCESS != CU_initialize_registry()) {
    return CU_get_error();
  }

  ste = CU_add_suite("findbin_suite", init_findbin_suite, clean_findbin_suite);
  if (NULL == ste) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  ADD_TEST(CU_add_test(ste, "Verify findbin()...", t_findbin));

  // CU_console_run_tests();
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_suite(ste);
  CU_basic_show_failures(CU_get_failure_list());
  CU_cleanup_registry();

  printf("\n");

  return CU_get_error();
}
