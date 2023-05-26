#include <stdio.h>
#include <SDL.h>
#include <vector>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

struct Point {
	SDL_FPoint x;
	SDL_FPoint y;
};

struct Triangle {
	std::vector<SDL_Vertex> points;
};

const Triangle outerTri = {
	{ 
    	{ SDL_FPoint{ 100, 550 }, SDL_Color{ 0, 0, 0, 255 }, SDL_FPoint{ 0 }, },
	    { SDL_FPoint{ 700, 550 }, SDL_Color{ 0, 0, 0, 255 }, SDL_FPoint{ 0 }, },
    	{ SDL_FPoint{ 400, 50 }, SDL_Color{ 0, 0, 0, 255 }, SDL_FPoint{ 0 }, } 
	}
};

std::vector<Triangle> vertices;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool init() {
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		// add print statement -  could not start sdl
		success = false;
	}
	else {
		window = SDL_CreateWindow(
			"Sierpinski Triangle",
			100, 100, SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_ALLOW_HIGHDPI
		);

		if (window == NULL) {
			// add printf - could not create window
			success = false;
		}
		else {
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

			if (renderer == NULL) {
				// add printf - could not create renderer
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

int innerTriangle(Triangle outerVertices, int iterationCounter, int triangleCounter) {
	if (iterationCounter < 7) {
		SDL_FPoint point1 = outerVertices.points[0].position;
		SDL_FPoint point2 = outerVertices.points[1].position;
		SDL_FPoint point3 = outerVertices.points[2].position;

		SDL_FPoint newPoint1 = { (point3.x + point2.x) / 2, (point3.y + point2.y) / 2 };
		SDL_FPoint newPoint2 = { (point1.x + point3.x) / 2, (point1.y + point3.y) / 2 };
		SDL_FPoint newPoint3 = { (point1.x + point2.x) / 2, (point1.y + point2.y) / 2 };

		Triangle newTri = {
		{
			{ SDL_FPoint{ newPoint1 }, SDL_Color{ 255, 255, 255, 255 }, SDL_FPoint{ 0 }, },
			{ SDL_FPoint{ newPoint2 }, SDL_Color{ 255, 255, 255, 255 }, SDL_FPoint{ 0 }, },
			{ SDL_FPoint{ newPoint3 }, SDL_Color{ 255, 255, 255, 255 }, SDL_FPoint{ 0 }, }
		}
		};

		triangleCounter++;
		iterationCounter++;
		vertices.push_back(newTri);

		triangleCounter =  innerTriangle({
			{
				{ SDL_FPoint{ point1 }, SDL_Color{ 255, 255, 255, 255 }, SDL_FPoint{ 0 }, },
				{ SDL_FPoint{ newPoint2 }, SDL_Color{ 255, 255, 255, 255 }, SDL_FPoint{ 0 }, },
				{ SDL_FPoint{ newPoint3}, SDL_Color{ 255, 255, 255, 255 }, SDL_FPoint{ 0 }, }
			}
		}, iterationCounter, triangleCounter);

		triangleCounter = innerTriangle({
			{
				{ SDL_FPoint{ newPoint1 }, SDL_Color{ 255, 255, 255, 255 }, SDL_FPoint{ 0 }, },
				{ SDL_FPoint{ point2 }, SDL_Color{ 255, 255, 255, 255 }, SDL_FPoint{ 0 }, },
				{ SDL_FPoint{ newPoint3}, SDL_Color{ 255, 255, 255, 255 }, SDL_FPoint{ 0 }, }
			}
		}, iterationCounter, triangleCounter);

		triangleCounter = innerTriangle({
			{
				{ SDL_FPoint{ newPoint1 }, SDL_Color{ 255, 255, 255, 255 }, SDL_FPoint{ 0 }, },
				{ SDL_FPoint{ newPoint2 }, SDL_Color{ 255, 255, 255, 255 }, SDL_FPoint{ 0 }, },
				{ SDL_FPoint{ point3}, SDL_Color{ 255, 255, 255, 255 }, SDL_FPoint{ 0 }, }
			}
		}, iterationCounter, triangleCounter);

		// NOT ASYNCRONOUS!! DO NOT UNCOMMENT
		//SDL_Delay(1000);
	}

	return triangleCounter;
}

void TriangleDraw() {
	if (init()) {
		int triangles = innerTriangle(outerTri, 0, 1);
		printf("Number of triangles: %d", triangles);

		bool quit = false;

		SDL_Event e;

		while (!quit) 
		{
			while (SDL_PollEvent(&e)) 
			{
				if (e.type == SDL_QUIT) {
					quit = true;
				}
			}

			SDL_SetRenderDrawColor(
				renderer,
				//0x00, 0x88, 0xFF, 0xFF
				0xFF, 0xFF, 0xFF, 0xFF
			);

			SDL_RenderClear(renderer);

			SDL_RenderGeometry(
				renderer, nullptr, outerTri.points.data(), outerTri.points.size(),
				nullptr, 0
			);

			for (int i = 0; i < vertices.size(); i++)
			{
				SDL_RenderGeometry(
					renderer, nullptr, 
					vertices[i].points.data(), vertices[i].points.size(),
					nullptr, 0
				);
			}

			SDL_RenderPresent(renderer);
		}
	}

	closeApp();
}