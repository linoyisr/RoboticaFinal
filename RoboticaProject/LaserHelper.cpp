/*
 * LaserHelper.cpp
 *
 *  Created on: May 16, 2014
 *      Author: user
 */

#include "LaserHelper.h"
#include <math.h>

#define BEAM_PER_ANGLE 0.36
#define MINIMAL_ANGLE -120
#define HALF_CYCLE 180

LaserHelper::LaserHelper() {
	// TODO Auto-generated constructor stub

}

LaserHelper::~LaserHelper() {
	// TODO Auto-generated destructor stub
}

double LaserHelper::indexToAngle(int index)
{
	return index * BEAM_PER_ANGLE + MINIMAL_ANGLE;
}

double LaserHelper::angleToRad(float angle)
{
	return angle * M_PI / HALF_CYCLE;
}

double LaserHelper::indexToRad(int index)
{
	return angleToRad(indexToAngle(index));
}
