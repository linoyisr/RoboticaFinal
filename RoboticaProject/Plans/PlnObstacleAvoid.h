/*
 * PlnObstacleAvoid.h
 */

#ifndef PLNOBSTACLEAVOID_H_
#define PLNOBSTACLEAVOID_H_

#include "../behaviors/TurnRight.h"
#include "../behaviors/TurnLeft.h"
#include "../behaviors/GoForward.h"
#include "../behaviors/Behavior.h"
#include "Plan.h"

class PlnObstacleAvoid: public Plan
{
	Behavior* _behaviors[3];

public:
	PlnObstacleAvoid(Robot* robot);
	Behavior* getStartPoint(){return _startBehavior;}
	virtual ~PlnObstacleAvoid();
};

#endif /* PLNOBSTACLEAVOID_H_ */
