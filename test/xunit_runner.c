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
#include <fossil/xtest.h>   // basic test tools

XTEST_EXTERN_POOL(basic_group);

//
// XUNIT-RUNNER: running test groups from test files
//
int main(int argc, char **argv) {
    XTEST_CREATE(argc, argv);

    XTEST_IMPORT_POOL(basic_group);

    return XTEST_ERASE();
} // end of func
