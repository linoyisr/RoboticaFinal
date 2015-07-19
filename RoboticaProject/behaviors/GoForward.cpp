/*
 * GoForward.cpp
 */

#include "GoForward.h"


bool GoForward::startCond() {
	/*return (_robot.checkRange(_robot.getLaserSpec() / 2 - LASER_SPEC,
	 _robot.getLaserSpec() / 2 + LASER_SPEC));*/
	bool result = (_robot->isRangeClear(_robot->getLaserSpec() / 2 - 111, _robot->getLaserSpec() / 2 + 111));
	cout << endl << "GoForward startCond: " <<result << endl;
	return result;
}

bool GoForward::stopCond() {
	_robot->Read();

	int xLoc = _robot->getEstimateLocation().GetPoint().GetX();
	int yLoc = _robot->getEstimateLocation().GetPoint().GetY();

	//cout << "GoForward::stopCond , robotLocx: " << xLoc << " robotLocy: " << yLoc;
/*
	vector<Point>::iterator wpoint;
	for (vector<Point>::iterator iter = _waypointsManager->wayPoints.begin(); iter != _waypointsManager->wayPoints.end(); iter++)
	{//iterate through the vector to look for the correct name
		if((*iter).GetX() == xLoc && (*iter).GetY() == yLoc)
		{
			wpoint = iter;
		}
	}
	*/
	Point wpoint(99999,99999);
	/*
	for(int i = 0; i < _waypointsManager->wayPoints.size(); i++)
	{
		if( (_waypointsManager->wayPoints[i]).GetX() == xLoc &&
			(_waypointsManager->wayPoints[i]).GetY() == yLoc)
		{
			wpoint = _waypointsManager->wayPoints[i];
		}
	}*/
	if( (_waypointsManager->currentWayPoint).GetX() == xLoc &&
		(_waypointsManager->currentWayPoint).GetY() == yLoc)
	{
		wpoint = _waypointsManager->currentWayPoint;
	}

	// check if robot location is in waypoints list
	//if (wpoint != _waypointsManager.wayPoints.end())

	bool isRangeClear = startCond();
	bool locationInWaypoints = (wpoint.GetX() != 99999 || wpoint.GetY() != 99999);
	cout << "GoForward::stopCond , isRangeClear: " << isRangeClear << " location In Waypoints: " << locationInWaypoints << endl;
	cout << "GoForward::stopCond , robotLoc: " << endl;
	_robot->getEstimateLocation().Print();
	return (!isRangeClear || locationInWaypoints);

}

void GoForward::action() {
	//_robot.setSpeed(MOVE_SPEED, 0.0);
	cout << endl << "GoForward start run" << endl;
	_robot->setSpeed(0.4, 0.0);
}

GoForward::GoForward(Robot* robot, WaypointsManager* waypointsManager) :
		Behavior(robot) {
	_waypointsManager = waypointsManager;
}

GoForward::~GoForward() {
	// TODO Auto-generated destructor stub
}
