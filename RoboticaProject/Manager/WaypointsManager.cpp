/*
 * WaypointsManager.cpp
 *
 *  Created on: Jun 26, 2015
 *      Author: colman
 */

#include "WaypointsManager.h"

WaypointsManager::WaypointsManager(vector<Point*> path, double resolution)
{
	astarPath = path;
	mapResolution = resolution;
}

vector<Point*> WaypointsManager::getWaypointsList()
{
	return wayPoints;
}

void WaypointsManager::CreateWaypoints()
{
	int jumps = 3;

	for(unsigned i=0; i< astarPath.size(); i += jumps){
		this->wayPoints.push_back(astarPath[i]);
	}

	if ((astarPath.size() % jumps) != 0){
		this->wayPoints.push_back(astarPath[astarPath.size() -1]);
	}

	wayPoints.erase(wayPoints.begin());
}

WaypointsManager::~WaypointsManager()
{
}
