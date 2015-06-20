/*
 * Map.h
 *
 *  Created on: May 16, 2014
 *      Author: user
 */

#ifndef MAP_H_
#define MAP_H_

#include "Point.h"
#include <iostream>
#define OCCUPIED 1
#define FREE    0
#define HEIGHT 100
#define WIDTH 100
#define RESOLUTION 5
#define UNKNOWN  2
#define BEAMS_PER_CHECK 6
#define LASERS_NUMBER 666
#define SAFE_MAX_DISTANCE 3.5
#define MAPPING_START_POINT 5
#define MAPPING_END_POINT (SAFE_MAX_DISTANCE*100)/RESOLUTION

class Map {
public:
	Map();
	virtual ~Map();
    int matrix[HEIGHT][WIDTH];
	void SetClearCell(Point ponit);
	void SetOccupiedCell(Point point);
	Point* ConvertPositionToPoint(Point position);
	Point* RealObstacleLocation(Point p, double yaw, double angle, double dist);
	double UpdateMap(double deltaX, double deltaY, double deltaYaw, float* laserArray);
	void Print();
	int GetCellValue(Point ponit);
	int getValueByResolution(float range);
    int getHeight()
    {
    	return HEIGHT;
    }
    int getWidth()
    {
    	return WIDTH;
    }

};

#endif /* MAP_H_ */
