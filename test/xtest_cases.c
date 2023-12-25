/*
   File: xtest_cases.c
   Description: This C test runner file is used for testing the Native Meson Build Application, a project under the Trilobite Coder Lab.
   
   Author: 
   - Name: Michael Gene Brockus (Dreamer)
   - Email: michaelbrockus@gmail.com
   - Website: https://trilobite.home.blog

   License: This software is released under the Apache License 2.0. Please refer to the LICENSE file for more details.

   Purpose: 
   - This C test runner file is responsible for running unit tests and verifying the correctness of the Native Meson Build Application.
   - It should be used in conjunction with a testing framework or library to ensure the functionality of the application.
   - Customize this file as needed for your specific project's testing requirements.

   For more information on the Native Meson Build Application, the Trilobite Coder Lab project, and the testing framework or library being used, please refer to the relevant project documentation.
*/
#include "app.h" // app source code

#include <trilobite/xtest.h>   // basic test tools
#include <trilobite/xassert.h> // extra asserts
#include <stdlib.h>
#include <stdbool.h>

//
// XUNIT-CASES: list of test cases testing project features
//
XTEST_CASE(basic_run_of_string) {
    char *one = "Something";
    char *two = "Coffe Cup";
    TEST_ASSERT_EQUAL_STRING(one, one);
    TEST_ASSERT_NOT_EQUAL_STRING(one, two);
}

XTEST_CASE(basic_run_of_pointer) {
    TEST_ASSERT_NOT_NULL_PTR("Coffee Cup");
    TEST_ASSERT_NULL_PTR(NULL);
}

XTEST_CASE(basic_run_of_boolean) {
    TEST_ASSERT_TRUE(true);
    TEST_ASSERT_FALSE(false);
}

//
// XUNIT-GROUP: a group of test cases from the current test file
//
XTEST_GROUP_DEFINE(basic_group) {
    XTEST_RUN_UNIT(basic_run_of_string,  runner);
    XTEST_RUN_UNIT(basic_run_of_pointer, runner);
    XTEST_RUN_UNIT(basic_run_of_boolean, runner);
} // end of fixture
