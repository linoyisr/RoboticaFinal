/*
 * TurnAround.h
 *
 *  Created on: Jun 27, 2015
 *      Author: colman
 */
/*
#ifndef TURNAROUND_H_
#define TURNAROUND_H_

#include "Behavior.h"

class TurnAround: public Behavior {
public:
	TurnAround(Robot* robot);
	virtual ~TurnAround();

	bool startCond();
	bool stopCond();
	void action();
	void stopAction();
};

#endif /* TURNAROUND_H_ */
