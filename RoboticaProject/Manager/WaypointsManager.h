/*
 * WaypointsManager.h
 *
 *  Created on: Jun 26, 2015
 *      Author: colman
 */

#ifndef WAYPOINTSMANAGER_H_
#define WAYPOINTSMANAGER_H_

#include <vector>
#include <math.h>
#include "../Point.h"
using namespace std;

class WaypointsManager {
public:
	WaypointsManager(vector<Point> path);
	WaypointsManager();
	~WaypointsManager();
	void CreateWaypoints();
	vector<Point> getWaypointsList();
	void setNextWayPoint(Point nextWayPoint);
	bool isInWayPoint(double x,double y);

	double calc_yaw();
	double calc_incline();


	vector<Point> astarPath;
	vector<Point> wayPoints;
	Point currentWayPoint;
	Point nextWayPoint;
	bool isVerticle;
};

#endif /* WAYPOINTSMANAGER_H_ */
