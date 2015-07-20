/*
 * main.cpp
 */
#include "Map.h"
#include "Robot.h"
#include "Manager.h"
#include "Plans/PathPlanner.h"
#include "Plans/PlnObstacleAvoid.h"
using namespace std;

int main()
{
	Robot robot("localhost",6665);
	Manager manager(&robot);
	manager.run();

	return 0;
}
