/*
 * Manager.cpp
 */

#include "Manager.h"


Manager::Manager(Robot* robot, Plan* pln, LocalizationManager* locManager)
{
	_robot = robot;
	_curr = pln->getStartPoint();
	_localizationManager = locManager;
}

void Manager::run()
{
	_robot->Read();
	if((!(_curr->startCond())) || _curr == NULL)
		return;
	_curr->action();
	while(_curr !=NULL)
	{
		while(_curr->stopCond() == false)
		{
			_curr->action();
			_robot->Read();
		}
		_curr = _curr->selectNext();
		_robot->Read();
	}
}

Manager::~Manager() {
	// TODO Auto-generated destructor stub
}
