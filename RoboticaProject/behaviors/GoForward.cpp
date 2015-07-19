/*
 * GoForward.cpp
 */

#include "GoForward.h"


bool GoForward::startCond() {
	/*return (_robot.checkRange(_robot.getLaserSpec() / 2 - LASER_SPEC,
	 _robot.getLaserSpec() / 2 + LASER_SPEC));*/
	bool result = (_robot->isRangeClear(_robot->getLaserSpec() / 2 - 111, _robot->getLaserSpec() / 2 + 111));
	cout << endl;
	cout << "GoForward startCond: " <<result << endl;;
	return result;
}

bool GoForward::stopCond() {
	_robot->Read();

	int xLoc = _robot->getEstimateLocation().GetPoint().GetX();
	int yLoc = _robot->getEstimateLocation().GetPoint().GetY();

	cout << "GoForward::stopCond , robotLocx: " << xLoc << " robotLocy: " << yLoc;;

	vector<Point>::iterator wpoint;
	for (vector<Point>::iterator iter = _waypointsManager->wayPoints.begin(); iter != _waypointsManager->wayPoints.end(); iter++)
	{//iterate through the vector to look for the correct name
		if((*iter).GetX() == xLoc && (*iter).GetY() == yLoc)
		{
			wpoint = iter;
		}
	}

	// check if robot location is in waypoints list
	//if (wpoint != _waypointsManager.wayPoints.end())

	bool isRangeClear = startCond();
	bool locationInWaypoints = (wpoint != _waypointsManager->wayPoints.end());
	cout << "GoForward::stopCond , isRangeClear: " << isRangeClear << " location In Waypoints: " << locationInWaypoints << endl;;
	return (!isRangeClear || locationInWaypoints);

}

void GoForward::action() {
	//_robot.setSpeed(MOVE_SPEED, 0.0);
	cout << endl << "GoForward start run" << endl;
	_robot->setSpeed(0.3, 0.0);
}

GoForward::GoForward(Robot* robot, WaypointsManager* waypointsManager) :
		Behavior(robot) {
	_waypointsManager = waypointsManager;
}

GoForward::~GoForward() {
	// TODO Auto-generated destructor stub
}
