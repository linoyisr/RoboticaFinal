/*
 * WaypointsManager.h
 *
 *  Created on: Jun 26, 2015
 *      Author: colman
 */

#ifndef WAYPOINTSMANAGER_H_
#define WAYPOINTSMANAGER_H_

#include <vector>
#include "../Point.h"
using namespace std;

class WaypointsManager {
public:
	WaypointsManager(vector<Point*> path, double mapResolution);
	~WaypointsManager();

	void getWaypointsList();

	vector<Point*> astarPath;
	vector<Point*> wayPoints;
	double mapResolution;
};

#endif /* WAYPOINTSMANAGER_H_ */
