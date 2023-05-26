#pragma once

#include <SDL.h>
#include <string>

bool init();

SDL_Surface* loadSurface(std::string path);

bool loadMedia();

void closeApp();

int NavigatorMain();

void GetImageOnKeyDown(int newX, int newY);