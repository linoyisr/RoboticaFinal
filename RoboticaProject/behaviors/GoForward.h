/*
 * GoForward.h
 */

#ifndef GOFORWARD_H_
#define GOFORWARD_H_


#include "Behavior.h"
#include "../Robot.h"
#include "../Manager/WaypointsManager.h"
#include <iostream>
#include <math.h>
#include "../Point.h"
#include "../Location.h"
#include <vector>
#include <iterator>

using namespace std;

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
