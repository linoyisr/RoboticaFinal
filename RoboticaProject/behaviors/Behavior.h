/*
 * Behavior.h
 *
 *      Author: user
 */

#ifndef BEHAVIOR_H_
#define BEHAVIOR_H_
#include <vector>
#include "../Robot.h"
using namespace std;

class Behavior {
	vector<Behavior*> _behVect;
protected:
	Robot* _robot;
public:
	Behavior(Robot* robot);
	virtual ~Behavior();
	virtual bool startCond() = 0;
	virtual bool stopCond() = 0;
	virtual void action() = 0;
	virtual void stopAction() = 0;
	void addBeh(Behavior* next);
	Behavior* selectNext();

};

#endif /* BEHAVIOR_H_ */
