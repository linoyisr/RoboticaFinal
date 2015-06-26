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

typedef enum
{
	First,
	Goal,
	Obstacle,
	None
}NodeType;

class Node {
public:
	Node() : parent(0) {}

	Node(int x, int y, Node *_parent = 0)
	{
		m_coords = new Point(x,y);
		parent = _parent;
		m_id = y * WORLD_SIZE + x;
		G = 0;
		H = 0;
	}

	float GetF();
	float ManHattanDistance(Node *nodeEnd);

	Point* GetPoint();
	Node* GetParent();
	int GetNodeID();
	int GetH();
	int GetG();

	void setPoint(Point* p);
	void setParent(Node* p);
	void setNodeID(int id);
	void setH(int h);
	void setG(int g);

private:
	Point *m_coords;
	int m_id;
	Node *parent;
	float G;
	float H;
	NodeType type;
};

#endif /* NODE_H_ */
