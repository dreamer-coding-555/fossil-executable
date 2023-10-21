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
#include <SDL.h>

/**
 * Function to run the application with command-line argument parsing.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 * @return 0 if the --help option is detected and help is printed, EXIT_SUCCESS otherwise.
 */
int run_app(int argc, char **argv) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    } // end if

    // Create a window
    SDL_Window* window = SDL_CreateWindow("Hello SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    } // end if

    // Create a renderer for the window
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    } // end if

    bool quit = false;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true; // Exit the loop when the window is closed
            } // end if
        } // end while

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Set the draw color to white
        SDL_RenderClear(renderer); // Clear the screen
        SDL_RenderPresent(renderer); // Present the renderer to the window
    } // end while

    // Cleanup and quit
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
} // end of func
