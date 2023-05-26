#include <SDL.h>
#include <string>

#pragma once

using namespace std;

// Load individual texture
SDL_Texture* loadTexture(string path);

// intialisation function
bool init3();

// load all the media required
bool loadMedia();

// deallocate variables and close program
void close();

// function that runs everything
int TextureRendering();