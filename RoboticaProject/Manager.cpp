/*
 * Manager.cpp
 */

#include "Manager.h"


Manager::Manager(Robot* robot, Plan* pln, LocalizationManager* locManager)
{
	_robot = robot;
	_currBehavior = pln->getStartBehavior();
	_locManager = locManager;
}

void Manager::getLaserScan(float* laserScans)
{
	for (int i = 0; i < 666; i++)
	{
		laserScans[i] = _robot->getLaserByIndex(i);
	}
}

void Manager::run()
{
	_robot->Read();

	if((!(_currBehavior->startCond())) || _currBehavior == NULL)
		return;

	_currBehavior->action();
	int loopsCounter = 1;

	while(_currBehavior !=NULL)
	{
		while(!_currBehavior->stopCond())
		{
			_currBehavior->action();
			_robot->Read();

			// Every 15 reads make all the calculations and update the particles and their corresponding data
			if (loopsCounter == 15)
			{
				loopsCounter = 0;
				double deltaX;
				double deltaY;
				double deltaYaw;
				// What is 666 ? ask orli/aviram
				float laserScans[666];
				getLaserScan(laserScans);

				Location location(deltaX, deltaY, deltaYaw);
				_robot->updateRobotLocation(location);
				_locManager->Update(location, laserScans);
			}
			else
				loopsCounter++;

		}
		_currBehavior = _currBehavior->selectNext();
		_robot->Read();
	}
}

Manager::~Manager() {
	// TODO Auto-generated destructor stub
}
