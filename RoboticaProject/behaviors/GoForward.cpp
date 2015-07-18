/*
 * GoForward.cpp
 */

#include "GoForward.h"
#include <iostream>
#include <math.h>

bool GoForward::startCond()
{
	/*return (_robot.checkRange(_robot.getLaserSpec() / 2 - LASER_SPEC,
			_robot.getLaserSpec() / 2 + LASER_SPEC));*/
	return (_robot->checkRange(_robot->getLaserSpec() / 2 - 111,
				_robot->getLaserSpec() / 2 + 111));
}

bool GoForward::stopCond()
{
	_robot->Read();
	Point robotLocation = new Point(_robot->getRobotLocation().GetPoint().GetX(),
				_robot->getRobotLocation().GetPoint().GetY());
	vector<Point>::iterator wpoint =
			find(_waypointsManager->wayPoints.begin(),
			_waypointsManager->wayPoints.end(),
			robotLocation);

	// check if robot location is in waypoints list
	//if (wpoint != _waypointsManager.wayPoints.end())

	return (!startCond() || (wpoint != _waypointsManager->wayPoints.end()));
}

void GoForward::action()
{
	//_robot.setSpeed(MOVE_SPEED, 0.0);
	_robot->setSpeed(0.1, 0.0);
}

GoForward::GoForward(Robot* robot, WaypointsManager* waypointsManager): Behavior(robot) {
	_waypointsManager = waypointsManager;
}

GoForward::~GoForward() {
	// TODO Auto-generated destructor stub
}
