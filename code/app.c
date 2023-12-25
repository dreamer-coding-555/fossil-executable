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

/*
 * The run_app function is designed to read data from a file named "data.txt"
 * using a custom stream implementation (cstream). It follows these steps:
 *
 * 1. Initializes a cstream object named 'io'.
 * 2. Attempts to open the file "data.txt" in read-only mode.
 * 3. If the file is successfully opened, reads its content into a buffer
 *    (up to 255 characters) using the stream_read function.
 * 4. Null-terminates the buffer to convert it into a valid C string.
 * 5. Prints the content of the file to the standard output.
 * 6. Closes the file using stream_close.
 *
 * Note: The function assumes that the file contains text data and does not
 * handle binary files differently. It also does not handle potential errors
 * during the file operations for simplicity. Consider adding error handling
 * based on the specific requirements of your application.
 *
 * Returns EXIT_SUCCESS if the file is read successfully; otherwise, the
 * behavior is undefined.
 */
int run_app(int argc, char **argv) {
    cstream io;

    // Attempt to open the file "data.txt" in read-only mode
    if (tscl_stream_open(&io, "data.txt", "r") == 0) {
        char buffer[256];

        // Read data from the file into the buffer
        size_t read_count = tscl_stream_read(&io, buffer, sizeof(char), sizeof(buffer) - 1);
        buffer[read_count] = '\0'; // Null-terminate the string

        // Print the content of the file
        tscl_console_out("Read from file: %s\n", buffer);

        // Close the file
        tscl_stream_close(&io);
    }

    return EXIT_SUCCESS;
} // end of func
