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

	double xLoc = _robot->getEstimateLocation().GetPoint().GetX();
	double yLoc = _robot->getEstimateLocation().GetPoint().GetY();

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
	double waypointX =  (_waypointsManager->currentWayPoint.GetX());
	double waypointY =  (_waypointsManager->currentWayPoint.GetY());
	cout << "waypointX " << waypointX;
	cout << " waypointY " <<waypointY << endl;
	cout << "x sum " << waypointX - xLoc << " y sum " <<waypointY - yLoc <<endl;
	cout << "x abs " << abs(waypointX - xLoc) << " y abs " << abs(waypointY - yLoc) << endl;
	double powX = (pow(waypointX - xLoc, 2));
	double powY = (pow(waypointY - yLoc, 2));
	cout << "powX " << powX << " powY " << powY << endl;
	double distance = sqrt(powX + powY);
	cout << "distance " << distance << endl;
	//if(abs(waypointX - xLoc) < 1 && abs(waypointY - yLoc) < 1)
			//waypointY == yLoc)
	//if (distance < _waypointsManager->minDistance)
	//{
	//	_waypointsManager->minDistance = distance;
	//}
	//else
	//if(abs(waypointX - xLoc) < 1 && abs(waypointY - yLoc) < 1)
	if (distance < sqrt(1.6))
	{
		cout << "Is Innnn" << endl;
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
