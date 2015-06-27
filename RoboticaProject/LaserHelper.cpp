/*
 * LaserHelper.cpp
 */

#include "LaserHelper.h"
#include <math.h>

double LaserHelper::indexToAngle(int index)
{
	return index * BEAM_FOREACH_ANGLE + MINIMAL_ANGLE;
}

double LaserHelper::angleToRad(float angle)
{
	return angle * M_PI / HALF_CYCLE;
}

double LaserHelper::indexToRad(int index)
{
	return angleToRad(indexToAngle(index));
}
