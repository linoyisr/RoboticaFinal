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

#define RESOLUTION 5 //Each cell in real world, Accepted 5
#define BEAMS_PER_CHECK 6
#define LASERS_NUMBER 666
#define SAFE_MAX_DISTANCE 3.5
#define MAPPING_START_POINT 5
#define MAPPING_END_POINT (SAFE_MAX_DISTANCE*100)/RESOLUTION

class Map {
private:

	int numOfCellsForeachPixel = 4;

	string blowMapPath = "resources/blowMap.png";
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
	unsigned char getColorOfCell(std::vector<unsigned char> grid,unsigned width, unsigned height, int row, int col, int res);

public:
	unsigned int mapHeight; // will initialize to 380
	unsigned int mapWidth; // will initialize to 550
	unsigned int gridHeight;
	unsigned int gridWidth;

	Map();
	virtual ~Map();
	std::vector<unsigned char> pngVector;
	std::vector<unsigned char> mapVector;
	std::vector<unsigned char> blowImage;

	std::vector<unsigned char> grid;

	void SetFreeCell(Point ponit);
	void SetOccupiedCell(Point point);
	Point* ConvertPositionToPoint(Point position);
	double UpdateMap(double deltaX, double deltaY, double deltaYaw, float* laserArray);
	void PrintMatrix();
	int GetCellValue(Point point);

	std::vector<std::vector<int> > getMatrix();
};

#endif /* MAP_H_ */
