/*
 * GoForward.h
 */

#ifndef GOFORWARD_H_
#define GOFORWARD_H_

#include "Behavior.h"
#include "../Robot.h"
#include "../Manager/WaypointsManager.h"

class GoForward: public Behavior {

public:
	GoForward(Robot* robot,  WaypointsManager* waypointsManager);
	bool startCond();
	bool stopCond();
	void action();
	virtual ~GoForward();

private:
	WaypointsManager* _waypointsManager;
};

#endif /* GOFORWARD_H_ */
