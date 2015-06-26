/*
 * Point.cpp
 */

#include "Point.h"

Point::Point()
{
	_x = 0;
	_y = 0;
}
Point::Point(int x, int y)
{
	_x = x;
	_y = y;
}

int Point::GetX()
{
	return _x;
}

int Point::GetY()
{
	return _y;
}

void Point::SetX(int x)
{
	_x = x;
}

void Point::SetY(int y)
{
	_y = y;
}

void Point::PrintPoint()
{
	cout << "[" << _x << "," << _y <<  "]" << endl;
}


Point::~Point()
{
}
