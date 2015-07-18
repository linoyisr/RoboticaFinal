/*
 * PlnObstacleAvoid.h
 */

#ifndef PLNOBSTACLEAVOID_H_
#define PLNOBSTACLEAVOID_H_

#include "../behaviors/Behavior.h"
#include "../behaviors/GoToPoint.h"
#include "Plan.h"

class PlnObstacleAvoid: public Plan
{
	Behavior* _behaviors[4];

public:
	PlnObstacleAvoid(Robot robot, WaypointsManager waypointsManager);
	Behavior* getStartPoint(){return _startBehavior;}
	virtual ~PlnObstacleAvoid();
};

#endif /* PLNOBSTACLEAVOID_H_ */
