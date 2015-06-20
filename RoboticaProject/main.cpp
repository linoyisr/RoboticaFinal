/*
 * main.cpp
 */
#include "Robot.h"
#include "Manager.h"
#include "Configuration.h"
#include "Plans/PlnObstacleAvoid.h"
int main()
{
	Configuration cfg("parameters.txt");

	bool exists = cfg.keyExists("GridResolutionCM");
	cout << "GridResolutionCM key: " << boolalpha << exists << "\n";

	string GridResolutionCMValue = cfg.getValueOfKey<string>("GridResolutionCM");
	cout << "value of key GridResolutionCM: " << GridResolutionCMValue << "\n";

	std::cin.get();




	Robot robot("localhost",6665);
	PlnObstacleAvoid plnOA(&robot);
	Manager manager(&robot, &plnOA);
	manager.run();



	return 0;
}
