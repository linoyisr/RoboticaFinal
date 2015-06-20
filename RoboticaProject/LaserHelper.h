/*
 * LaserHelper.h
 *
 *  Created on: May 16, 2014
 *      Author: user
 */

#ifndef LASERHELPER_H_
#define LASERHELPER_H_

#include "Point.h"

class LaserHelper {
public:
	LaserHelper();
	virtual ~LaserHelper();
	static double indexToAngle(int index);
	static Point findObjectLocation(Point robotLoc, float robotAngle, int laserIndex);
	static double angleToRad(float angle);
	static double indexToRad(int index);
};

#endif /* LASERHELPER_H_ */
