/*
 * Node.cpp
 *
 *  Created on: Jun 26, 2015
 *      Author: colman
 */

#include "Node.h"

float Node::GetF()
{
	return G + H;
}

float Node::ManHattanDistance(Node *nodeEnd)
{
	float x = (float)(fabs((float)(m_coords->GetX() - nodeEnd->m_coords->GetX())));
	float y = (float)(fabs((float)(m_coords->GetY() - nodeEnd->m_coords->GetY())));

	return x + y;
}

Point* Node::GetPoint()
{
	return m_coords;
}

Node* Node::GetParent()
{
	return parent;
}

int Node::GetNodeID()
{
	return m_id;
}

void Node::setPoint(Point* p)
{
	m_coords = p;
}

void Node::setParent(Node* p)
{
	parent = p;
}

void Node::setNodeID(int id)
{
	m_id = id;
}

void Node::setH(int h)
{
	H=h;
}
void Node::setG(int g)
{
	G=g;
}

int Node::GetH()
{
	return H;
}

int Node::GetG()
{
	return G;
}
