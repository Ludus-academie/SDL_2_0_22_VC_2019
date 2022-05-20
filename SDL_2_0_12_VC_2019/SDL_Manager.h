#pragma once
#include <SDL.h>


typedef struct sdl_manager {
	SDL_Window* pWindow;
	SDL_Renderer* pRenderer;
	SDL_Texture* pTexture;
	SDL_Surface* pSurface;
}sdl_manager;


int SDL_Manager_INIT(sdl_manager* p_manager);
void SDL_Manager_FREE(sdl_manager* p_manager);