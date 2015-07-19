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
		{
			return false;
		}
		else if(distanceBetweenYaw >= 180)
		{
			isRight =  1;
			//isRight =  0;
			distanceBetweenYaw = 360 - distanceBetweenYaw;
		}
		else if (distanceBetweenYaw < -180)
		{
			isRight = 0;
	//		isRight = 1;
			distanceBetweenYaw = 360 + distanceBetweenYaw;
		}
		else if (distanceBetweenYaw > 0)
		{
	//		isRight = 1;
			isRight = 0;
		}
		else
		{
			isRight = 1;
	//		isRight = 0;
			distanceBetweenYaw = abs(distanceBetweenYaw);
		}

		bool result;
		if(isRight)
		{
			//return (_robot.checkRange(0, distanceBetweenYaw * ONE_DEGREE_INDEXES));
			//return (_robot->isRangeClear(0, distanceBetweenYaw * 2.4667));
			result = (_robot->isRangeClear(0, distanceBetweenYaw * 2.775));
		}
		else
		{
			//return(_robot.checkRange( _robot->getLaserSpec() - (diffrence * ONE_DEGREE_INDEXES),
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
		int waypointYaw = _waypointsManager->calcYaw();
		cout << robotYaw <<endl;

		int absYawDistance = abs(robotYaw - waypointYaw);
		if(isRight)
		{
			// ONE_DEGREE_INDEXES = 2.4667
			isRangeClear = (_robot->isRangeClear(0, distanceBetweenYaw * 2.775));
		}
		else
		{
			// ONE_DEGREE_INDEXES = 2.4667
			isRangeClear = _robot->isRangeClear
				(_robot->getLaserSpec() - (distanceBetweenYaw * 2.775),_robot->getLaserSpec());
		}

		//absResult <= MAX_YAW_DIFF));
		cout << "GoToPoint::stopCond , result: " << (!isRangeClear || (absYawDistance <= 3)) << endl;
		return(!isRangeClear || (absYawDistance <= 3));
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


