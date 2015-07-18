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
		double yaw = _robot->getRobotLocation().GetYawPoint();
		diffrence = _waypointsManager->calc_yaw() - yaw;

		if(diffrence == 0)
		{
			return false;
		}
		else if(diffrence >= 180)
		{
			isRight =  1;
			//isRight =  0;
			diffrence = 360 - diffrence;
		}
		else if (diffrence < -180)
		{
			isRight = 0;
	//		isRight = 1;
			diffrence = 360 + diffrence;
		}
		else if (diffrence > 0)
		{
	//		isRight = 1;
			isRight = 0;
		}
		else
		{
			isRight = 1;
	//		isRight = 0;
			diffrence = abs(diffrence);
		}

		if(isRight)
		{
			//return (_robot.checkRange(0, diffrence * ONE_DEGREE_INDEXES));
			return (_robot->checkRange(0, diffrence * 2.4667));
		}
		else
		{
			//return(_robot.checkRange( _robot->getLaserSpec() - (diffrence * ONE_DEGREE_INDEXES),
			return(_robot->checkRange( _robot->getLaserSpec() - (diffrence * 2.4667),
					_robot->getLaserSpec()));
		}
	}

	bool GoToPoint::stopCond()
	{
		bool isRangeGood;
		int absResult;
		if(isRight)
		{
			// ONE_DEGREE_INDEXES = 2.4667
			isRangeGood = (_robot->checkRange(0, diffrence * 2.4667));
			absResult = abs(_robot->getRobotLocation().GetYawPoint() -
					_waypointsManager->calc_yaw());
		}
		else
		{
			// ONE_DEGREE_INDEXES = 2.4667
			isRangeGood = _robot->checkRange
					(_robot->getLaserSpec() - (diffrence * 2.4667),_robot->getLaserSpec());
			absResult = abs(_robot->getRobotLocation().GetYawPoint() -
					_waypointsManager->calc_yaw());
		}

		//absResult <= MAX_YAW_DIFF));
		return(!isRangeGood || (absResult <= 2));
	}

	void GoToPoint::action()
	{
		if(isRight)
		{
			_robot->setSpeed(0.0, -0.4);
		}
		else
		{
			_robot->setSpeed(0.0, 0.4);
		}
	}


