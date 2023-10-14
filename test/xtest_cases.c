/*
   File: xtest_cases.c
   Description: This C test runner file is used for testing the Native Meson Build Application, a project under the Trilobite Coder Lab.
   
   Author: 
   - Name: Michael Gene Brockus (Dreamer)
   - Email: michaelbrockus@gmail.com
   - Website: https://trilobite.code.blog

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

//
// XUNIT-DATA: test data for use in current project test cases
//
XTEST_DATA(ProjectTestData) {
    char *one;
    char *two;
}project_data;

//
// XUNIT-FIXTURE: test fixture for setup/teardown and other tesk
//
XTEST_FIXTURE(project_tests);
XTEST_SETUP(project_tests) {
    project_data.one = "Something";
    project_data.two = "Coffe Cup";
}

XTEST_TEARDOWN(project_tests) {
    // empty
}

//
// XUNIT-CASES: list of test cases testing project features
//
XTEST_CASE_FIXTURE(project_tests, basic_run_of_string) {
    XASSERT_STRING_EQUAL(project_data.one, project_data.one);
    XASSERT_STRING_NOT_EQUAL(project_data.one, project_data.two);
}

XTEST_CASE_FIXTURE(project_tests, basic_run_of_pointer) {
    XASSERT_PTR_NOT_NULL("Coffee Cup");
    XASSERT_PTR_NULL(NULL);
}

XTEST_CASE_FIXTURE(project_tests, basic_run_of_boolean) {
    XASSERT_BOOL_TRUE(true);
    XASSERT_BOOL_FALSE(false);
}

//
// XUNIT-GROUP: a group of test cases from the current test file
//
void basic_group(XUnitRunner *runner) {
    XTEST_RUN_FIXTURE(basic_run_of_string,  project_tests, runner);
    XTEST_RUN_FIXTURE(basic_run_of_pointer, project_tests, runner);
    XTEST_RUN_FIXTURE(basic_run_of_boolean, project_tests, runner);
} // end of fixture
