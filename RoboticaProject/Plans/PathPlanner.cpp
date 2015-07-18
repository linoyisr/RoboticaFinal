/*
 * PathPlanner.cpp
 *
 *  Created on: Jun 26, 2015
 *      Author: colman
 */

#include "PathPlanner.h"


PathPlanner::PathPlanner(void)
{
	m_initializedStartGoal = false;
	m_foundGoal = false;
}

PathPlanner::~PathPlanner(void)
{}

void PathPlanner::ClearOpenList()
{
	m_openList.clear();
}

void PathPlanner::ClearVisitedList()
{
	m_visitedList.clear();
}

void PathPlanner::ClearPathToGoal()
{
	m_pathToGoal.clear();
}

vector<Point> PathPlanner::GetPathToGoal()
{
	return m_pathToGoal;
}

void PathPlanner::FindPath(vector<vector<int> > pngGrid, Point currentPos, Point targetPos)
{
	if (!m_initializedStartGoal)
	{
		for (unsigned int i = 0; i<m_openList.size(); i++)
		{
			delete m_openList[i];
		}
		m_openList.clear();

		for (unsigned int i = 0; i<m_visitedList.size(); i++)
		{
			delete m_visitedList[i];
		}
		m_visitedList.clear();

		for (unsigned int i = 0; i<m_pathToGoal.size(); i++)
		{
			delete &m_pathToGoal[i];
		}
		m_pathToGoal.clear();

		// Initialize start
		Node start;
		start.setPoint(&currentPos);

		// Initialize Goal
		Node goal;
		goal.setPoint(&targetPos);

		SetStartAndGoal(start, goal);
		m_pngGrid = pngGrid;
		m_initializedStartGoal = true;
	}

	if (m_initializedStartGoal)
	{
		while (!m_foundGoal)
			ContinuePath();
	}
}

void PathPlanner::SetStartAndGoal(Node start, Node goal)
{

	m_startCell = new Node(start.GetPoint()->GetX(), start.GetPoint()->GetY(), NULL);
	m_goalCell = new Node(goal.GetPoint()->GetX(), goal.GetPoint()->GetY(), &goal);

	m_startCell->setG(0);
	m_startCell->setH(m_startCell->ManHattanDistance(m_goalCell));
	m_startCell->setParent(0);

	m_openList.push_back(m_startCell);
}

Node* PathPlanner::GetNextCell()
{
	float bestF = 999999.0f;
	int cellIndex = -1;
	Node* nextCell = NULL;

	for (unsigned int i = 0; i<m_openList.size(); i++)
	{
		if (m_openList[i]->GetF() < bestF)
		{
			bestF = m_openList[i]->GetF();
			cellIndex = i;
		}
	}

	if (cellIndex >= 0)
	{
		nextCell = m_openList[cellIndex];
		m_visitedList.push_back(nextCell);
		m_openList.erase(m_openList.begin() + cellIndex);
	}

	return nextCell;
}

void PathPlanner::pathOpened(int x, int z, float newCost, Node *parent)
{
	if (m_pngGrid[x][z] == 1)
	{ // אם זה קיר
		return;
	}

	int id = z * WORLD_SIZE + x;
	for (unsigned int i = 0; i< m_visitedList.size(); i++)
	{
		if (id == m_visitedList[i]->GetNodeID())
		{
			return;
		}
	}

	Node* newChild = new Node(x, z, parent);
	newChild->setG(newCost);
	newChild->setH(newChild->ManHattanDistance(m_goalCell));

	for (unsigned int i = 0; i< m_openList.size(); i++)
	{
		if (id == m_openList[i]->GetNodeID())
		{
			float newF = newChild->GetG() + newCost + m_openList[i]->GetH();

			if (m_openList[i]->GetF() > newF)
			{
				m_openList[i]->setG(newChild->GetG() + newCost);
				m_openList[i]->setParent(newChild);
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

void PathPlanner::ContinuePath()
{
	if (m_openList.empty())
	{
		return;
	}

	Node* currentCell = GetNextCell();
	if (currentCell->GetNodeID() == m_goalCell->GetNodeID())
	{
		m_goalCell->setParent(currentCell->GetParent());
		Node* getPath;

		for (getPath = m_goalCell; getPath != NULL; getPath = getPath->GetParent())
		{
			Point p(getPath->GetPoint()->GetX(), getPath->GetPoint()->GetY());
			m_pathToGoal.push_back(p);
		}
		reverse(m_pathToGoal.begin(), m_pathToGoal.end());

		for (unsigned int i = 0; i< m_pathToGoal.size(); i++)
		{
			m_pathToGoal[i].PrintPoint();
		}

		m_foundGoal = true;
		return;
	}
	else
	{
		// rightCell
		pathOpened(currentCell->GetPoint()->GetX() + 1, currentCell->GetPoint()->GetY(), currentCell->GetG() + 1, currentCell);
		// LeftSide
		pathOpened(currentCell->GetPoint()->GetX() - 1, currentCell->GetPoint()->GetY(), currentCell->GetG() + 1, currentCell);
		// UpCell
		pathOpened(currentCell->GetPoint()->GetX(), currentCell->GetPoint()->GetY() + 1, currentCell->GetG() + 1, currentCell);
		// downCell
		pathOpened(currentCell->GetPoint()->GetX(), currentCell->GetPoint()->GetY() - 1, currentCell->GetG() + 1, currentCell);
		// leftUp
		pathOpened(currentCell->GetPoint()->GetX() - 1, currentCell->GetPoint()->GetY() + 1, currentCell->GetG() + 1.414f, currentCell);
		// rightUp
		pathOpened(currentCell->GetPoint()->GetX() + 1, currentCell->GetPoint()->GetY() + 1, currentCell->GetG() + 1.414f, currentCell);
		// leftDown
		pathOpened(currentCell->GetPoint()->GetX() - 1, currentCell->GetPoint()->GetY() - 1, currentCell->GetG() + 1.414f, currentCell);
		// rightDown
		pathOpened(currentCell->GetPoint()->GetX() + 1, currentCell->GetPoint()->GetY() - 1, currentCell->GetG() + 1.414f, currentCell);

		for (unsigned int i = 0; i< m_openList.size(); i++)
		{
			if (currentCell->GetNodeID() == m_openList[i]->GetNodeID())
			{
				m_openList.erase(m_openList.begin() + 1);
			}
		}
	}

}
