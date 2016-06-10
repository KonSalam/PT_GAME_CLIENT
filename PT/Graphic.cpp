#include "Graphic.h"
#include "Client.h"

bool Graphic::init() {

	if (SDL_Init(SDL_INIT_VIDEO) < 0){
		cout << "SDL could not initialize! SDL_Error:" << SDL_GetError() << endl;
		return false;
	}
	else{
		gWindow = SDL_CreateWindow("Panzer Tournament v.0.1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
			return false;
		}
		else{
			gScreenSurface = SDL_GetWindowSurface(gWindow);
			return true;
		}
	}
}

void Graphic::close() {
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	SDL_Quit();
}

bool Graphic::loadMedia() {
	gTank[0] = SDL_LoadBMP("graphic/tank_red_down.bmp");
	gTank[1] = SDL_LoadBMP("graphic/tank_green_up.bmp");
	gTank[2] = SDL_LoadBMP("graphic/tank_blue_down.bmp");
	gTank[3] = SDL_LoadBMP("graphic/tank_yellow_up.bmp");
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
void Graphic::updateView(int d[]) {
	// 1-dol 2-gora 3-lewo 4-prawo
	if (d[2] == 1)
		gTank[0] = SDL_LoadBMP("graphic/tank_red_down.bmp");
	else if (d[2] == 2)
		gTank[0] = SDL_LoadBMP("graphic/tank_red_up.bmp");
	else if (d[2] == 3)
		gTank[0] = SDL_LoadBMP("graphic/tank_red_left.bmp");
	else if (d[2] == 4)
		gTank[0] = SDL_LoadBMP("graphic/tank_red_right.bmp");

	if (d[5] == 1)
		gTank[1] = SDL_LoadBMP("graphic/tank_green_down.bmp");
	else if (d[5] == 2)
		gTank[1] = SDL_LoadBMP("graphic/tank_green_up.bmp");
	else if (d[5] == 3)
		gTank[1] = SDL_LoadBMP("graphic/tank_green_left.bmp");
	else if (d[5] == 4)
		gTank[1] = SDL_LoadBMP("graphic/tank_green_right.bmp");

	if (d[8] == 1)
		gTank[2] = SDL_LoadBMP("graphic/tank_blue_down.bmp");
	else if (d[8] == 2)
		gTank[2] = SDL_LoadBMP("graphic/tank_bluee_up.bmp");
	else if (d[8] == 3)
		gTank[2] = SDL_LoadBMP("graphic/tank_blue_left.bmp");
	else if (d[8] == 4)
		gTank[2] = SDL_LoadBMP("graphic/tank_blue_right.bmp");

	if (d[11] == 1)
		gTank[3] = SDL_LoadBMP("graphic/tank_yellow_down.bmp");
	else if (d[11] == 2)
		gTank[3] = SDL_LoadBMP("graphic/tank_yellow_up.bmp");
	else if (d[11] == 3)
		gTank[3] = SDL_LoadBMP("graphic/tank_yellow_left.bmp");
	else if (d[11] == 4)
		gTank[3] = SDL_LoadBMP("graphic/tank_yellow_right.bmp");
}

void Graphic::updatePosition(int d[]) {
	dTank[0].x = d[0];
	dTank[0].y = d[1];

	dTank[1].x = d[3];
	dTank[1].y = d[4];

	dTank[2].x = d[6];
	dTank[2].y = d[7];

	dTank[3].x = d[9];
	dTank[3].y = d[10];
	SDL_FillRect(gScreenSurface, NULL, 0x000000);
	updateView(d);

	for (int i = 0; i < 4; i++) {
		cout << "UPDATE: " << dTank[i].x << " " << dTank[i].y << endl;
		SDL_BlitSurface(gTank[i], NULL, gScreenSurface, &dTank[i]);
	}
	SDL_UpdateWindowSurface(gWindow);
}