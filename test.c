#include <stdio.h>
#include <stdbool.h>

#include "SDL2/SDL.h"
#include "GL/glew.h"
#include "GL/gl.h"

#define SCREEN_HEIGHT 400
#define SCREEN_WIDTH 600

int main(int argc, char **argv)
{
	bool quit = false;
	SDL_Event event;

	fprintf(stderr, "Initializing SDL...\n");
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1) {
		fprintf(stderr, "Initialization failed: %s\n", SDL_GetError());
	       exit(-1);	
	}
	fprintf(stderr, "Initialization successful\n");

	SDL_Window* window = SDL_CreateWindow("SDL Practice", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		fprintf(stderr, "Window creation failed: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_Surface* surface = SDL_GetWindowSurface(window);
	if (surface == NULL) {
		fprintf(stderr, "Surface retrieval failed: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));

	while (!quit) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) 
				quit = true;
		}
		SDL_UpdateWindowSurface(window);
	}

	SDL_DestroyWindow(window);
	SDL_Quit(); fprintf(stderr, "Shutting down SDL...\n");
	return 0;
}
