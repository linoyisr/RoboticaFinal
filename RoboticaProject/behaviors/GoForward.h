/*
 * GoForward.h
 */

#ifndef GOFORWARD_H_
#define GOFORWARD_H_

#include "Behavior.h"

class GoForward: public Behavior {
public:
	GoForward(Robot* robot);
	virtual ~GoForward();

	bool startCond();
	bool stopCond();
	void action();
	void stopAction();
};

#endif /* GOFORWARD_H_ */
