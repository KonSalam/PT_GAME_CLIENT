#ifndef Graphic_H
#define Graphic_H
#include <SDL.h>
#include "Tank.h"
#undef main
#include <iostream>

#define HEIGHT 550
#define WIDTH 550

using namespace std;
class Graphic {
private:
	SDL_Window* gWindow = NULL;
	SDL_Surface* gScreenSurface = NULL;
	SDL_Surface* gTank[4];
	SDL_Rect dTank[4];

public:
	bool init(Tank tanks[]);
	bool loadMedia(Tank tanks[]);
	void close();
	void updateWindow(Tank tanks[]);
	void updateView(Tank tanks[]);
	void updatePosition(Tank tanks[]);
	void Graphic::showMessage(bool win, string message);
};
#endif