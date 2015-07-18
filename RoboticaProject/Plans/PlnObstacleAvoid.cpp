/*
 * PlnObstacleAvoid.cpp
 */

#include "PlnObstacleAvoid.h"

PlnObstacleAvoid::PlnObstacleAvoid(Robot robot, WaypointsManager waypointsManager) : Plan(robot)
{
	//Creating Behaviors
	_behaviors = new Behavior*[2];
	_behaviors[0] = new GoToPoint(robot, waypointsManager);
	_behaviors[1] = new GoForward(robot, waypointsManager);

	//Connecting behaviors
	_behaviors[0]->addNextBehavior(_behaviors[1]);
	_behaviors[1]->addNextBehavior(_behaviors[0]);
	//_behaviors[2]->addNextBehavior(_behaviors[0]);

	_startBehavior = _behaviors[0];

	/*
	//Creating Behaviors
	_behaviors[0] = new TurnRight(robot);
	_behaviors[1] = new TurnLeft(robot);
	_behaviors[2] = new GoForward(robot);
	_behaviors[3] = new TurnAround(robot);

	//Connecting Behaviors
	_behaviors[0]->addBeh(_behaviors[1]);
	_behaviors[0]->addBeh(_behaviors[2]);
	_behaviors[0]->addBeh(_behaviors[3]);

	_behaviors[1]->addBeh(_behaviors[0]);
	_behaviors[1]->addBeh(_behaviors[2]);
	_behaviors[1]->addBeh(_behaviors[3]);

	_behaviors[2]->addBeh(_behaviors[0]);
	_behaviors[2]->addBeh(_behaviors[1]);
	_behaviors[2]->addBeh(_behaviors[3]);

	_behaviors[3]->addBeh(_behaviors[0]);
	_behaviors[3]->addBeh(_behaviors[1]);
	_behaviors[3]->addBeh(_behaviors[2]);

	_startBehavior = _behaviors[0];
	*/
}

PlnObstacleAvoid::~PlnObstacleAvoid() {
	// TODO Auto-generated destructor stub
	for(int i=0;i<4;i++)
		delete _behaviors[i];
}
