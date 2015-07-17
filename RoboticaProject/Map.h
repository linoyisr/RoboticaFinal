/*
 * Map.h
 *
 *      Author: user
 */

#ifndef MAP_H_
#define MAP_H_

#include "Point.h"
#include <iostream>
#include <vector>

using namespace std;

class Map {
private:
	string mapPath;
	int mapResolution;
	int gridResolution;
	unsigned int robotWidth;
	unsigned int robotHeight;

	void getConfigValues();
	void pngToVector();
	void blowMap();
	void saveBlowingMap();
	int getValueByResolution(float range);
	void BlowingMapToGrid();
	unsigned char getColorOfCell(vector<unsigned char> grid,unsigned width, unsigned height, int row, int col, int res);
	void setBlowMapMatrix();
	void setGridMatrix();

public:
	unsigned int mapHeight; // will initialize to 380
	unsigned int mapWidth; // will initialize to 550
	unsigned int gridHeight;
	unsigned int gridWidth;
	int blowMapHeight;
	int blowMapWidth;

	Map();
	virtual ~Map();
	vector<unsigned char> pngVector;
	vector<unsigned char> blowMapVector;
	vector<unsigned char> gridVector;
	std::vector<std::vector<int> > mapMatrix;
	std::vector<std::vector<int> > blowMapMatrix;

	void PrintGridMatrix();
	std::vector<std::vector<int> > getMapMatrix();
	std::vector<std::vector<int> > getBlowMapMatrix();
	void PrintBlowMapMatrix();
	Point getRealPointBy(Point gridPoint);
	Point getImagePointBy(Point gridPoint);
	Point getGridPointBy(Point imagePoint);
	int getGridValueAt(Point gridPoint);

};

#endif /* MAP_H_ */
