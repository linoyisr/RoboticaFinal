/*
 * main.cpp
 */
#include "Map.h"
#include "Robot.h"
#include "Manager.h"
#include "Location.h"
#include "Manager/ConfigurationManager.h"
#include "Plans/PathPlanner.h"
#include "Plans/PlnObstacleAvoid.h"
#include <stdio.h>
#include <stdlib.h>
#include <ostream>
#include <string>

typedef basic_stringstream<char> stringstream;
using namespace std;

int main()
{
	// TODO: Move this code (read from config) to MAP class
/*	string mapPngPath;
	string startLocationString;
	int xStart;
	int yStart;
	int yawStart;
	string goalString;
	int xGoal;
	int yGoal;
	string robotSizeString;
	int robotHeight;
	int robotWidth;
	double MapResolutionCM;
	double GridResolutionCM;

	ConfigurationManager cfg("parameters.txt");

	mapPngPath = cfg.getValueOfKey("map");

	startLocationString = cfg.getValueOfKey("startLocation");

	// convert string with spaces to array
	vector<int> startLocationArray;
	stringstream ss1(startLocationString);
	int temp1;
	while (ss1 >> temp1)
		startLocationArray.push_back(temp1);

	xStart = startLocationArray[0];
	yStart = startLocationArray[1];
	Point startPoint(xStart, yStart);
	yawStart = startLocationArray[2];
	Location loc(&startPoint, yawStart);

	goalString = cfg.getValueOfKey("goal");
	// convert string with spaces to array
	vector<int> goalArray;
	stringstream ss2(goalString);
	int temp2;
	while (ss2 >> temp2)
		goalArray.push_back(temp2);

	xGoal = goalArray[0];
	yGoal = goalArray[1];

	robotSizeString = cfg.getValueOfKey("robotSize");
	// convert string with spaces to array
	vector<int> robotSizeArray;
	stringstream ss3(robotSizeString);
	int temp3;
	while (ss3 >> temp3)
		robotSizeArray.push_back(temp3);

	robotHeight = robotSizeArray[0];
	robotWidth = robotSizeArray[1];

	MapResolutionCM = atof(cfg.getValueOfKey("MapResolutionCM").c_str());
	GridResolutionCM = atof(cfg.getValueOfKey("GridResolutionCM").c_str());
*/

	// TODO: This code try PathPlanner (aStar)
/*	PathPlanner planner;
	Point startPoint(2, 3);
	Point endPoint(6, 6);
	vector<vector<int>> grid(7,vector<int>(7));

	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[i].size(); j++)
		{
			grid[i][j] = 0;
		}
	}

	grid[2][5] = 1;
	grid[3][5] = 1;
	grid[4][5] = 1;
	grid[4][4] = 1;
	grid[5][4] = 1;
	grid[5][3] = 1;

	planner.FindPath(grid, startPoint, endPoint);

	vector<Point*> pathToGoal = planner.GetPathToGoal();
	for (int i = 0; i < pathToGoal.size(); i++)
	{
		Point* point = pathToGoal[i];
		grid[point->GetX()][point->GetY()] = 8;
	}


	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[i].size(); j++)
		{
			if (grid[i][j] == 0)
				cout << '0';
			else if (grid[i][j] == 1)
				cout << 'X';
			else if (grid[i][j] == 8)
				cout << '1';
			else
				cout << "?";
		}
		cout << "\n";
	}
*/

	Map * map = new Map(); //TODO:not sould be here
	Robot robot("localhost",6665);
	PlnObstacleAvoid plnOA(&robot);
	Manager manager(&robot, &plnOA);
	manager.run();

	return 0;
}
