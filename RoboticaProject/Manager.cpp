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

	for (int i = 0; i < _waypointsManager->wayPoints.size(); i++)
	{
		Point currentWayPoint = _waypointsManager->wayPoints[i];
		cout << endl << "Work on Waypoint: x - " << currentWayPoint.GetX() << " y - "
				<<currentWayPoint.GetY();
		_robot->Read();

		if (i < _waypointsManager->wayPoints.size() - 1)
			_waypointsManager->setNextWayPoint(_waypointsManager->wayPoints[i]);
		_currBehavior->startCond();

		while (true)
		{
			// If the current behavior can't run
			if(_currBehavior->stopCond())
			{
				_robot->setSpeed(0,0);
				_robot->Read();
				// Perform the next behavior according to the plan
				_currBehavior = _currBehavior->selectNextBehavior();

				/*
				vector<Point>::iterator wpoint;
				for (vector<Point>::iterator iter = _waypointsManager->wayPoints.begin(); iter != _waypointsManager->wayPoints.end(); iter++)
				{//iterate through the vector to look for the correct name

					if((*iter).GetX() == _robot->getEstimateLocation().GetPoint().GetX() &&
						(*iter).GetY() == _robot->getEstimateLocation().GetPoint().GetY())
					{
						wpoint = iter;
						cout << endl << "robot in waypoint" << endl;
					}
				}
				*/

				Point wpoint(99999,99999);
				for(int i = 0; i < _waypointsManager->wayPoints.size(); i++)
				{
					if((_waypointsManager->wayPoints[i]).GetX() == _robot->getEstimateLocation().GetPoint().GetX() &&
						(_waypointsManager->wayPoints[i]).GetY() == _robot->getEstimateLocation().GetPoint().GetY())
					{
						wpoint = _waypointsManager->wayPoints[i];
						cout << endl << "robot in waypoint" << endl;
					}
				}

				// check if robot location is in waypoints list
				if (wpoint.GetX() != 99999 || wpoint.GetY() != 99999)
				{
					cout << endl << "wayPoints break" << endl;
					break;
				}

				if (!_currBehavior)
				{
					cout << endl << "behavoir break" << endl;
					break;
				}
			}

			_currBehavior->action();

			_robot->Read();

			Location deltaLocation = _robot->getDeltaLocation();
			float laserScans[LASERS_NUMBER];
			getLaserScan(laserScans);

			_locManager->Update(deltaLocation, laserScans);
			_robot->updateRobotEstimateLocation(_locManager->GetBestLocation());
			//cout << "best location: ";
			//_locManager->GetBestLocation().Print();
			//cout << endl;
			//_robot->updateRobotEstimateLocation(Location(Point(87,73),15));
			//_robot->updateRobotEstimateLocation(_robot->getCurrentOdometryLocation());
		}
	}
}

Manager::~Manager() {
	// TODO Auto-generated destructor stub
}
