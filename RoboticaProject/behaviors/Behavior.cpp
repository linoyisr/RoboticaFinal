/*
 * Behavior.cpp
 */

#include "Behavior.h"

Behavior::Behavior(Robot* robot) {
	_robot = robot;

}

Behavior::~Behavior() {
}

void Behavior::StartMove()
{
	_robot->setSpeed(0.3, 0.0);

	/*Location* newLoc;*/
	Point* robotLoc = _robot->getRobotLocation()->GetPoint();
	if (robotLoc->GetX() > _wayPoint->GetX() && robotLoc->GetY() > _wayPoint->GetY())
	{
	/*	newLoc = new Location(robotLoc->GetX()-1, robotLoc->GetY()-1, 0); */
	}
	else if (robotLoc->GetX() < _wayPoint->GetX() && robotLoc->GetY() < _wayPoint->GetY())
	{
	/*	newLoc = new Location(robotLoc->GetX()+1, robotLoc->GetY()+1, 0);*/
	}
	else if (robotLoc->GetX() > _wayPoint->GetX() && robotLoc->GetY() < _wayPoint->GetY())
	{
	/*	newLoc = new Location(robotLoc->GetX()-1, robotLoc->GetY()+1, 0);*/
	}
	else if (robotLoc->GetX() < _wayPoint->GetX() && robotLoc->GetY() > _wayPoint->GetY())
	{
	/*	newLoc = new Location(robotLoc->GetX()+1, robotLoc->GetY()-1, 0);*/
	}
	/*_robot->updateRobotLocation(newLoc);*/
}

void Behavior::SetWayPoint(Point* p)
{
	_wayPoint = p;
}

bool Behavior::StopCond()
{
	Point* robotLoc = _robot->getRobotLocation()->GetPoint();
	if (robotLoc->GetX() == _wayPoint->GetX() && robotLoc->GetY() == _wayPoint->GetY())
		return true;
	else
		return false;
}

/*
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
*/
