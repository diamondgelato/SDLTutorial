#include <SDL.h>
#include <stdio.h>
#include <complex>
#include <cmath>
//#include "ComplexNumber.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int RENDERER_MULTIPLIER = 2;

std::complex<double> constant = -1.0;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool init() {
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("could not init SDL");
		success = false;
	}
	else {
		window = SDL_CreateWindow(
			"Julia Sets", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			SCREEN_WIDTH, SCREEN_HEIGHT, 0
		);

		if (window == NULL) {
			printf("could not init window");
			success = false;
		}
		else {
			renderer = SDL_CreateRenderer(
				window, -1, SDL_RENDERER_ACCELERATED
			);

			if (renderer == NULL) {
				printf("could not init renderer");
				success = false;
			}
		}
	}

	return success;
}

void closeApp() {
	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	SDL_DestroyWindow(window);
	window = NULL;

	SDL_Quit();
}

std::complex<double> ScreenSpacetoComplex(int xScr, int yScr) {
	std::complex<double> complexNum;

	complexNum.real(xScr * 4.0 / (SCREEN_WIDTH * RENDERER_MULTIPLIER) - 2);
	complexNum.imag((yScr * -4.0) / (SCREEN_HEIGHT * RENDERER_MULTIPLIER) + 2);
	//printf("%f + %fi\n", complexNum.real(), complexNum.imag());

	return complexNum;
}

int CheckExplosion(int xScr, int yScr) {
	std::complex<double> complexNum;
	complexNum = ScreenSpacetoComplex(xScr, yScr);	

	for (int i = 0; i < 25; i++)
	{
		complexNum = std::pow(complexNum, 2) + constant;

		if (std::norm(complexNum) > 100) {
			return i;
		}
	}
	return 0;
}

void JuliaSet() {
	if (init()) {
		bool quit = false;

		int i = 0, j = 0;

		SDL_Event e;

		SDL_RenderSetLogicalSize(
			renderer, 
			SCREEN_WIDTH * RENDERER_MULTIPLIER, 
			SCREEN_HEIGHT * RENDERER_MULTIPLIER
		);

		SDL_SetRenderDrawColor(
			renderer, 0xFF, 0xFF, 0xFF, 0xFF
		);
		SDL_RenderClear(renderer);

		int iterations;

		try
		{
			for (
				int i = 0;
				i < SCREEN_WIDTH * RENDERER_MULTIPLIER;
				i++
				)
			{
				for (
					int j = 0;
					j < SCREEN_HEIGHT * RENDERER_MULTIPLIER;
					j++
					)
				{
					iterations = CheckExplosion(i, j);
					if (iterations == 0) {
						SDL_SetRenderDrawColor(
							renderer, 0x0, 0x0, 0x0, 0xFF
						);
						SDL_RenderDrawPoint(
							renderer, i, j
						);
					}
				}
			}
		}
		catch (const std::exception&)
		{
			printf("wrong");
		}
		
		
		SDL_RenderPresent(renderer);

		while (!quit)
		{
			while (SDL_PollEvent(&e)) {
				if (e.type == SDL_QUIT)
					quit = true;
			}
		}
	}
}