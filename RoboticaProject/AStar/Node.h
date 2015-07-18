/*
 * Node.h
 *
 *  Created on: Jun 20, 2015
 *      Author: colman
 */
/*
#ifndef NODE_H_
#define NODE_H_

#include <math.h>
//#define WORLD_SIZE 4

class Node {
	public:
	int m_xcoord, m_zcoord;
	int m_id;
	Node *parent;
	float G;
	float H;

	Node(): parent(0)
	{ }

	Node(int x, int z, Node *_parent = 0)
	{
		m_xcoord = x;
		m_zcoord = z;
		parent = _parent;
		m_id = z * 64 + x;
		G = 0;
		H = 0;
	}

	float GetF()
	{
	return G+H;
	}

	float ManHattanDistance(Node *nodeEnd)
	{
		float x = (float)(fabs((float)(m_xcoord - nodeEnd->m_xcoord)));
		float z = (float)(fabs((float)(m_zcoord - nodeEnd->m_zcoord)));

		return x+z;
	}
};

#endif /* NODE_H_ */
