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

void Manager::run()
{
	_robot->Read();

	if((!(_currBehavior->startCond())) || _currBehavior == NULL)
		return;

	_currBehavior->action();
	int loopsCounter = 1;

	while(_currBehavior !=NULL)
	{
		/*while(!_currBehavior->stopCond())
		{
			_currBehavior->action();
			_robot->Read();

			// Every 15 reads make all the calculations and update the particles and their corresponding data
			if (loopsCounter == 15)
			{
				double deltaX;
				double deltaY;
				double deltaYaw;
				float *laserScans = this->_robot->getLaserScan();

				// Set robot delta values by its odometry
				this->_robot->SetDeltaValues(deltaX, deltaY, deltaYaw);

				_locManager->Update(deltaX,deltaY, deltaYaw, laserScans);

				loopsCounter = 0;
			}
			else
				loopsCounter++;

		}*/
		_currBehavior = _currBehavior->selectNext();
		_robot->Read();
	}
}

Manager::~Manager() {
	// TODO Auto-generated destructor stub
}
