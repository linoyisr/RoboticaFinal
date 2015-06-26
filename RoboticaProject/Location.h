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
	Location(Point* p, int yaw)
	{
		point = p;
		yawPoint = yaw;
	}
	virtual ~Location(){}

	Point* GetPoint()
	{
		return point;
	}

	void SetPoint(Point* p)
	{
		point = p;
	}

	int GetYawPoint()
	{
		return yawPoint;
	}

	void SetYawPoint(int yaw)
	{
		yawPoint = yaw;
	}

private:
	Point* point;
	int yawPoint;
};

#endif /* LOCATION_H_ */
