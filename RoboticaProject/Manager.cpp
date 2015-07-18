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
	Location loc(_startPoint, yawStart);
	_location = loc;
	_robot->updateRobotLocation(loc);

	string goalString = cfg.getValueOfKey("goal");
	vector<int> goalArray = cfg.ConvertStringToIntArray(goalString);

	int xGoal = goalArray[0];
	int yGoal = goalArray[1];
	Point goalPoint(xGoal, yGoal);
	_goalPoint = goalPoint;
}

void Manager::run()
{
	_pathPlanner->FindPath(_map->getBlowMapMatrix(), _map->getGridPointBy(_startPoint), _map->getGridPointBy(_goalPoint));
	_waypointsManager = new WaypointsManager(_pathPlanner->GetPathToGoal());
	wayPoints = _waypointsManager->wayPoints;
	_robot->Read();

	double dTeta = _robot->getRobotLocation().GetYawPoint();

	vector<Point>::iterator it;
	for (it = (_waypointsManager->wayPoints).begin(); it != (_waypointsManager->wayPoints).end(); ++it)
	{
		Point currentWayPoint = *it;
		_robot->Read();

		_waypointsManager->setNextWayPoint(currentWayPoint);
		_currBehavior->startCond();

		while (true)
		{
			// If the current behavior can't run
			if(_currBehavior->stopCond())
			{
				_robot->Read();
				// Perform the next behavior according to the plan
				_currBehavior = _currBehavior->selectNextBehavior();

				Point robotLocation = new Point(_robot->getRobotLocation().GetPoint().GetX(),
						 _robot->getRobotLocation().GetPoint().GetY());
				vector<Point>::iterator wpoint =
						find(wayPoints.begin(), wayPoints.end(), robotLocation);

				// check if robot location is in waypoints list
				if (wpoint != wayPoints.end())
					break;

				if (!_currBehavior)
					break;
			}

			_currBehavior->action();

			_robot->Read();

			Location deltaLocation = _robot->getDeltaLocation();
			float laserScans[LASERS_NUMBER];
			getLaserScan(laserScans);
			//_robot->updateRobotLocation(deltaLocation);
			_locManager->Update(deltaLocation, laserScans);
		}
	}
}

Manager::~Manager() {
	// TODO Auto-generated destructor stub
}
