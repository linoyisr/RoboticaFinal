/*
 * Manager.cpp
 */

#include "Manager.h"
#include "LaserHelper.h"

Manager::Manager(Robot* robot)
{
	_map = new Map();
	_robot = robot;
	setStartAndGoal();
	_behavior = new Behavior(_robot);
	_pathPlanner = new PathPlanner();
	_obstacleAvoid = new PlnObstacleAvoid(_robot);
	_currBehavior = _obstacleAvoid->getStartBehavior();
	_locManager = new LocalizationManager(_robot->getRobotLocation(), _map);
}

void Manager::getLaserScan(float* laserScans)
{
	for (int i = 0; i < LASERS_NUMBER; i++)
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
	_robot->updateRobotLocation(&loc);

	string goalString = cfg.getValueOfKey("goal");
	vector<int> goalArray = cfg.ConvertStringToIntArray(goalString);

	int xGoal = goalArray[0];
	int yGoal = goalArray[1];
	Point goalPoint(xGoal, yGoal);
	_goalPoint = goalPoint;
}

void Manager::run()
{
	_pathPlanner->FindPath(_map->getGridMatrix(), _startPoint, _goalPoint);
	_waypointsManager = new WaypointsManager(_pathPlanner->GetPathToGoal());
	wayPoints = _waypointsManager->wayPoints;
	_robot->Read();

	int loopsCounter = 1;

	for(int i=0; i < wayPoints.size(); i++)
	{
		Point* currentPoint = wayPoints[i];
		_behavior->SetWayPoint(currentPoint);
		_behavior->StartMove();

		while(!_behavior->StopCond())
		{
			_behavior->StartMove();
			// Every 15 reads make all the calculations and update the particles and their corresponding data
			if (loopsCounter == 15)
			{
				loopsCounter = 0;
				Location deltaLocation = _robot->getDeltaLocation();

				float laserScans[LASERS_NUMBER];
				getLaserScan(laserScans);

				_robot->updateRobotLocation(&deltaLocation);
				_locManager->Update(deltaLocation, laserScans);
			}
			else
				loopsCounter++;

			_robot->Read();
		}
	}
}

Manager::~Manager() {
	// TODO Auto-generated destructor stub
}
