/*
 * GoToPoint.cpp
 *
 *  Created on: Jul 17, 2015
 *      Author: colman
 */

#include "GoToPoint.h"

	GoToPoint::GoToPoint(Robot* robot, WaypointsManager* waypointsManager):Behavior(robot) {
		_waypointsManager = waypointsManager;
	}

	GoToPoint::~GoToPoint() {
		// TODO Auto-generated destructor stub
	}


	bool GoToPoint::startCond()
	{
		//_robot->Read();

		double robotYaw = _robot->getEstimateLocation().GetYawPoint();
		distanceBetweenYaw = _waypointsManager->calcYaw() - robotYaw;

		if(distanceBetweenYaw == 0)
			return false;
		else if(distanceBetweenYaw >= 180)
		{
			isRight =  1;
			distanceBetweenYaw = 360 - distanceBetweenYaw;
		}
		else if (distanceBetweenYaw < -180)
		{
			isRight = 0;
			distanceBetweenYaw = 360 + distanceBetweenYaw;
		}
		else if (distanceBetweenYaw > 0)
		{
			isRight = 0;
		}
		else
		{
			isRight = 1;
			distanceBetweenYaw = abs(distanceBetweenYaw);
		}

		bool result;
		if(isRight)
		{
			result = (_robot->isRangeClear(0, distanceBetweenYaw * 2.775));
		}
		else
		{
			result = (_robot->isRangeClear( _robot->getLaserSpec() - (distanceBetweenYaw * 2.775),
					_robot->getLaserSpec()));
		}
		cout << endl << "GoToPoint startCond: " <<result << endl;
		return result;
	}

	bool GoToPoint::stopCond()
	{
		bool isRangeClear;
		int robotYaw = _robot->getEstimateLocation().GetYawPoint();
		int waypointYaw = _waypointsManager->calcYaw() + 20;
		cout << "robotYaw : " << robotYaw <<endl;
		cout << "waypointYaw : " << waypointYaw <<endl;

		int absYawDistance = abs(robotYaw - waypointYaw);
		if(isRight)
		{
			isRangeClear = (_robot->isRangeClear(0, distanceBetweenYaw * 2.775));
		}
		else
		{
			isRangeClear = _robot->isRangeClear
				(_robot->getLaserSpec() - (distanceBetweenYaw * 2.775),_robot->getLaserSpec());
		}

		cout << "GoToPoint::stopCond , result: " << (!isRangeClear || (absYawDistance <= 2)) << endl;
		return(!isRangeClear || (absYawDistance <= 2));
	}

	void GoToPoint::action()
	{
		cout << "GoToPoint action" << endl;
		if(isRight)
		{
			_robot->setSpeed(0.0, -0.4);
		}
		else
		{
			_robot->setSpeed(0.0, 0.4);
		}
	}


