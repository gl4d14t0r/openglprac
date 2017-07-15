#include <stdio.h>
#include <stdbool.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "GL/glew.h"
#include "GL/gl.h"

#define SCREEN_HEIGHT 400
#define SCREEN_WIDTH 600

SDL_Surface* loadSurface(const char *path, SDL_Surface *screen_surface)
{
	SDL_Surface* new_surface = IMG_Load(path);
	
	if (new_surface == NULL) {
		fprintf(stderr, "Unable to load image: %s\n", IMG_GetError());
		exit(EXIT_FAILURE);
	} else
		new_surface = SDL_ConvertSurface(new_surface, screen_surface->format, 0);

	if (new_surface != NULL)
		return new_surface;
	else {
		fprintf(stderr, "Unable to convert surface: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char **argv)
{
	bool quit = false;
	SDL_Event event;

	fprintf(stderr, "Initializing SDL...\n");
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1) {
		fprintf(stderr, "Initialization failed: %s\n", SDL_GetError());
	       exit(EXIT_FAILURE);	
	}
	fprintf(stderr, "Initialization successful\n");

	fprintf(stderr, "Initializing SDL_image...\n");
	if (!(IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG)) {
		fprintf(stderr, "Initialization failed: %s\n", IMG_GetError());
		exit(EXIT_FAILURE);
	}
	fprintf(stderr, "Initialization successful\n");

	SDL_Window* window = SDL_CreateWindow("SDL Practice", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		fprintf(stderr, "Window creation failed: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_Surface* screen_surface = SDL_GetWindowSurface(window);
	if (screen_surface == NULL) {
		fprintf(stderr, "Surface retrieval failed: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	SDL_FillRect(screen_surface, NULL, SDL_MapRGB(screen_surface->format, 0xFF, 0xFF, 0xFF));

	SDL_Surface* image_surface = loadSurface("randomspaceimage.jpg", screen_surface);
	
	SDL_Rect stretch = {
		0,
		0,
		SCREEN_WIDTH,
		SCREEN_HEIGHT
	};

	SDL_BlitScaled(image_surface, NULL, screen_surface, &stretch);

	while (!quit) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) 
				quit = true;
		}
		SDL_UpdateWindowSurface(window);
	}

	SDL_FreeSurface(screen_surface);
	SDL_FreeSurface(image_surface);
	SDL_DestroyWindow(window);
	SDL_Quit(); fprintf(stderr, "Shutting down SDL...\n");
	return 0;
}
