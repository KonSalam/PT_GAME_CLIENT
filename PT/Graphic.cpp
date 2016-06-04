#include "Graphic.h"
#include "Client.h"

bool Graphic::init() {

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL could not initialize! SDL_Error:" << SDL_GetError() << endl;
		return false;
	}
	else
	{
		gWindow = SDL_CreateWindow("Panzer Tournament v.0.1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
			return false;
		}
		else
		{
			gScreenSurface = SDL_GetWindowSurface(gWindow);
			return true;
		}
	}
}

bool Graphic::loadMedia() {
	gTank[0] = SDL_LoadBMP("graphic/tankRed.bmp");
	gTank[1] = SDL_LoadBMP("graphic/tankGreen.bmp");
	gTank[2] = SDL_LoadBMP("graphic/tankBlue.bmp");
	gTank[3] = SDL_LoadBMP("graphic/tankYellow.bmp");
	dTank[0] = { 0, 0, 0, 0 };
	dTank[1] = { 0, 500, 0, 0 };
	dTank[2] = { 500, 0, 0, 0 };
	dTank[3] = { 500, 500, 0, 0 };

	for (int i = 0; i < 4; i++) {
		SDL_BlitSurface(gTank[i], NULL, gScreenSurface, &dTank[i]);
	}
	SDL_UpdateWindowSurface(gWindow);
	return true;
}

void Graphic::close() {
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	SDL_Quit();
}

void Graphic::update(int d[]) {
	dTank[0].x = d[0];
	dTank[0].y = d[1];

	dTank[1].x = d[2];
	dTank[1].y = d[3];

	dTank[2].x = d[4];
	dTank[2].y = d[5];

	dTank[3].x = d[6];
	dTank[3].y = d[7];
	SDL_FillRect(gScreenSurface, NULL, 0x000000);

	for (int i = 0; i < 4; i++) {
		cout << "UPDATE: " << dTank[i].x << " " << dTank[i].y << endl;
		SDL_BlitSurface(gTank[i], NULL, gScreenSurface, &dTank[i]);
	}
	SDL_UpdateWindowSurface(gWindow);
}