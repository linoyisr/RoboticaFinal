/*
 * WaypointsManager.h
 *
 *  Created on: Jun 26, 2015
 *      Author: colman
 */

#ifndef WAYPOINTSMANAGER_H_
#define WAYPOINTSMANAGER_H_

#include <vector>
#include <cmath>
#include "../Robot.h"
#include "../Point.h"
using namespace std;

class WaypointsManager {
public:
	WaypointsManager(vector<Point> path, Robot* r);
	WaypointsManager();
	~WaypointsManager();
	void CreateWaypoints();
	vector<Point> getWaypointsList();
	void setNextWayPoint(Point nextWayPoint);
	bool isInWayPoint(double x,double y);

	double calcYaw();
	double calcIncline();


	vector<Point> astarPath;
	vector<Point> wayPoints;
	Point currentWayPoint;
	Point nextWayPoint;
	bool isVerticle;
	bool initPointsFirstTime;
	double minDistance;
	Robot* _robot;
};

#endif /* WAYPOINTSMANAGER_H_ */
