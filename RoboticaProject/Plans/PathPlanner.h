/*
 * PathPlanner.h
 *
 *  Created on: Jun 26, 2015
 *      Author: colman
 */

#ifndef PATHPLANNER_H_
#define PATHPLANNER_H_

#include "../Point.h"
#include "Node.h"
#include <vector>
#include <algorithm>

using namespace std;

class PathPlanner {
public:
	PathPlanner(void);
	~PathPlanner(void);

	void FindPath(vector<vector<int> > pngGrid, Point currentPos, Point targetPos);
	Point NextPathPos(Point currentPoint);
	void ClearOpenList()
	{
		m_openList.clear();
	}

	void ClearVisitedList()
	{
		m_visitedList.clear();
	}

	void ClearPathToGoal()
	{
		m_pathToGoal.clear();
	}

	vector<Point*> GetPathToGoal()
	{
		return m_pathToGoal;
	}

	bool m_initializedStartGoal;
	bool m_foundGoal;

private:
	void SetStartAndGoal(Node strat, Node goal);
	void pathOpened(int x, int z, float newCost, Node *parent);
	Node *GetNextCell();
	void ContinuePath();

	Node *m_startCell;
	Node *m_goalCell;
	vector<Node*> m_openList;
	vector<Node*> m_visitedList;
	vector<Point*> m_pathToGoal;

	vector<vector<int> > m_pngGrid;
};

#endif /* PATHPLANNER_H_ */
