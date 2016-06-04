#ifndef Graphic_H
#define Graphic_H
#include <SDL.h>
#undef main
#include <iostream>

#define HEIGHT 550
#define WIDTH 550

using namespace std;
class Graphic {
	public: 
	 SDL_Window* gWindow = NULL;
	 SDL_Surface* gScreenSurface = NULL;
	 SDL_Surface* gHelloWorld = NULL;	
	 SDL_Surface* gTank[4];
	 SDL_Rect dTank[4];
	 bool init();
	 bool loadMedia();
	 void update(int d[]);
	 void close();
	 void run();
};
#endif