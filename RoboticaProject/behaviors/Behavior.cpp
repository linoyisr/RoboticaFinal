/*
 * Behavior.cpp
 */

#include "Behavior.h"

Behavior::Behavior(Robot* robot)
{
	_robot = robot;
	_nextBehavior = NULL;
	_behaviorsCount = 0;
}

Behavior* Behavior::addNextBehavior(Behavior* behavior){

	Behavior** behaviors = new Behavior*[_behaviorsCount + 1];

	for (int i = 0; i < _behaviorsCount; ++i)
	{
		behaviors[i] = _nextBehavior[i];
	}

	behaviors[_behaviorsCount] = behavior;
	delete [] _nextBehavior;
	_behaviorsCount++;

	_nextBehavior = behaviors;
	return this;
}

Behavior* Behavior::selectNextBehavior(){

	int i;
	for(i=0; i<_behaviorsCount; i++)
		if(_nextBehavior[i]->startCond())
			return _nextBehavior[i];

	return NULL;
}

Behavior::~Behavior() {

	delete [] _nextBehavior;
}
