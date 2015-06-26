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
			delete m_pathToGoal[i];
		}
		m_pathToGoal.clear();

		// Initialize start
		Node start;
		start.m_coords->SetX(currentPos.GetX());
		start.m_coords->SetY(currentPos.GetY());

		// Initialize Goal
		Node goal;
		goal.m_coords->SetX(targetPos.GetX());
		goal.m_coords->SetY(targetPos.GetY());

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
	m_startCell = new Node(start.m_coords->GetX(), start.m_coords->GetY(), NULL);
	m_goalCell = new Node(goal.m_coords->GetX(), goal.m_coords->GetY(), &goal);

	m_startCell->G = 0;
	m_startCell->H = m_startCell->ManHattanDistance(m_goalCell);
	m_startCell->parent = 0;

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
		if (id == m_visitedList[i]->m_id)
		{
			return;
		}
	}

	Node* newChild = new Node(x, z, parent);
	newChild->G = newCost;
	newChild->H = newChild->ManHattanDistance(m_goalCell);

	for (unsigned int i = 0; i< m_openList.size(); i++)
	{
		if (id == m_openList[i]->m_id)
		{
			float newF = newChild->G + newCost + m_openList[i]->H;

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

void PathPlanner::ContinuePath()
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

		for (getPath = m_goalCell; getPath != NULL; getPath = getPath->parent)
		{
			m_pathToGoal.push_back(new Point(getPath->m_coords->GetX(), getPath->m_coords->GetY()));
		}
		reverse(m_pathToGoal.begin(), m_pathToGoal.end());

		m_foundGoal = true;
		return;
	}
	else
	{
		// rightCell
		pathOpened(currentCell->m_coords->GetX() + 1, currentCell->m_coords->GetY(), currentCell->G + 1, currentCell);
		// LeftSide
		pathOpened(currentCell->m_coords->GetX() - 1, currentCell->m_coords->GetY(), currentCell->G + 1, currentCell);
		// UpCell
		pathOpened(currentCell->m_coords->GetX(), currentCell->m_coords->GetY() + 1, currentCell->G + 1, currentCell);
		// downCell
		pathOpened(currentCell->m_coords->GetX(), currentCell->m_coords->GetY() - 1, currentCell->G + 1, currentCell);
		// leftUp
		pathOpened(currentCell->m_coords->GetX() - 1, currentCell->m_coords->GetY() + 1, currentCell->G + 1.414f, currentCell);
		// rightUp
		pathOpened(currentCell->m_coords->GetX() + 1, currentCell->m_coords->GetY() + 1, currentCell->G + 1.414f, currentCell);
		// leftDown
		pathOpened(currentCell->m_coords->GetX() - 1, currentCell->m_coords->GetY() - 1, currentCell->G + 1.414f, currentCell);
		// rightDown
		pathOpened(currentCell->m_coords->GetX() + 1, currentCell->m_coords->GetY() - 1, currentCell->G + 1.414f, currentCell);

		for (unsigned int i = 0; i< m_openList.size(); i++)
		{
			if (currentCell->m_id == m_openList[i]->m_id)
			{
				m_openList.erase(m_openList.begin() + 1);
			}
		}
	}

}
