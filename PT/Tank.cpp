#include <iostream>
#include "Tank.h"

Tank::Tank(int x1,int y1)
{
	x = x1;
	y = y1;
}

void Tank::setX(int x2)
{
	x = x2;
}

void Tank::setY(int y2)
{
	y = y2;
}

int Tank::getX()
{
	return x;
}

int Tank::getY()
{
	return y;
}

