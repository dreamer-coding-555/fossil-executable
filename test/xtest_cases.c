/*
==============================================================================
Author: Michael Gene Brockus (Dreamer)
Email: michaelbrockus@gmail.com
Organization: Fossil Logic
Description: 
    This file is part of the Fossil Logic project, where innovation meets
    excellence in software development. Michael Gene Brockus, also known as
    "Dreamer," is a dedicated contributor to this project. For any inquiries,
    feel free to contact Michael at michaelbrockus@gmail.com.
==============================================================================
*/
#include "app.h" // app source code

#include <fossil/xtest.h>   // basic test tools
#include <fossil/xassume.h> // extra asserts
#include <stdlib.h>

//
// XUNIT-CASES: list of test cases testing project features
//
XTEST_CASE(basic_run_of_string) {
    char *one = "Something";
    char *two = "Coffe Cup";
    TEST_ASSUME_EQUAL_CSTRING(one, one);
    TEST_ASSUME_NOT_EQUAL_CSTRING(one, two);
}

XTEST_CASE(basic_run_of_pointer) {
    TEST_ASSUME_NOT_CNULLPTR("Coffee Cup");
    TEST_ASSUME_CNULLPTR(cnull);
}

XTEST_CASE(basic_run_of_boolean) {
    TEST_ASSUME_TRUE(APP_ENABLE);
    TEST_ASSUME_FALSE(APP_DISABLE);
}

//
// XUNIT-GROUP: a group of test cases from the current test file
//
XTEST_DEFINE_POOL(basic_group) {
    XTEST_RUN_UNIT(basic_run_of_string);
    XTEST_RUN_UNIT(basic_run_of_pointer);
    XTEST_RUN_UNIT(basic_run_of_boolean);
} // end of fixture
