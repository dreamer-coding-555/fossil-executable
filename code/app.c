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
    TriloOptionParser* parser = trilo_xcore_parser_create_option_parser();
    
    // Add options for your program here
    trilo_xcore_parser_add_option(parser, "enable_logging", TRILO_BOOL_OPTION, 0, 0, "");
    trilo_xcore_parser_add_option(parser, "threshold", TRILO_INT_OPTION, 0, 100, "");
    trilo_xcore_parser_add_option(parser, "output_file", TRILO_STRING_OPTION, 0, 0, "");
    trilo_xcore_parser_add_option(parser, "auto_mode", TRILO_FEATURE_OPTION, 0, 0, "enable,disable,auto");

    trilo_xcore_parser_process_arguments(parser, argc, argv);

    // Check and use the options
    if (trilo_xcore_parser_has_option(parser, "enable_logging")) {
        printf("Logging is enabled.\n");
    } else {
        printf("Logging is disabled.\n");
    }

    if (trilo_xcore_parser_has_option(parser, "threshold")) {
        int threshold = parser->options[1].int_value;
        printf("Threshold is set to %d.\n", threshold);
    }

    if (trilo_xcore_parser_has_option(parser, "output_file")) {
        const char* outputFile = parser->options[2].str_value;
        printf("Output file is set to '%s'.\n", outputFile);
    }

    if (trilo_xcore_parser_has_option(parser, "auto_mode")) {
        int autoMode = parser->options[3].feature_value;
        if (autoMode == 0) {
            printf("Auto mode is disabled.\n");
        } else if (autoMode == 1) {
            printf("Auto mode is enabled.\n");
        } else {
            printf("Auto mode is set to 'auto'.\n");
        }
    }

    // Clean up
    for (int i = 0; i < parser->num_options; i++) {
        free(parser->options[i].str_value);
    }
    free(parser->options);
    free(parser);
    return EXIT_SUCCESS;
} // end of func