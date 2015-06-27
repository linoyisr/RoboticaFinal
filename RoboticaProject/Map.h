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

public:
	unsigned int mapHeight; // will initialize to 380
	unsigned int mapWidth; // will initialize to 550
	unsigned int gridHeight;
	unsigned int gridWidth;

	Map();
	virtual ~Map();
	vector<unsigned char> pngVector;
	vector<unsigned char> blowMapVector;
	vector<unsigned char> gridVector;

	void PrintGridMatrix();
	std::vector<std::vector<int> > getGridMatrix();
	void PrintBlowGridMatrix();
	std::vector<std::vector<int> > getBlowGridMatrix();
	Point getRealLocationBy(Point gridPoint);
	Point getImageLocationBy(Point gridPoint);
	Point getGridLocationBy(Point imagePoint);
	int getGridValueAt(Point gridPoint);

};

#endif /* MAP_H_ */
