/*
 * Plan.h
 */

#ifndef PLAN_H_
#define PLAN_H_
#include "../behaviors/Behavior.h"
#include "../Robot.h"
class Plan {

protected:
	Robot* _robot;
	Behavior* _startBehavior;
	Behavior** _behaviors;
public:
	Plan(Robot* robot);
	virtual Behavior* getStartBehavior(){return _startBehavior;}
	virtual ~Plan();
};

#endif /* PLAN_H_ */
