/*
 * TurnRight.h
 */

#ifndef TURNRIGHT_H_
#define TURNRIGHT_H_

#include "Behavior.h"

class TurnRight: public Behavior {
public:
	TurnRight(Robot* robot);
	virtual ~TurnRight();

	bool startCond();
	bool stopCond();
	void action();
	void stopAction();
};

#endif /* TURNRIGHT_H_ */
