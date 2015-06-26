/*
 * Plan.h
 */

#ifndef PLAN_H_
#define PLAN_H_
#include "../behaviors/Behavior.h"
#include "../Robot.h"
class Plan {

protected:
	Behavior* _start;
public:
	Plan(Robot* robot);
	virtual Behavior* getStartBehavior(){return _start;}
	virtual ~Plan();
};

#endif /* PLAN_H_ */
