/*
 * WaypointsManager.cpp
 *
 *  Created on: Jun 26, 2015
 *      Author: colman
 */

#include "WaypointsManager.h"

WaypointsManager::WaypointsManager(vector<Point> path)
{
	astarPath = path;
	CreateWaypoints();
}

WaypointsManager::WaypointsManager()
{
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
			nextWayPoint = astarPath[i + 1];
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
	currentWayPoint.SetX(next.GetX());
	currentWayPoint.SetY(next.GetY());
}

double WaypointsManager::calc_yaw()
{
	double m = calc_incline();
	double angle;

	if(!isVerticle)
	{
		angle = 180 * atan(m) / M_PI;
	}

	if (isVerticle)
	{
		if (nextWayPoint.GetY() > currentWayPoint.GetY())
		{
			return (270);
		}
		else
		{
			return (90);
		}
	}
	else if ( m == 0)
	{
		if (nextWayPoint.GetX() > currentWayPoint.GetX())
		{
			return (angle);
		}
		else
		{
			return (180 + angle);
		}
	}
	else if (m > 0)
	{
		if (nextWayPoint.GetY() > currentWayPoint.GetY())
		{
			return (360 - angle);
		}
		else
		{
			return (180 - angle);
		}
	}
	else
	{
		if (nextWayPoint.GetY() > currentWayPoint.GetY())
		{
			return (180 + angle);
		}
		else
		{
			return (angle);
		}
	}
}

double WaypointsManager::calc_incline()
{
	isVerticle = 0;
	if(currentWayPoint.GetX() == nextWayPoint.GetX())
	{
		isVerticle = 1;
		// TODO- CHECK if ok
		return(9999);
	}
	else
	{
		return((nextWayPoint.GetY() - currentWayPoint.GetY()) /
				(nextWayPoint.GetX() - currentWayPoint.GetX()));
	}
}

WaypointsManager::~WaypointsManager()
{
}
