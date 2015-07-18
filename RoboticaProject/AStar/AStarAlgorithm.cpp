/*
 * AStarAlgorithm.cpp
 *
 *  Created on: Jun 20, 2015
 *      Author: colman
 */
/*
#include "AStarAlgorithm.h"


AStarAlgorithm::AStarAlgorithm(void)
{
m_initializedStartGoal = false;
m_foundGoal = false;
}

AStarAlgorithm::~AStarAlgorithm(void)
{}

void AStarAlgorithm::FindPath(Point currentPos, Point targetPos)
{
	if (!m_initializedStartGoal)
	{
		for(unsigned int i=0; i<m_openList.size(); i++)
		{
			delete m_openList[i];
		}
		m_openList.clear();

		for(unsigned int i=0; i<m_visitedList.size(); i++)
		{
			delete m_visitedList[i];
		}
		m_visitedList.clear();

		for(unsigned int i=0; i<m_pathToGoal.size(); i++)
		{
			delete m_pathToGoal[i];
		}
		m_pathToGoal.clear();

		// Initialize start
		Node start;
		start.m_xcoord = currentPos.GetX();
		start.m_zcoord = currentPos.GetY();

		// Initialize Goal
		Node goal;
		goal.m_xcoord = targetPos.GetX();
		goal.m_zcoord = targetPos.GetY();

		SetStartAndGoal(start,goal);
		m_initializedStartGoal  = true;
	}

	if (m_initializedStartGoal)
	{
		while (!m_foundGoal)
			ContinuePath();
	}
}

void AStarAlgorithm::SetStartAndGoal(Node start, Node goal)
{
	m_startCell = new Node(start.m_xcoord, start.m_zcoord,NULL);
	m_goalCell = new Node(goal.m_xcoord, goal.m_zcoord, &goal);

	m_startCell->G = 0;
	m_startCell->H = m_startCell->ManHattanDistance(m_goalCell);
	m_startCell->parent=0;

	m_openList.push_back(m_startCell);
}

Node* AStarAlgorithm::GetNextCell()
{
	float bestF = 999999.0f;
	int cellIndex = -1;
	Node* nextCell = NULL;

	for(unsigned int i=0;i<m_openList.size(); i++)
	{
		if (m_openList[i]->GetF() < bestF)
		{
			bestF = m_openList[i]->GetF();
			cellIndex = i;
		}
	}

	if(cellIndex >= 0)
	{
		nextCell = m_openList[cellIndex];
		m_visitedList.push_back(nextCell);
		m_openList.erase(m_openList.begin() + cellIndex);
	}

	return nextCell;
}

void AStarAlgorithm::pathOpened(int x, int z, float newCost, Node *parent)
{
	/*if (CELL_BLOCKED)
	{ // אם זה קיר
		return;
	}

	int id = z * 64 + x;
	for(unsigned int i; i< m_visitedList.size(); i++)
	{
		if (id == m_visitedList[i]->m_id)
		{
			return;
		}
	}

	Node* newChild = new Node(x,z,parent);
	newChild->G = newCost;
	newChild->H = parent->ManHattanDistance(m_goalCell);

	for(unsigned int i =0; i< m_openList.size(); i++)
	{
		if (id == m_openList[i]->m_id)
		{
			float newF = newChild->G + newCost+ m_openList[i]->H;

			if (m_openList[i]->GetF() > newF)
			{
				m_openList[i]->G = newChild->G + newCost;
				m_openList[i]->parent = newChild;
			}
			else
			{
				delete newChild;
				return;
			}
		}
	}

	m_openList.push_back(newChild);
}

void AStarAlgorithm::ContinuePath()
{
	if (m_openList.empty())
	{
		return;
	}

	Node* currentCell = GetNextCell();
	if (currentCell->m_id == m_goalCell->m_id)
	{
		m_goalCell->parent = currentCell->parent;
		Node* getPath;

		for(getPath = m_goalCell; getPath != NULL; getPath = getPath->parent)
		{
			m_pathToGoal.push_back(new Point(getPath->m_xcoord, getPath->m_zcoord));
		}

		m_foundGoal = true;
		return;
	}
	else
	{
		// rightCell
		pathOpened(currentCell->m_xcoord + 1, currentCell->m_zcoord,currentCell->G + 1, currentCell);
		// LeftSide
		pathOpened(currentCell->m_xcoord - 1, currentCell->m_zcoord,currentCell->G + 1, currentCell);
		// UpCell
		pathOpened(currentCell->m_xcoord, currentCell->m_zcoord + 1,currentCell->G + 1, currentCell);
		// downCell
		pathOpened(currentCell->m_xcoord, currentCell->m_zcoord - 1,currentCell->G + 1, currentCell);
		// leftUp
		pathOpened(currentCell->m_xcoord -1, currentCell->m_zcoord + 1,currentCell->G + 1.414f, currentCell);
		// rightUp
		pathOpened(currentCell->m_xcoord +1, currentCell->m_zcoord + 1,currentCell->G + 1.414f, currentCell);
		// leftDown
		pathOpened(currentCell->m_xcoord -1, currentCell->m_zcoord - 1,currentCell->G + 1.414f, currentCell);
		// rightDown
		pathOpened(currentCell->m_xcoord +1, currentCell->m_zcoord = 1,currentCell->G + 1.414f, currentCell);

		for(unsigned int i=0; i< m_openList.size(); i++)
		{
			if (currentCell->m_id == m_openList[i]->m_id)
			{
				m_openList.erase(m_openList.begin() + 1);
			}
		}
	}

}

Point AStarAlgorithm::NextPathPos(Point currentPoint)
{
	int index = 1;
	Point nextPos;
	nextPos.SetX(m_pathToGoal[m_pathToGoal.size() - index]->GetX());
	nextPos.SetY(m_pathToGoal[m_pathToGoal.size() - index]->GetY());

	//current position = pos
	Point distance(nextPos.GetX() - currentPoint.GetX(),nextPos.GetY() - currentPoint.GetY());

	if (index < m_pathToGoal.size())
	{
		if (distance.Length() < radius)
		{
			m_pathToGoal.erase(m_pathToGoal.end() - index);
		}
	}

	return nextPos;
}*/
