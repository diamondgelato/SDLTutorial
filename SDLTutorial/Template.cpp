#include <SDL.h>
#include <stdio.h>


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


// window for rendering
SDL_Window* window = NULL;

// surface contained by the window
SDL_Surface* screenSurface = NULL;

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
		("Add window name here",
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

	// load splash image
	/*helloWorld = SDL_LoadBMP("sample1.bmp");

	if (helloWorld == NULL) {
		printf("Unable to load image %s! SDL Error: %s\n", "sample1.bmp", SDL_GetError());
		success = false;
	}*/

	return success;
}

void closeApp() {
	// Deallocate surface
	/*SDL_FreeSurface(helloWorld);
	helloWorld = NULL;*/

	// Destroy window
	SDL_DestroyWindow(window);
	window = NULL;

	// Quit SDL subsystems
	SDL_Quit();
}

int Template() {
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
			}
		}
	}

	// free resources and close SDl
	closeApp();

	return 0;
}