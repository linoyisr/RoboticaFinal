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

void WaypointsManager::getWaypointsList()
{

}

WaypointsManager::~WaypointsManager()
{
}
