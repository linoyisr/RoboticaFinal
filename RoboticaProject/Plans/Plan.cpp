/*
 * Plan.cpp
 */

#include "Plan.h"

Plan::Plan(Robot* robot) {
	_startBehavior = NULL;
	_robot = robot;
}

Plan::~Plan() {
	// TODO Auto-generated destructor stub
}
