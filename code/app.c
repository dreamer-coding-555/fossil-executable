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
#include <SDL_ttf.h>

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

    // Initialize SDL_ttf for rendering text
    if (TTF_Init() != 0) {
        printf("SDL_ttf initialization failed: %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    } // end if

    // Load a font
    TTF_Font* font = TTF_OpenFont("data/font.ttf", 24);
    if (font == NULL) {
        printf("Font loading failed: %s\n", TTF_GetError());
        TTF_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    } // end if

    bool quit = false;
    SDL_Event event;

    // Open and read the data file
    TriloStream file;
    if (trilo_xcore_stream_open(&file, "data/data.txt", "r") == -1) {
        printf("Failed to open the data file\n");
        return EXIT_FAILURE;
    } // end if

    char buffer[256];
    size_t bytesRead = trilo_xcore_stream_read(&file, buffer, sizeof(letter), sizeof(buffer));
    trilo_xcore_stream_close(&file);

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } // end if
        } // end while

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Render the text from the data file
        SDL_Color text_color = { 0, 0, 0, 255 };
        SDL_Surface* text_surface = TTF_RenderText_Solid(font, buffer, text_color);
        SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);

        SDL_Rect text_rect;
        text_rect.x = 200;
        text_rect.y = 300;
        SDL_QueryTexture(text_texture, NULL, NULL, &text_rect.w, &text_rect.h);

        SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);
        SDL_RenderPresent(renderer);

        SDL_FreeSurface(text_surface);
        SDL_DestroyTexture(text_texture);

        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                quit = true;
            } // end if
        } // end if
    } // end while

    // Cleanup and quit
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
    return EXIT_SUCCESS;
} // end of func
