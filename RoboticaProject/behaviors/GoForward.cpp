/*
 * GoForward.cpp
 */

#include "GoForward.h"

GoForward::GoForward(Robot* robot):Behavior(robot){
	// TODO Auto-generated constructor stub

}

GoForward::~GoForward() {
	// TODO Auto-generated destructor stub
}

bool GoForward::startCond()
{
	return _robot->isForwardFree();
}
bool GoForward::stopCond()
{
	//TODO: Until Obstacle
	return false;
}

void GoForward::action()
{
	// Fix this number
	_robot->setSpeed(0.0, 0.3);
}

void GoForward::stopAction()
{
	_robot->setSpeed(0.0, 0.0);
}

