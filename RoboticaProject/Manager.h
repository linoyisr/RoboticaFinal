/*
 * Manager.h
 */

#ifndef MANAGER_H_
#define MANAGER_H_
#include "Plans/PlnObstacleAvoid.h"
#include "Robot.h"
#include "behaviors/Behavior.h"
#include "Manager/LocalizationManager.h"

class Manager {
private:
	Behavior* _currBehavior;
	Robot* _robot;
	LocalizationManager* _locManager;

	void getLaserScan(float* laserScans);

public:
	Manager(Robot* robot, Plan* pln, LocalizationManager* locManager);
	void run();
	virtual ~Manager();
};

#endif /* MANAGER_H_ */
