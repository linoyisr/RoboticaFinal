/*
 * AStarAlgorithm.h
 *
 *  Created on: Jun 20, 2015
 *      Author: colman
 */
/*
#ifndef ASTARALGORITHM_H_
#define ASTARALGORITHM_H_

#include "../Point.h"
#include "Node.h"
#include <vector>

using namespace std;

class AStarAlgorithm
{
	public:
	AStarAlgorithm(void);
	~AStarAlgorithm(void);

	void FindPath(Point currentPos, Point targetPos);
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

	bool m_initializedStartGoal;
	bool m_foundGoal;

	private:
	void SetStartAndGoal(Node strat, Node goal);
	void pathOpened (int x, int z, float newCost, Node *parent);
	Node *GetNextCell();
	void ContinuePath();

	Node *m_startCell;
	Node *m_goalCell;
	vector<Node*> m_openList;
	vector<Node*> m_visitedList;
	vector<Point*> m_pathToGoal;

};


#endif /* ASTARALGORITHM_H_*/
