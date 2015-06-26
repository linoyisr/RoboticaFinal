/*
 * Map.cpp
 */

#include "Map.h"
#include "LaserHelper.h"
#include "Manager/ConfigurationManager.h"
#include "math.h"
#include "pngUtil.h"
#include "lodepng.h"
#include <stdio.h>
#include <stdlib.h>
#include <ostream>
#include <string>
#include "Location.h"
typedef basic_stringstream<char> stringstream;

Map::Map()
{
	getConfigValues();
	pngToVector();
	blowMap();
	BlowingMapToGrid();
	getMatrix();

	//this code checking converting between image point to grid point
	//the points i test are black
	/*
	Point a = getImageLocationBy(Point(91,4));
	Point b = getGridLocationBy(a);
	if (pngVector[a.GetY() * mapWidth * 4 + a.GetX() *4] ==
			gridVector[b.GetY() * gridWidth * 4 + b.GetX() *4])
		cout << true <<endl;

	a = getImageLocationBy(Point(78,10));
	b = getGridLocationBy(a);
	if (pngVector[a.GetY() * mapWidth * 4 + a.GetX() *4] ==
			gridVector[b.GetY() * gridWidth * 4 + b.GetX() *4])
		cout << true <<endl;

	a = getImageLocationBy(Point(69,12));
	b = getGridLocationBy(a);
	if (pngVector[a.GetY() * mapWidth * 4 + a.GetX() *4] ==
			gridVector[b.GetY() * gridWidth * 4 + b.GetX() *4])
		cout << true <<endl;*/

}

void Map::getConfigValues()
{
	ConfigurationManager cfg("parameters.txt");

	mapPath = cfg.getValueOfKey("map");
	string robotSizeString = cfg.getValueOfKey("robotSize");
	// convert string with spaces to array
	vector<int> robotSizeArray;
	stringstream ss3(robotSizeString);
	int temp3;
	while (ss3 >> temp3)
		robotSizeArray.push_back(temp3);

	robotHeight = robotSizeArray[0];
	robotWidth = robotSizeArray[1];

	mapResolution = atof(cfg.getValueOfKey("MapResolutionCM").c_str());
	gridResolution = atof(cfg.getValueOfKey("GridResolutionCM").c_str());
	/*
		string startLocationString;
		int xStart;
		int yStart;
		int yawStart;
		string goalString;
		int xGoal;
		int yGoal;

		startLocationString = cfg.getValueOfKey("startLocation");
		// convert string with spaces to array
		vector<int> startLocationArray;
		stringstream ss1(startLocationString);
		int temp1;
		while (ss1 >> temp1)
			startLocationArray.push_back(temp1);

		xStart = startLocationArray[0];
		yStart = startLocationArray[1];
		Point startPoint(xStart, yStart);
		yawStart = startLocationArray[2];
		Location loc(&startPoint, yawStart);

		goalString = cfg.getValueOfKey("goal");
		// convert string with spaces to array
		vector<int> goalArray;
		stringstream ss2(goalString);
		int temp2;
		while (ss2 >> temp2)
			goalArray.push_back(temp2);

		xGoal = goalArray[0];
		yGoal = goalArray[1];*/
}
void Map::pngToVector()
{
	// Convert png to vector
	int error = lodepng::decode(pngVector,mapWidth,mapHeight, mapPath);

	//if there's an error, display it
	if (error)
	{
		cout << "decoder error #" << error << ": " << lodepng_error_text(error) << endl;
		return;
	}
}

void Map::blowMap()
{
	//Change size of the vector because each pixel represented by 4 cells (3 for RGB + last one always 255)
	blowMapVector.resize(mapWidth * mapHeight * numOfCellsForeachPixel);

	// the really point of the robot is at the center
	int xPixelsToBlowing = int(robotWidth / mapResolution) / 2;
	int yPixelsToBlowing = int(robotHeight / mapResolution) / 2;

	for (int y = 0; y < mapHeight; y++)
	{
		for (int x = 0; x < mapWidth; x++)
		{
			int currPixel = (y * mapWidth * numOfCellsForeachPixel) + (x * numOfCellsForeachPixel);

			if (pngVector[currPixel] == BLACK)
			{
				// Move the left and right cells to blowing
				for (int i = -xPixelsToBlowing; i < xPixelsToBlowing; i++)
				{
				// Move the up and down cells to blowing
					for (int j = -yPixelsToBlowing; j < yPixelsToBlowing; j++)
					{
						int offset = ((j * numOfCellsForeachPixel) + ((mapWidth) * i * numOfCellsForeachPixel));
						//Make sure there is no scope creep from map
						if (currPixel + offset >= 0 && currPixel + offset + BOFFSET < blowMapVector.size())
						{
							blowMapVector[currPixel + offset + ROFFSET] = BLACK;
							blowMapVector[currPixel + offset + GOFFSET] = BLACK;
							blowMapVector[currPixel + offset + BOFFSET] = BLACK;
						}
					}
				}
			}
			else
			{
				blowMapVector[currPixel + ROFFSET] = WHITE;
				blowMapVector[currPixel + GOFFSET] = WHITE;
				blowMapVector[currPixel + BOFFSET] = WHITE;
			}

			// last pixel is always white
			blowMapVector[currPixel + AOFFSET] = WHITE;
		}
	}

	saveBlowingMap();
}

void Map::saveBlowingMap()
{
	int encodeError = lodepng::encode(blowMapPath, blowMapVector, mapWidth, mapHeight);

	if (encodeError)
	{
		cout << "encoder error " << encodeError << ": "
				<< lodepng_error_text(encodeError) << endl;
	}
}

// Return map to be original size after blowing
void Map::BlowingMapToGrid()
{
	unsigned char color;

	//Check why mapResolution change to 2
	int newGridResoultion = (int)(floor(gridResolution/mapResolution));

	gridHeight = (unsigned int)(mapHeight/newGridResoultion);
	gridWidth = (unsigned int)(mapWidth/newGridResoultion);

	gridVector.resize(gridHeight * gridWidth * numOfCellsForeachPixel);

	for (unsigned y = 0; y < gridHeight; y++)
	{
		for (unsigned x = 0; x < gridWidth; x++)
		{
			int currPixel = (y * gridWidth * numOfCellsForeachPixel) + (x * numOfCellsForeachPixel);

			color = getColorOfCell(blowMapVector, mapWidth, mapHeight, y, x, newGridResoultion);

			gridVector[currPixel + ROFFSET] = color;
			gridVector[currPixel + GOFFSET] = color;
			gridVector[currPixel + BOFFSET] = color;
			gridVector[currPixel + AOFFSET] = WHITE;
		}
	}
}

vector<vector<int> > Map::getMatrix()
{
	vector<vector<int> > matrix(gridHeight, vector<int>(gridWidth));
	unsigned char color;

	for (unsigned int y = 0; y < gridHeight; y++)
	{
		for (unsigned int x = 0; x < gridWidth; x++)
		{
			color = getColorOfCell(gridVector, gridWidth, gridHeight, y, x, 1);
			switch (color)
			{
				case WHITE:
					matrix[y][x] = FREE;
					break;
				case BLACK:
					matrix[y][x] = OCCUPIED;
					break;
				default:
					matrix[y][x] = UNKNOWN;
			}
		}
	}

	//only for checking
	//int encodeError = lodepng::encode("resources/gridVector.png", gridVector, gridWidth, gridHeight);

	return matrix;
}

unsigned char Map::getColorOfCell(vector<unsigned char> grid,unsigned width, unsigned height, int row, int column, int resolution)
{
	for (int y = 0; y < resolution; y++)
	{
		for (int x = 0; x < resolution; x++)
		{
			unsigned char color = pngUtil::getColorOfPixel(grid, width, height, ((row*resolution) + y), ((column*resolution)+ x));

			// If there at least 1 cell black in blowMap, the representing cell in the gridVector will be black
			if(color == BLACK)
			{
				return color;
			}
		}
	}

	return WHITE;
}

void Map::PrintMatrix()
{
	vector<vector<int> > matrix = getMatrix();

	for (unsigned int y = 0; y < gridHeight; y++)
		{
			for (unsigned int x = 0; x < gridWidth; x++)
			{
				cout << matrix[y][x];
			}
			cout << endl;
		}
}

Point Map::getRealLocationBy(Point gridPoint)
{
	//Each cell in grid , pi 10 in the real world
	return Point(gridPoint.GetX() * gridResolution, gridPoint.GetY() * gridResolution);
}

Point Map::getImageLocationBy(Point gridPoint)
{
	return Point(gridPoint.GetX() * (mapWidth/gridWidth), gridPoint.GetY() * (mapHeight/gridHeight) );
}

Point Map::getGridLocationBy(Point imagePoint)
{
	return Point(imagePoint.GetX() / (mapWidth/gridWidth), imagePoint.GetY() / (mapHeight/gridHeight) );
}

void Map::SetFreeCell(Point pnt)
{
	gridVector[pnt.GetX() * mapWidth + pnt.GetY()] = FREE;
}

void Map::SetOccupiedCell(Point pnt)
{
	gridVector[pnt.GetX() * mapWidth + pnt.GetY()] = OCCUPIED;
}

Point* Map::ConvertPositionToPoint(Point position)
{
	return NULL;
}

int Map::GetCellValue(Point point)
{
	return gridVector[point.GetX() * mapWidth + point.GetY()];
}

double Map::UpdateMap(double x, double y, double yaw, float* laserArray)
{
	double angleForLaser;
	float xForLaser;
	float yForLaser;
	int missCounter = 0;
	int hitCounter = 0;

	for (int beamIndex = 0; beamIndex < LASERS_NUMBER; beamIndex+=BEAMS_PER_CHECK)
	{
		if (laserArray[beamIndex] > SAFE_MAX_DISTANCE)
		{
			for (int curr_distance = MAPPING_START_POINT; curr_distance <= MAPPING_END_POINT; curr_distance+= RESOLUTION)
			{
				angleForLaser = LaserHelper::indexToRad(beamIndex) + yaw;
				yForLaser = y + (curr_distance * sin(angleForLaser));
				xForLaser = x + (curr_distance * cos(angleForLaser));

				Point* pnt = new Point(xForLaser, yForLaser);
				pnt = ConvertPositionToPoint(*pnt);

				pnt->PrintPoint();
				cout << "when clear" << endl;

				if (GetCellValue(*pnt) == FREE)
				{
					hitCounter++;
				}
				else if (GetCellValue(*pnt) == OCCUPIED)
				{
					missCounter++;
					SetFreeCell(*pnt);
				}
				else if (GetCellValue(*pnt) == UNKNOWN)
				{
					hitCounter++;
					SetFreeCell(*pnt);
				}
			}

		}
		else
		{
			cout << "**** " << beamIndex << "*********" << laserArray[beamIndex] << endl;
			// TODO: <========== minusssssssssssssssssssssssss
			int distance = getValueByResolution(laserArray[beamIndex]);

			if (distance < 5)
			{
				distance = 5;
			}

			angleForLaser = LaserHelper::indexToRad(beamIndex) + yaw;
			yForLaser = y + (distance * sin(angleForLaser));
			xForLaser = x + (distance * cos(angleForLaser));

			Point* pnt = new Point(xForLaser, yForLaser);
			pnt = ConvertPositionToPoint(*pnt);

			pnt->PrintPoint();
			cout << "when occupied" << endl;

			if (GetCellValue(*pnt) == FREE)
			{
				cout << "clear" << endl;
				missCounter++;
				SetOccupiedCell(*pnt);
			}
			else if (GetCellValue(*pnt) == OCCUPIED)
			{
				cout << "occupied" << endl;
				hitCounter++;
			}
			else if (GetCellValue(*pnt) == UNKNOWN)
			{
				cout << "unknown" << endl;
				hitCounter++;
				SetOccupiedCell(*pnt);
			}

			cout << "check if got into the for " << endl;
			for (int curr_distance = distance-5; curr_distance >= MAPPING_START_POINT; curr_distance-= RESOLUTION )
			{

				angleForLaser = LaserHelper::indexToRad(beamIndex) + yaw;
				yForLaser = y + (curr_distance * sin(angleForLaser));
				xForLaser = x + (curr_distance * cos(angleForLaser));

				Point* pnt = new Point(xForLaser, yForLaser);
				pnt = ConvertPositionToPoint(*pnt);

				pnt->PrintPoint();
				cout << "when clear2" << endl;

				if (GetCellValue(*pnt) == FREE)
				{
					hitCounter++;
				}
				else if (GetCellValue(*pnt) == OCCUPIED)
				{
					missCounter++;
					SetFreeCell(*pnt);

				}
				else if (GetCellValue(*pnt) == UNKNOWN)
				{
					hitCounter++;
					SetFreeCell(*pnt);
				}
			}
		}
	}
	//TODO:change!!!
	cout << "plzzzzzzzzzzzz" << endl;
	this->PrintMatrix();
	return (float)(hitCounter/(hitCounter + missCounter));
}

int Map::getValueByResolution(float range)
{
	return (int)(floor((range * 100)/5));
}

Map::~Map()
{
}

