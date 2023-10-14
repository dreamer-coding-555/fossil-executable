/*
   File: main.c
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

/*
 > Application Foundation Function:
 > This function is considered to be the starting point for applications created
 > and hosted at the Trilobite AppHub.
 > 
 > There should not be a reason for you to touch the
 > main source file; begin your work in the program
 > source file.
 >
 > @param argc The number of command-line arguments.
 > @param argv An array of strings containing the command-line arguments.
 > @return An integer indicating the application's exit status.
 */
extern int run_app(int argc, char **argv);

/*
 > Main Function:
 > This is where program execution starts, and the application foundation function
 > is called, initiating the program's logic.
 >
 > @param argc The number of command-line arguments.
 > @param argv An array of strings containing the command-line arguments.
 > @return An integer indicating the application's exit status.
 */
int main(int argc, char **argv) {
    return run_app(argc, argv);
} // end of func
