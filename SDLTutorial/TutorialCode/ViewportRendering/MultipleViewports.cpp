#include <stdio.h>
#include <SDL.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

SDL_Window* window5 = NULL;
SDL_Renderer* renderer2 = NULL;

bool init5() {
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Could not initialise SDL");
		success = false;
	}
	else {
		window5 = SDL_CreateWindow(
			"Multiple Viewports",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_ALLOW_HIGHDPI
		);

		if (window5 == NULL) {
			printf("could not init window");
			success = false;
		}
		else {
			renderer2 = SDL_CreateRenderer(
				window5, -1, SDL_RENDERER_ACCELERATED
			);

			if (renderer2 == NULL) {
				printf("could not init renderer");
				success = false;
			}
		}
	}

	return success;
}

void closeApp5() {
	// destroy renderer
	SDL_DestroyRenderer(renderer2);
	renderer2 = NULL;

	// destroy window
	SDL_DestroyWindow(window5);
	window5 = NULL;

	SDL_Quit();
}

void MultipleViewports() {
	if (init5()) {
		bool quit = false;
		SDL_Event e;

		// top left viewport
		SDL_Rect topLeftViewport;
		topLeftViewport.x = 0;
		topLeftViewport.y = 0;
		topLeftViewport.w = SCREEN_WIDTH / 2;
		topLeftViewport.h = SCREEN_HEIGHT / 2;
		SDL_RenderSetViewport(renderer2, &topLeftViewport);

		// top right viewport
		SDL_Rect topRightViewport;
		topRightViewport.x = SCREEN_WIDTH / 2;
		topRightViewport.y = 0;
		topRightViewport.w = SCREEN_WIDTH / 2;
		topRightViewport.h = SCREEN_HEIGHT / 2;
		SDL_RenderSetViewport(renderer2, &topRightViewport);

		// top right viewport
		/*SDL_Rect topRightViewport;
		topRightViewport.x = SCREEN_WIDTH / 2;
		topRightViewport.y = 0;
		topRightViewport.w = SCREEN_WIDTH / 2;
		topRightViewport.h = SCREEN_HEIGHT / 2;
		SDL_RenderSetViewport(renderer2, &topRightViewport);*/

		while (!quit)
		{
			while (SDL_PollEvent(&e))
			{
				if (e.type == SDL_QUIT)
					quit = true;
			}
		}
	}

	closeApp5();
}