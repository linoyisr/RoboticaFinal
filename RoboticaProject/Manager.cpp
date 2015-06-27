/*
 * Manager.cpp
 */

#include "Manager.h"


Manager::Manager(Robot* robot)
{
	_map = new Map();
	_robot = robot;
	_pathPlanner = new PathPlanner();
	_obstacleAvoid = new PlnObstacleAvoid(_robot);
	_currBehavior = _obstacleAvoid->getStartBehavior();
	_locManager = new LocalizationManager(_map);
}

void Manager::getLaserScan(float* laserScans)
{
	for (int i = 0; i < 666; i++)
	{
		laserScans[i] = _robot->getLaserByIndex(i);
	}
}

void Manager::setStartAndGoal()
{
	ConfigurationManager cfg("parameters.txt");

	string startString = cfg.getValueOfKey("startLocation");
	vector<int> startArray = cfg.ConvertStringToIntArray(startString);

	int xStart = startArray[0];
	int yStart = startArray[1];
	Point startPoint(xStart, yStart);
	_startPoint = startPoint;
	int yawStart = startArray[2];
	Location loc(&_startPoint, yawStart);
	_location = &loc;

	string goalString = cfg.getValueOfKey("goal");
	vector<int> goalArray = cfg.ConvertStringToIntArray(goalString);

	int xGoal = goalArray[0];
	int yGoal = goalArray[1];
	Point goalPoint(xGoal, yGoal);
	_goalPoint = goalPoint;
}

void Manager::run()
{
	_pathPlanner->FindPath(_map->getMatrix(), _startPoint, _goalPoint);
	_waypointsManager = new WaypointsManager(_pathPlanner->GetPathToGoal());

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
