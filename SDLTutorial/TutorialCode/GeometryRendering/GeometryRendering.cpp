#include <SDL.h>
#include <stdio.h>


const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;


SDL_Window* window4 = NULL;
SDL_Renderer* renderer1 = NULL;

bool init4() {
	// initialise SDL
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialise: SDLError: %s\n", SDL_GetError());
		success = false;
	}
	else {
		// Create Window
		window4 = SDL_CreateWindow
		("Geometry Primitive Rendering",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI
		);

		if (window4 == NULL) {
			printf("Window could not be created, SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else {
			// Create renderer
			renderer1 = SDL_CreateRenderer(
				window4, -1, SDL_RENDERER_ACCELERATED
			);

			if (renderer1 == NULL) {
				printf("Renderer could not be created. SDL Error: %s\n", SDL_GetError());
				success = false;
			}
		}
	}

	return success;
}

void closeApp4() {
	// Destroy window
	SDL_DestroyWindow(window4);
	window4 = NULL;

	// Quit SDL subsystems
	SDL_Quit();
}

int GeometryRendering() {
	// Start up SDL and create window
	if (!init4()) {
		printf("Failed to initialise!\n");
	}
	else {
		// line width for all things here
		int lineWidth = 10;

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


				// display white on screen
				SDL_SetRenderDrawColor(
					renderer1, 0xCC, 0xCC, 0xCC, 0xFF
				);
				SDL_RenderClear(renderer1);


				// green rectangle
				SDL_Rect greenRect = {
					SCREEN_WIDTH / 6,
					SCREEN_HEIGHT / 6,
					SCREEN_WIDTH * 2 / 3,
					SCREEN_HEIGHT * 2 / 3
				};
				SDL_SetRenderDrawColor(
					renderer1, 0x44, 0xFF, 0x88, 0xFF
				);
				SDL_RenderFillRect(renderer1, &greenRect);


				SDL_Rect whiteRect = {
					(SCREEN_WIDTH / 6) + lineWidth,
					(SCREEN_HEIGHT / 6) + lineWidth,
					(SCREEN_WIDTH * 2 / 3) - (2 * lineWidth),
					(SCREEN_HEIGHT * 2 / 3) - (2 * lineWidth)
				};
				SDL_SetRenderDrawColor(
					renderer1, 0xCC, 0xCC, 0xCC, 0xFF
				);
				SDL_RenderFillRect(renderer1, &whiteRect);


				// red rectangle
				SDL_Rect redRect = {
					SCREEN_WIDTH / 4,
					SCREEN_HEIGHT / 4,
					SCREEN_WIDTH / 2,
					SCREEN_HEIGHT / 2
				};
				SDL_SetRenderDrawColor(
					renderer1, 0xFF, 0x44, 0x88, 0xFF
				);
				SDL_RenderFillRect(renderer1, &redRect);


				// blue line
				SDL_SetRenderDrawColor(
					renderer1, 0x22, 0x44, 0xFF, 0xFF
				);
				SDL_RenderDrawLine(
					renderer1,
					0, SCREEN_HEIGHT / 2,
					SCREEN_WIDTH, SCREEN_HEIGHT / 2
				);

				// yellow dotted line
				SDL_SetRenderDrawColor(
					renderer1, 0xFF, 0xFF, 0x00, 0xFF
				);
				
				for (int i = 0; i < SCREEN_HEIGHT; i+=3) 
				{
					SDL_RenderDrawPoint(
						renderer1,
						SCREEN_WIDTH / 2, i
					);
				}


				// update screen
				SDL_RenderPresent(renderer1);
			}
		}
	}

	// free resources and close SDl
	closeApp4();

	return 0;
}