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
#include <manchicken.h>
#include <CUnit/Basic.h>

#define ADD_TEST(X) do { if (!X) { CU_cleanup_registry();return CU_get_error(); } } while (0)

int init_swansong_suite(void) {
  return 0;
}

int clean_swansong_suite(void) {
  return 0;
}

int exited_with = 0;

void my_exit(int code) {
  exited_with = code;
}

void t_swansong(void) {
  swansong("This is a test!", SWANSONG_NONFATAL);
  CU_ASSERT_EQUAL(exited_with, 0);
  swansong("This is a \"fatal\" test!", &my_exit);
  CU_ASSERT_EQUAL(exited_with, -1);
}

/* MAIN */
int main(void) {
  CU_pSuite ste = NULL;

  if (CUE_SUCCESS != CU_initialize_registry()) {
    return CU_get_error();
  }

  ste = CU_add_suite("swansong_suite", init_swansong_suite, clean_swansong_suite);
  if (NULL == ste) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  ADD_TEST(CU_add_test(ste, "Verify swansong()...", t_swansong));

  // CU_console_run_tests();
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_suite(ste);
  CU_basic_show_failures(CU_get_failure_list());
  CU_cleanup_registry();

  printf("\n");

  return CU_get_error();
}
