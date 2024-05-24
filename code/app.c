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

/**
 * Entry point for the FossilApp.
 * Initializes the FossilApp structure with the provided name, argc, and argv,
 * then calls the main app code function to start the app.
 *
 * @param name The name of the application.
 * @param argc The number of command-line arguments.
 * @param argv An array of command-line arguments.
 * @return     The result of the app code execution.
 */
int fossil_app_main(int argc, char **argv) {
    cstream io;  // Declare a cstream structure for file I/O

    // Attempt to open the file "data.txt" in read-only mode
    if (fscl_stream_open(&io, "data.txt", "r") == 0) {
        char buffer[256];  // Declare a buffer to store file content

        // Read data from the file into the buffer
        size_t read_count = fscl_stream_read(&io, buffer, sizeof(char), sizeof(buffer) - 1);
        
        // Null-terminate the string
        buffer[read_count] = cterminator;

        // Print the content of the file to the console
        fscl_console_out("Read from file: f{str}\n", buffer);

        // Close the file
        fscl_stream_close(&io);
    }
    return FSCL_SUCCESS;
} // end of func
