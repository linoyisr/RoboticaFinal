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
	//Map* _map = new Map();
	Robot robot("localhost",6665);
	Manager manager(&robot);
	manager.run();



	/*
	 *
	 * if (lp[2] < 0.8)
		{
			if(lp[1] < lp[3])
				pp.SetSpeed(0.8, 1.9);
			else
				pp.SetSpeed(0.8, -1.9);
		}
		else if (lp[1] < 0.5)
			pp.SetSpeed(0.8, 0.6);
		else if (lp[3] < -0.5)
			pp.SetSpeed(0.8, -0.6);
		else if (lp[0] < 0.3)
			pp.SetSpeed(0.8, 0.4);
		else if (lp[4] < -0.3)
			pp.SetSpeed(0.8, -0.4);
		else
			pp.SetSpeed(0.8, 0.0);
	 */
	return 0;
}
