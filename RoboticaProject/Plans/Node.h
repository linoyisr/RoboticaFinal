/*
 * Node.h
 *
 *  Created on: Jun 26, 2015
 *      Author: colman
 */

#ifndef NODE_H_
#define NODE_H_

#include <math.h>
#include "../Point.h"
#define WORLD_SIZE 64

class Node {
public:
	Point *m_coords;
	int m_id;
	Node *parent;
	float G;
	float H;

	Node() : parent(0)
	{ }

	Node(int x, int y, Node *_parent = 0)
	{
		m_coords = new Point(x,y);
		parent = _parent;
		m_id = y * WORLD_SIZE + x;
		G = 0;
		H = 0;
	}

	float GetF()
	{
		return G + H;
	}

	float ManHattanDistance(Node *nodeEnd)
	{
		float x = (float)(fabs((float)(m_coords->GetX() - nodeEnd->m_coords->GetX())));
		float y = (float)(fabs((float)(m_coords->GetY() - nodeEnd->m_coords->GetY())));

		return x + y;
	}
};

#endif /* NODE_H_ */
