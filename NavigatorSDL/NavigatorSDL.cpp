#include <SDL.h>
#include <stdio.h>
#include <string>

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;
const int MAP_SIZE = 9;
const int MAP_WIDTH = 3;

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Surface* currentSurface = NULL;
SDL_Surface* surfaceMap[MAP_SIZE];

// functions used
// SDL_Init(), SDL_CreateWindow(), SDL_GetWindowSurface()
bool init() {
	bool success = true;

	// initialise SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialise. SDLError %s\n", SDL_GetError());
		success = false;
	}
	else {
		// Create Window
		window = SDL_CreateWindow
		("Navigator Demo",
			100, 100, SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_ALLOW_HIGHDPI
		);

		if (window == NULL) {
			printf("Window could not be created. SDLError: %s\n",
				SDL_GetError());
			success = false;
		}
		else {
			// get window surface
			screenSurface = SDL_GetWindowSurface(window);
		}

		return success;
	}
}

// functions used
// SDL_LoadBMP(), SDL_ConvertSurface(), SDL_FreeSurface() [get rid of unconverted surface]
SDL_Surface* loadSurface(std::string path) {
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	SDL_Surface* optimisedSurface = NULL;

	if (loadedSurface == NULL) {
		printf("unable to load image. Error %s\n", SDL_GetError());
	}
	else {
		// convert surface to screen format
		optimisedSurface = SDL_ConvertSurface(
			loadedSurface, screenSurface->format, 0
		);

		if (optimisedSurface == NULL) {
			printf("unable to optimise image. Error %s\n", SDL_GetError());
		}

		SDL_FreeSurface(loadedSurface);
		//loadedSurface = NULL;
	}

	return optimisedSurface;
	//return loadedSurface;
}

// functions used
// loadSurface() - local
bool loadMedia() {
	bool success = true;

	for (int i = 0; i < MAP_SIZE; i++)
	{
		std::string path = "Images/" + std::to_string(i + 1) + ".bmp";

		surfaceMap[i] = loadSurface(path);

		if (surfaceMap[i] == NULL) {
			printf("Unable to load image %s. Error %s\n", path.c_str(), SDL_GetError());
			success = false;
		}
	}

	return success;
}

// functions used
// SDL_DestroyWindow(), SDL_Quit()
void closeApp() {
	// Deallocate surfaces
	SDL_FreeSurface(currentSurface);
	currentSurface = NULL;

	// Destroy window
	SDL_DestroyWindow(window);
	window = NULL;

	// Quit SDL subsystems
	SDL_Quit();
}

// calculate the image to be shown next
void GetImageOnKeyDown(int newX, int newY) {
	currentSurface = surfaceMap[newY * MAP_WIDTH + newX];
}

int NavigatorMain() {
	int xPos = 1;
	int yPos = 1;

	SDL_Rect screenRect;
	screenRect.x = 0;
	screenRect.y = 0;
	screenRect.w = SCREEN_WIDTH;
	screenRect.h = SCREEN_HEIGHT;

	// start SDL and create window
	if (init()) {
		if (loadMedia()) {

			// show initial image
			GetImageOnKeyDown(xPos, yPos);
			SDL_BlitScaled(currentSurface, NULL, screenSurface, &screenRect);
			SDL_UpdateWindowSurface(window);

			// main loop flag
			bool quit = false;

			// event handler
			SDL_Event e;

			// main loop - if application is running
			while (quit == false) {

				// get event from queue
				while (SDL_PollEvent(&e)) {

					// if user clicks x button
					if (e.type == SDL_QUIT) {
						quit = true;
					}
					else if (e.type == SDL_KEYDOWN) {
						switch (e.key.keysym.sym)
						{
						case SDLK_UP:
						case SDLK_w:
							yPos -= 1;

							if (yPos < 0)
								yPos = 0;

							GetImageOnKeyDown(xPos, yPos);
							break;

						case SDLK_DOWN:
						case SDLK_s:
							yPos += 1;

							if (yPos > MAP_WIDTH - 1)
								yPos = MAP_WIDTH - 1;

							GetImageOnKeyDown(xPos, yPos);
							break;

						case SDLK_LEFT:
						case SDLK_a:
							xPos -= 1;

							if (xPos < 0)
								xPos = 0;

							GetImageOnKeyDown(xPos, yPos);
							break;

						case SDLK_RIGHT:
						case SDLK_d:
							xPos += 1;

							if (xPos > MAP_WIDTH - 1)
								xPos = MAP_WIDTH - 1;

							GetImageOnKeyDown(xPos, yPos);
							break;

						default:
							break;
						}
					}
				}

				SDL_BlitScaled(currentSurface, NULL, screenSurface, &screenRect);
				SDL_UpdateWindowSurface(window);
			}
		}
		else {
			printf("couldn't load media");
		}
	}
	else {
		printf("couldn't initialise");
	}

	// close properly
	closeApp();

	return 0;
}
