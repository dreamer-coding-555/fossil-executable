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
#include "app.h"


// The run_app function is designed to read data from a file named "data.txt"
// using a custom stream implementation (cstream).
// Returns EXIT_SUCCESS if the file is read successfully; otherwise, the
// behavior is undefined.
int run_app(int argc, char **argv) {
    cstream io;

    // Attempt to open the file "data.txt" in read-only mode
    if (fscl_stream_open(&io, "data.txt", "r") == 0) {
        char buffer[256];

        // Read data from the file into the buffer
        size_t read_count = fscl_stream_read(&io, buffer, sizeof(char), sizeof(buffer) - 1);
        buffer[read_count] = '\0'; // Null-terminate the string

        // Print the content of the file
        fscl_console_out("Read from file: %s\n", buffer);

        // Close the file
        fscl_stream_close(&io);
    }

    return EXIT_SUCCESS;
} // end of func
