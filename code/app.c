/*
   File: app.c
   Description: This C source file is part of the Native Meson Build Application, which is a project under the Trilobite Coder Lab.
   
   Author: 
   - Name: Michael Gene Brockus (Dreamer)
   - Email: michaelbrockus@gmail.com
   - Website: https://trilobite.code.blog

   License: This software is released under the Apache License 2.0. Please refer to the LICENSE file for more details.

   Purpose: 
   - This C source file contains the implementation for the Native Meson Build Application.
   - It includes the main logic and functionality required for the application to run.
   - Review and modify this file as needed for your specific project requirements.

   For more information on the Native Meson Build Application and the Trilobite Coder Lab project, please refer to the project documentation and website.
*/
#include "app.h"

/**
 * Function to run the application with command-line argument parsing.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 * @return 0 if the --help option is detected and help is printed, EXIT_SUCCESS otherwise.
 */
int run_app(int argc, char **argv) {
    cstream io;

    if (trilo_xcore_stream_open(&io, "data.txt", "r") == 0) {
        char buffer[256];
        size_t read_count = trilo_xcore_stream_read(&io, buffer, sizeof(char), sizeof(buffer) - 1);
        buffer[read_count] = '\0'; // Null-terminate the string
        printf("Read from file: %s\n", buffer);

        trilo_xcore_stream_close(&io);
    }

    return EXIT_SUCCESS;
} // end of func
