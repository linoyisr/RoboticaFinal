/*
 * Location.h
 *
 *  Created on: Jun 26, 2015
 *      Author: colman
 */

#ifndef LOCATION_H_
#define LOCATION_H_

#include "Point.h"

class Location {
public:
	Location();
	Location(Point p, double yaw);
	Location(double x ,double y, double yaw);
	virtual ~Location();

	Point GetPoint();
	double GetYawPoint();

	void SetPoint(Point p);
	void SetYawPoint(double yaw);
	void SetLocation(Location location);
	void Print();

private:
	Point point;
	double yawPoint;
};

#endif /* LOCATION_H_ */
