/*
 * Point.h
 */

#ifndef POINT_H_
#define POINT_H_

#include <iostream>

using namespace std;

class Point {

private:
	int _x;
	int _y;

public:
	Point();
	Point(int x, int y);
	virtual ~Point();
	int GetX();
	int GetY();
	void SetX(int x);
	void SetY(int y);
	void PrintPoint();
};

#endif /* POINT_H_ */
