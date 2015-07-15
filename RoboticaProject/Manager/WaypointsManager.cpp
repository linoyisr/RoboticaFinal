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

vector<Point> WaypointsManager::getWaypointsList()
{
	return wayPoints;
}

void WaypointsManager::CreateWaypoints()
{
	int numOfJumps = 3;

	for(unsigned i=0; i< astarPath.size(); i += numOfJumps){
		this->wayPoints.push_back(astarPath[i]);
	}

	if ((astarPath.size() % numOfJumps) != 0){
		this->wayPoints.push_back(astarPath[astarPath.size() -1]);
	}

	wayPoints.erase(wayPoints.begin());
}

WaypointsManager::~WaypointsManager()
{
}
