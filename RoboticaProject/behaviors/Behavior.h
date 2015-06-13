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
	void addBeh(Behavior* next)
	{
		_behVect.push_back(next);
	}
	Behavior* selectNext()
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

};

#endif /* BEHAVIOR_H_ */
