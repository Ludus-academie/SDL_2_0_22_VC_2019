#include "SDL_Manager.h"
#include <stdio.h>
#include <stdlib.h>

int SDL_Manager_INIT(sdl_manager* p_manager)
{
    int format = 0;
    int access = 0;
    int width = 1280;
    int height = 720;
    int depth = 32;
    //char* bmp_path = "Vierbit4.bmp";

    p_manager->pWindow = SDL_CreateWindow("A SDL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_RESIZABLE); //Create window
    p_manager->pRenderer = SDL_CreateRenderer(p_manager->pWindow, -1, SDL_RENDERER_ACCELERATED);
    p_manager->pSurface = SDL_CreateRGBSurface(0, width, height, depth, 0, 0, 0, 0);
    p_manager->pTexture = SDL_CreateTexture(p_manager->pRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);

    if (p_manager->pWindow == NULL) //errors management
    {
        printf_s("Error creating the window : %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    if (p_manager->pRenderer == NULL) //errors management
    {
        printf("Error creating the renderer : %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

void SDL_Manager_FREE(sdl_manager* p_manager)
{
    SDL_DestroyRenderer(p_manager->pRenderer);
    SDL_DestroyTexture(p_manager->pTexture);
    SDL_FreeSurface(p_manager->pSurface);
    SDL_DestroyWindow(p_manager->pWindow);
}
