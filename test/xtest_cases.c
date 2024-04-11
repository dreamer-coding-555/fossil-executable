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

//
// XUNIT-CASES: list of test cases testing project features
//

XTEST(app_name_case) {
    TEST_ASSUME_EQUAL_CSTRING(FOSSIL_APP_NAME, "My App");
}

XTEST(app_version_case) {
    TEST_ASSUME_EQUAL_CSTRING(FOSSIL_APP_VERSION, "0.1.0");
}

//
// XUNIT-GROUP: a group of test cases from the current test file
//
XTEST_DEFINE_POOL(basic_group) {
    XTEST_RUN_UNIT(app_name_case);
    XTEST_RUN_UNIT(app_version_case);
} // end of fixture
