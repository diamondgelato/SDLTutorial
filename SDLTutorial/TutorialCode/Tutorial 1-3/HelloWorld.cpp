#include <SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//// start SDL and create window
//bool init();

//// load media
//bool loadMedia();

//// free media and shut down SDL
//void closeApp();

//int HelloWorld();


// window for rendering
SDL_Window* window = NULL;

// surface contained by the window
SDL_Surface* screenSurface = NULL;

// image to show after quit
SDL_Surface* XOut = NULL;

bool init() {
	// initialise SDL
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialise: SDLError: %s\n", SDL_GetError());
		success = false;
	}
	else {
		// Create Window
		window = SDL_CreateWindow
		("SDL 1",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI
		);

		if (window == NULL) {
			printf("Window could not be created, SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else {
			// Get window surface
			screenSurface = SDL_GetWindowSurface(window);
		}
	}

	return success;
}

bool loadMedia() {
	// loading success flag
	bool success = true;

	XOut = SDL_LoadBMP("TutorialCode/Tutorial 1-3/x.bmp");

	if (XOut == NULL) {
		printf("Unable to load image %s! SDL Error: %s\n", "TutorialCode/Tutorial 1-3/x.bmp", SDL_GetError());
		success = false;
	}

	return success;
}

void closeApp() {
	// Deallocate surface
	SDL_FreeSurface(XOut);
	XOut = NULL;

	// Destroy window
	SDL_DestroyWindow(window);
	window = NULL;

	// Quit SDL subsystems
	SDL_Quit();
}

int HelloWorld() {
	// Start up SDL and create window
	if (!init())
		printf("Failed to initialise!\n");
	else {
		// Load media
		if (!loadMedia()) {
			printf("Failed to load media!\n");
		}
		else {
			// main loop flag
			bool quit = false;

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
						quit = true;
				}

				// apply new image
				SDL_BlitSurface(XOut, NULL, screenSurface, NULL);

				// update the surface
				SDL_UpdateWindowSurface(window);
			}
		}
	}

	// free resources and close SDl
	closeApp();

	return 0;
}