#include <SDL.h>
#include <SDL_image.h>
#include <string>

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

SDL_Window* window3 = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* texture = NULL;

SDL_Texture* loadTexture(string path) {
	// final texture
	SDL_Texture* newTexture = IMG_LoadTexture(
		renderer, path.c_str()
	);

	if (newTexture == NULL) {
		printf("Unable to create texture from %s. SDL Error: %s\n", path.c_str(), SDL_GetError());
	}

	return newTexture;
}

bool init3() {
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialise. SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else {
		// create window
		window3 = SDL_CreateWindow(
			"Texture Rendering",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI
		);

		if (window3 == NULL) {
			printf("Window could not be created. SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else {
			// Create renderer
			renderer = SDL_CreateRenderer(
				window3, -1, SDL_RENDERER_ACCELERATED
			);

			if (renderer == NULL) {
				printf("Renderer could not be created. SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else {
				// initialise renderer colour
				SDL_SetRenderDrawColor(
					renderer, 0xFF, 0xFF, 0xFF, 0xFF
				);

				// initialise PNG loading
				int imgFlags = IMG_INIT_PNG;

				// check if initialisation is successful
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					printf("SDL Image could not initialise. SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia3() {
	// loading success flag
	bool success = true;

	// load PNG texture
	texture = loadTexture("TutorialCode/TextureRendering/sample.png");

	if (texture == NULL) {
		printf("Failed to load texture image\n");
		success = false;
	}

	return success;
}

void close() {
	// Free loaded image
	SDL_DestroyTexture(texture);
	texture = NULL;

	// Destroy window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window3);
	renderer = NULL;
	window3 = NULL;

	// Quit SDL subsystems
	SDL_Quit();
	IMG_Quit();
}

int TextureRendering() {
	if (init3()) {
		if (loadMedia3()) {
			// main loop
			bool quit = false;

			SDL_Event e;

			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0) {
					if (e.type == SDL_QUIT) {
						quit = true;
					}
				}

				// Clear screen (?)
				SDL_RenderClear(renderer);

				// render texture to screen
				SDL_RenderCopy(
					renderer, texture, NULL, NULL
				);

				// update screen
				SDL_RenderPresent(renderer);
			}
		}
	}

	return 0;
}