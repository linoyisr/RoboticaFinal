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
	_pathPlanner = new PathPlanner();
	_pathPlanner->FindPath(_map->getBlowMapMatrix(), _map->getGridPointBy(_startPoint), _map->getGridPointBy(_goalPoint));
	_waypointsManager = new WaypointsManager(_pathPlanner->GetPathToGoal());
	_obstacleAvoid = new PlnObstacleAvoid(_robot, _waypointsManager);
	_currBehavior = _obstacleAvoid->getStartBehavior();
	_locManager = new LocalizationManager(_robot->getEstimateLocation(), _map);
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
	Location loc(_map->getGridPointBy(_startPoint), yawStart);
	_location = loc;
	_robot->updateRobotEstimateLocation(loc);

	string goalString = cfg.getValueOfKey("goal");
	vector<int> goalArray = cfg.ConvertStringToIntArray(goalString);

	int xGoal = goalArray[0];
	int yGoal = goalArray[1];
	Point goalPoint(xGoal, yGoal);
	_goalPoint = goalPoint;
}

void Manager::run()
{
	wayPoints = _waypointsManager->wayPoints;

	cout << "Way points:" <<endl;
	for (unsigned int i = 0; i< wayPoints.size(); i++)
	{
		wayPoints[i].PrintPoint();
	}

	_robot->Read();

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

				/*
				Point robotLocation = new Point(_robot->getRobotLocation().GetPoint().GetX(),
						 _robot->getRobotLocation().GetPoint().GetY());
				vector<Point>::iterator wpoint =
						find(wayPoints.begin(), wayPoints.end(), robotLocation);*/
				vector<Point>::iterator wpoint;
				for (vector<Point>::iterator iter = _waypointsManager->wayPoints.begin(); iter != _waypointsManager->wayPoints.end(); iter++)
				{//iterate through the vector to look for the correct name

					/*
					if((*iter).GetX() == _robot->getEstimateLocation().GetPoint().GetX() &&
							(*iter).GetY() == _robot->getEstimateLocation().GetPoint().GetY())*/

					if((*iter).GetX() == _robot->getEstimateLocation().GetPoint().GetX() &&
						(*iter).GetY() == _robot->getEstimateLocation().GetPoint().GetY())
					{
						wpoint = iter;
					}
				}

				// check if robot location is in waypoints list
				if (wpoint != wayPoints.end())
					break;

				if (!_currBehavior)
					break;
			}

			_currBehavior->action();

			_robot->Read();
/*
			Location deltaLocation = _robot->getDeltaLocation();
			float laserScans[LASERS_NUMBER];
			getLaserScan(laserScans);
*/
			//_locManager->Update(deltaLocation, laserScans);
			//_robot->updateRobotEstimateLocation(_locManager->GetBestLocation());
			//_robot->updateRobotEstimateLocation(_robot->getCurrentOdometryLocation());
		}
	}
}

Manager::~Manager() {
	// TODO Auto-generated destructor stub
}
