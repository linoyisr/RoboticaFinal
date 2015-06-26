/*
 * TurnLeft.h
 */

#ifndef TURNLEFT_H_
#define TURNLEFT_H_

#include "Behavior.h"

class TurnLeft: public Behavior {
public:
	TurnLeft(Robot* robot);
	virtual ~TurnLeft();

	bool startCond();
	bool stopCond();
	void action();
	void stopAction();
};

#endif /* TURNLEFT_H_ */
