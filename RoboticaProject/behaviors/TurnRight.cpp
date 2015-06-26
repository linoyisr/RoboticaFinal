/*
 * TurnRight.cpp
 */

#include "TurnRight.h"

TurnRight::TurnRight(Robot* robot):Behavior(robot) {
	// TODO Auto-generated constructor stub

}

TurnRight::~TurnRight() {
	// TODO Auto-generated destructor stub
}

bool TurnRight::startCond()
{
	return _robot->isRightFree();
}
bool TurnRight::stopCond()
{
	return _robot->isForwardFree();
}

void TurnRight::action()
{
	// Fix this number
	_robot->setSpeed(0.0, 0.3);
}

void TurnRight::stopAction()
{
	_robot->setSpeed(0.0, 0.0);
}
