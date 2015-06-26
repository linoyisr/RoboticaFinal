/*
 * Behavior.cpp
 */

#include "Behavior.h"

Behavior::Behavior(Robot* robot) {
	_robot = robot;

}

Behavior::~Behavior() {
	// TODO Auto-generated destructor stub
}

void Behavior::addBeh(Behavior* next)
{
	_behVect.push_back(next);
}

Behavior* Behavior::selectNext()
{
	//Run over vector and return first true
	//startCond of the first behavior

	for(size_t i = 0; i < _behVect.size(); i++)
	{
		if (_behVect[i]->startCond())
		{
			return _behVect[i];
		}
	}

	return NULL;
}
