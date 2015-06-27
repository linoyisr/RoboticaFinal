/*
 * LaserHelper.h
 */

#ifndef LASERHELPER_H_
#define LASERHELPER_H_

#include "Point.h"

#define HALF_CYCLE 180
#define LASERS_NUMBER 666
#define LASER_AREA 240
#define BEAM_FOREACH_ANGLE LASER_AREA/LASERS_NUMBER //0.36
#define MINIMAL_ANGLE -120


class LaserHelper {
private:
	static double indexToAngle(int index);
	static double angleToRad(float angle);
public:
	static double indexToRad(int index);
};

#endif /* LASERHELPER_H_ */
