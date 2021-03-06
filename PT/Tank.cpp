#include <iostream>
#include "Tank.h"

Tank::Tank()
{
}

Tank::Tank(int x1, int y1, int c)
{
	x = x1;
	y = y1;
	life = 3;
	course = c;
}

void Tank::setX(int x2)
{
	x = x2;

	if (x > 500){
		x = 500;
	}
	else if (x < 0){
		x = 0;
	}
}

void Tank::setY(int y2)
{
	y = y2;

	if (y > 500){
		y = 500;
	}
	else if (y < 0){
		y = 0;
	}
}

void Tank::setLife()
{
	life = life - 1;
}

void Tank::setDead()
{
	x = -100;
	y = -100;
	life = 0;
}

void Tank::setCourse(int c)
{
	course = c;
}

void Tank::setShooting(bool is) {
	isShooting = is;
}

int Tank::getX()
{
	return x;
}

int Tank::getY()
{
	return y;
}

int Tank::getLife()
{
	return life;
}

int Tank::getCourse()
{
	return course;
}

bool Tank::getShooting() {
	return isShooting;
}