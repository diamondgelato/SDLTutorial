#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "../Tutorial 1-3/HelloWorld.h"

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL,
};


// window for rendering
SDL_Window* window1 = NULL;

// surface contained by the window
SDL_Surface* screenSurface1 = NULL;

// currently displayed image
SDL_Surface* currentSurface = NULL;

// pointer to all images for each keypress
SDL_Surface* keyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];


bool init1() {
	// initialise SDL
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialise: SDLError: %s\n", SDL_GetError());
		success = false;
	}
	else {
		// Create Window
		window1 = SDL_CreateWindow
		("Add window name here",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI
		);

		if (window1 == NULL) {
			printf("Window could not be created, SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else {
			// Initialize PNG loading
			int imgFlags = IMG_INIT_PNG;

			if (!(IMG_Init(imgFlags) & imgFlags)) {
				printf("SDL_image could not initialize. SDL_image Error: %s\n", IMG_GetError());
			}
			else {
				// Get window surface
				screenSurface1 = SDL_GetWindowSurface(window1);
			}
		}
	}

	// return bool to signify whether initialisation has been successful or not 
	// main - close the program if not successful
	return success;
}

SDL_Surface* loadSurface(string path, int imgType) {
	// final optimised image
	SDL_Surface* optimisedSurface = SDL_LoadBMP(path.c_str());

	// load image at a specified path
	SDL_Surface* loadedSurface = NULL;
	switch (imgType)
	{
	case 1:
		loadedSurface = SDL_LoadBMP(path.c_str());
		break;

	case 2:
		loadedSurface = IMG_Load(path.c_str());
		break;

	default:
		loadedSurface = NULL;
		break;
	}

	if (loadedSurface == NULL) {
		printf("unable to load image %s. SDL Error: %s\n", path.c_str(), IMG_GetError());
	}
	else {
		// convert surface to screen format
		optimisedSurface = SDL_ConvertSurface(loadedSurface, screenSurface1->format, 0);

		if (optimisedSurface == NULL) {
			printf("Unable to optimise image %s. SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		// get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return optimisedSurface;
}

bool loadMedia1() {
	// loading success flag
	bool success = true;

	// load splash image
	//keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("04_key_presses/press.bmp");
	keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("TutorialCode/Tutorial 4-6/sample.png", 2);

	if (keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
		//printf("Unable to load image %s! SDL Error: %s\n", "04_key_presses/press.bmp", SDL_GetError());
		printf("Unable to load image %s! SDL Error: %s\n", "TutorialCode/Tutorial 4-6/sample.png", SDL_GetError());
		success = false;
	}

	keyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("Downloads/04_key_presses/up.bmp", 1);

	if (keyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL) {
		printf("Unable to load image %s! SDL Error: %s\n", "Downloads/04_key_presses/up.bmp", SDL_GetError());
		success = false;
	}

	keyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("Downloads/04_key_presses/down.bmp", 1);

	if (keyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL) {
		printf("Unable to load image %s! SDL Error: %s\n", "Downloads/04_key_presses/down.bmp", SDL_GetError());
		success = false;
	}

	keyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("Downloads/04_key_presses/left.bmp", 1);

	if (keyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL) {
		printf("Unable to load image %s! SDL Error: %s\n", "Downloads/04_key_presses/left.bmp", SDL_GetError());
		success = false;
	}

	keyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("Downloads/04_key_presses/right.bmp", 1);

	if (keyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL) {
		printf("Unable to load image %s! SDL Error: %s\n", "Downloads/04_key_presses/right.bmp", SDL_GetError());
		success = false;
	}


	return success;
}

void closeApp1() {
	// Deallocate surface
	/*SDL_FreeSurface(helloWorld);
	helloWorld = NULL;*/

	// Destroy window
	SDL_DestroyWindow(window1);
	window1 = NULL;

	// Quit SDL subsystems
	SDL_Quit();
}

//int main(int argc, char* args[]) {
int KeyPresses() {
	// make the stretched rectangle
	SDL_Rect stretchedRect;
	stretchedRect.x = 0;
	stretchedRect.y = 0;
	stretchedRect.w = SCREEN_WIDTH;
	stretchedRect.h = SCREEN_HEIGHT;

	// Start up SDL and create window
	if (!init1())
		printf("Failed to initialise!\n");
	else {
		// Load media
		if (!loadMedia1()) {
			printf("Failed to load media!\n");
		}
		else {
			// main loop flag
			bool quit = false;

			currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
			// SDL_BlitSurface(currentSurface, NULL, screenSurface1, NULL);
			SDL_BlitScaled(currentSurface, NULL, screenSurface1, &stretchedRect);
			SDL_UpdateWindowSurface(window1);

			// Event handler
			SDL_Event e;

			// while application is running
			while (quit == false)
			{
				// handle events in the queue
				while (SDL_PollEvent(&e))
				{
					// user requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					else if (e.type == SDL_KEYDOWN) {
						// Select surfaces based on type of key press
						switch (e.key.keysym.sym)
						{
						case SDLK_UP:
						case SDLK_w:
							currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_UP];
							break;

						case SDLK_DOWN:
						case SDLK_s:
							currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
							break;

						case SDLK_LEFT:
						case SDLK_a:
							currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
							break;

						case SDLK_RIGHT:
						case SDLK_d:
							currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
							break;

						default:
							currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
							break;
						}
					}
				}

				// apply current surface
				SDL_BlitScaled(currentSurface, NULL, screenSurface1, &stretchedRect);
				// SDL_BlitSurface(currentSurface, NULL, screenSurface1, NULL);

				// update surface
				SDL_UpdateWindowSurface(window1);
			}
		}
	}

	// free resources and close SDl
	closeApp1();

	return 0;
}