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
	Location(Point* p, int yaw);
	Location(int x ,int y, int yaw);
	virtual ~Location();

	Point* GetPoint();
	int GetYawPoint();

	void SetPoint(Point* p);
	void SetYawPoint(int yaw);
	void SetLocation(Location* location);

private:
	Point* point;
	int yawPoint;
};

#endif /* LOCATION_H_ */