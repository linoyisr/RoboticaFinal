/*
 * WaypointsManager.cpp
 *
 *  Created on: Jun 26, 2015
 *      Author: colman
 */

#include "WaypointsManager.h"

WaypointsManager::WaypointsManager(vector<Point> path)
{
	initPointsFirstTime = true;
	astarPath = path;
	minDistance = 99999;
	CreateWaypoints();
}

WaypointsManager::WaypointsManager()
{
	initPointsFirstTime = true;
	minDistance = 99999;
}

vector<Point> WaypointsManager::getWaypointsList()
{
	return wayPoints;
}

void WaypointsManager::CreateWaypoints()
{
	int numOfJumps = 3;

	for(unsigned i=0; i< astarPath.size(); i += numOfJumps)
	{
		if(i == 0)
		{
			currentWayPoint = astarPath[i];
			//nextWayPoint = astarPath[i + numOfJumps];
		}
		this->wayPoints.push_back(astarPath[i]);
	}

	if ((astarPath.size() % numOfJumps) != 0)
	{
		this->wayPoints.push_back(astarPath[astarPath.size() -1]);
	}
}

void WaypointsManager::setNextWayPoint(Point next)
{
	if (!initPointsFirstTime)
	{
		currentWayPoint.SetX(nextWayPoint.GetX());
		currentWayPoint.SetY(nextWayPoint.GetY());
	}

	nextWayPoint.SetX(next.GetX());
	nextWayPoint.SetY(next.GetY());
	initPointsFirstTime = false;
}

double WaypointsManager::calcYaw()
{
	cout << endl <<"current waypoint : " ;
	currentWayPoint.PrintPoint();
	cout << endl <<"next waypoint : " ;
	nextWayPoint.PrintPoint() ;
	cout << endl;
	double angle;

	cout << endl << "atan Y " << -(nextWayPoint.GetY() - currentWayPoint.GetY());
	cout << endl << "atan X " << (nextWayPoint.GetX() - currentWayPoint.GetX());
	angle = atan2(-(nextWayPoint.GetY() - currentWayPoint.GetY()) ,
			(nextWayPoint.GetX() - currentWayPoint.GetX()));

	return angle *180/M_PI;
}

double WaypointsManager::calcIncline()
{
	isVerticle = 0;
	if(currentWayPoint.GetX() == nextWayPoint.GetX())
	{
		isVerticle = 1;
		return(9999);
	}
	else
	{
		return(-(nextWayPoint.GetY() - currentWayPoint.GetY()) /
				(nextWayPoint.GetX() - currentWayPoint.GetX()));
	}
}

WaypointsManager::~WaypointsManager()
{
}
