/*
 * Manager.h
 */

#ifndef MANAGER_H_
#define MANAGER_H_
#include "Plans/PlnObstacleAvoid.h"
#include "Robot.h"
#include "behaviors/Behavior.h"
#include "Manager/LocalizationManager.h"
#include "Manager/ConfigurationManager.h"
#include "Plans/PathPlanner.h"
#include "Point.h"
#include <vector>

class Manager {
private:
	Point _startPoint;
	Point _goalPoint;
	Location* _location;
	Behavior* _currBehavior;
	Map* _map;
	Robot* _robot;
	LocalizationManager* _locManager;
	PlnObstacleAvoid* _obstacleAvoid;
	WaypointsManager* _waypointsManager;
	PathPlanner* _pathPlanner;
	vector<Point*> wayPoints;

	void getLaserScan(float* laserScans);
	void setStartAndGoal();

public:
	Manager(Robot* robot);
	void run();
	virtual ~Manager();
};

#endif /* MANAGER_H_ */
