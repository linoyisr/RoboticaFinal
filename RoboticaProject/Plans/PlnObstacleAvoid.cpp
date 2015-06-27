/*
 * PlnObstacleAvoid.cpp
 */

#include "PlnObstacleAvoid.h"

PlnObstacleAvoid::PlnObstacleAvoid(Robot* robot) : Plan(robot)
{
	//Creating Behaviors
	_behaviors[0] = new TurnRight(robot);
	_behaviors[1] = new TurnLeft(robot);
	_behaviors[2] = new GoForward(robot);

	//Connecting Behaviors
	_behaviors[0]->addBeh(_behaviors[1]);
	_behaviors[0]->addBeh(_behaviors[2]);

	_behaviors[1]->addBeh(_behaviors[0]);
	_behaviors[1]->addBeh(_behaviors[2]);

	_behaviors[2]->addBeh(_behaviors[0]);
	_behaviors[2]->addBeh(_behaviors[1]);

	_startBehavior = _behaviors[0];
}

PlnObstacleAvoid::~PlnObstacleAvoid() {
	// TODO Auto-generated destructor stub
	for(int i=0;i<3;i++)
		delete _behaviors[i];
}
