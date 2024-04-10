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
 * Main code function for the FossilApp.
 * Opens and reads the "data.txt" file, then prints its content to the console.
 *
 * @param app Pointer to the FossilApp structure.
 * @return    FSCL_SUCCESS if the operation succeeds, an error code otherwise.
 */
int fossil_app_code(FossilApp *app) {
    cstream io;  // Declare a cstream structure for file I/O

    // Attempt to open the file "data.txt" in read-only mode
    if (fscl_stream_open(&io, "data.txt", "r") == 0) {
        char buffer[256];  // Declare a buffer to store file content

        // Read data from the file into the buffer
        size_t read_count = fscl_stream_read(&io, buffer, sizeof(char), sizeof(buffer) - 1);
        
        // Null-terminate the string
        buffer[read_count] = '\0';

        // Print the content of the file to the console
        fscl_console_out("Read from file: %s\n", buffer);

        // Close the file
        fscl_stream_close(&io);
    }

    return FSCL_SUCCESS;  // Return success code
} // end of func

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
int fossil_app_entry(char *name, int argc, char **argv) {
    // Create a new instance of the FossilApp structure
    FossilApp app;

    // Print a message to the console indicating the app entry point initialization
    fscl_console_puts("Init app entry point");

    // Initialize the FossilApp structure with the provided parameters
    app.name = name;    // Set the app name
    app.argc = argc;    // Set the number of command-line arguments
    app.argv = argv;    // Set the command-line arguments

    // Call the main app code function with the initialized FossilApp structure
    return fossil_app_code(&app);
} // end of func
