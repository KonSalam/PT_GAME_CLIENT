#include "Graphic.h"
#include "Client.h"

bool Graphic::init(Tank tanks[]) {

	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0){
		cout << "SDL could not initialize! SDL_Error:" << SDL_GetError() << endl;
		success=false;
	}
	else{
		gWindow = SDL_CreateWindow("Panzer Tournament v.0.1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
			success=false;
		}
		else{
			gScreenSurface = SDL_GetWindowSurface(gWindow);
			success=true;
		}
	}
	if(success&&loadMedia(tanks)) updateWindow(tanks);
	else close();
	return success;
}

void Graphic::close() {
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	SDL_Quit();
}

void Graphic::updateWindow(Tank tanks[]) {
	while (true) {
		updatePosition(tanks);
		SDL_UpdateWindowSurface(gWindow);
		SDL_PumpEvents();
	}
}

void Graphic::showMessage(bool win, string message){

	if (win == true){
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Uwaga Wygrales", message.c_str(), NULL);
	}
	else{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Niestety Przegrales", message.c_str(), NULL);
	}
}

bool Graphic::loadMedia(Tank tanks[]) {
	gTank[0] = SDL_LoadBMP("graphic/tank_red_down.bmp");
	gTank[1] = SDL_LoadBMP("graphic/tank_green_up.bmp");
	gTank[2] = SDL_LoadBMP("graphic/tank_blue_down.bmp");
	gTank[3] = SDL_LoadBMP("graphic/tank_yellow_up.bmp");
	dTank[0] = { tanks[0].getX(), tanks[0].getY(), 0, 0 };
	dTank[1] = { tanks[1].getX(), tanks[1].getY(), 0, 0 };
	dTank[2] = { tanks[2].getX(), tanks[2].getY(), 0, 0 };
	dTank[3] = { tanks[3].getX(), tanks[3].getY(), 0, 0 };

	for (int i = 0; i < 4; i++) {
		SDL_BlitSurface(gTank[i], NULL, gScreenSurface, &dTank[i]);
	}
	SDL_UpdateWindowSurface(gWindow);
	SDL_PumpEvents();
	return true;
}
void Graphic::updateView(Tank tanks[]) {
	
	int redCourse = tanks[0].getCourse();
	int greenCourse = tanks[1].getCourse();
	int blueCourse = tanks[2].getCourse();
	int yellowCourse = tanks[3].getCourse();

	if (redCourse == 1)
		gTank[0] = SDL_LoadBMP("graphic/tank_red_down.bmp");
	else if (redCourse == 2)
		gTank[0] = SDL_LoadBMP("graphic/tank_red_up.bmp");
	else if (redCourse == 3)
		gTank[0] = SDL_LoadBMP("graphic/tank_red_left.bmp");
	else if (redCourse == 4)
		gTank[0] = SDL_LoadBMP("graphic/tank_red_right.bmp");

	if (greenCourse == 1)
		gTank[1] = SDL_LoadBMP("graphic/tank_green_down.bmp");
	else if (greenCourse == 2)
		gTank[1] = SDL_LoadBMP("graphic/tank_green_up.bmp");
	else if (greenCourse == 3)
		gTank[1] = SDL_LoadBMP("graphic/tank_green_left.bmp");
	else if (greenCourse == 4)
		gTank[1] = SDL_LoadBMP("graphic/tank_green_right.bmp");

	if (blueCourse == 1)
		gTank[2] = SDL_LoadBMP("graphic/tank_blue_down.bmp");
	else if (blueCourse == 2)
		gTank[2] = SDL_LoadBMP("graphic/tank_bluee_up.bmp");
	else if (blueCourse == 3)
		gTank[2] = SDL_LoadBMP("graphic/tank_blue_left.bmp");
	else if (blueCourse == 4)
		gTank[2] = SDL_LoadBMP("graphic/tank_blue_right.bmp");

	if (yellowCourse == 1)
		gTank[3] = SDL_LoadBMP("graphic/tank_yellow_down.bmp");
	else if (yellowCourse == 2)
		gTank[3] = SDL_LoadBMP("graphic/tank_yellow_up.bmp");
	else if (yellowCourse == 3)
		gTank[3] = SDL_LoadBMP("graphic/tank_yellow_left.bmp");
	else if (yellowCourse == 4)
		gTank[3] = SDL_LoadBMP("graphic/tank_yellow_right.bmp");
}

void Graphic::updatePosition(Tank tanks[]) {
	dTank[0].x = tanks[0].getX();
	dTank[0].y = tanks[0].getY();

	dTank[1].x = tanks[1].getX();
	dTank[1].y = tanks[1].getY();

	dTank[2].x = tanks[2].getX();
	dTank[2].y = tanks[2].getY();

	dTank[3].x = tanks[3].getX();
	dTank[3].y = tanks[3].getY();
	SDL_FillRect(gScreenSurface, NULL, 0x000000);
	updateView(tanks);

	for (int i = 0; i < 4; i++) {
		SDL_BlitSurface(gTank[i], NULL, gScreenSurface, &dTank[i]);
	}
}