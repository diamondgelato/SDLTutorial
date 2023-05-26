#include <SDL.h>
#include <string>

using namespace std;

// start SDL and create window
bool init1();

// load media
bool loadMedia1();

// free media and shut down SDL
void closeApp1();

// loads individual image
SDL_Surface* loadSurface(string path);

int KeyPresses();