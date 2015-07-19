/*
 * Point.h
 */

#ifndef POINT_H_
#define POINT_H_

#include <iostream>

using namespace std;

class Point {

private:
	double _x;
	double _y;

public:
	Point();
	Point(double x, double y);
	virtual ~Point();
	double GetX();
	double GetY();
	void SetX(double x);
	void SetY(double y);
	void PrintPoint();
};

#endif /* POINT_H_ */
