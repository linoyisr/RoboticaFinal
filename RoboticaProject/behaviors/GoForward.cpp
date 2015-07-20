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


	Point wpoint(99999,99999);

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

	if (distance < sqrt(1.6))
	{
		cout << "Is Innnn" << endl;
		wpoint = _waypointsManager->currentWayPoint;
	}


	bool isRangeClear = startCond();
	bool locationInWaypoints = (wpoint.GetX() != 99999 || wpoint.GetY() != 99999);
	cout << "GoForward::stopCond , isRangeClear: " << isRangeClear << " location In Waypoints: " << locationInWaypoints << endl;
	cout << "GoForward::stopCond , robotLoc: " << endl;
	_robot->getEstimateLocation().Print();
	return (!isRangeClear || locationInWaypoints);

}

void GoForward::action() {
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
