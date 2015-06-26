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
	Behavior* _currBehavior;
	Robot* _robot;
	LocalizationManager* _locManager;
public:
	Manager(Robot* robot, Plan* pln, LocalizationManager* locManager);
	void run();
	virtual ~Manager();
};

#endif /* MANAGER_H_ */
