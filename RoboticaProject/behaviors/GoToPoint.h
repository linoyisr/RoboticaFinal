/*
 * GoToPoint.h
 *
 *  Created on: Jul 17, 2015
 *      Author: colman
 */

#ifndef GOTOPOINT_H_
#define GOTOPOINT_H_

#include "Behavior.h"
#include "../Manager/WaypointsManager.h"
#include "../Robot.h"

class GoToPoint: public Behavior {
public:
	GoToPoint(Robot* robot, WaypointsManager* waypointsManager);
	bool startCond();
	bool stopCond();
	void action();
	virtual ~GoToPoint();

private:
	WaypointsManager* _waypointsManager;
	bool isRight;
	double diffrence;
};

#endif /* GOTOPOINT_H_ */
