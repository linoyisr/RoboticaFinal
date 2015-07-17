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

const int numOfCellsForeachPixel = 4;
const string blowMapPath = "resources/blowMap.png";

Map::Map()
{
	getConfigValues();
	pngToVector();
	blowMap();
	BlowingMapToGrid();
	setGridMatrix();
	setBlowMapMatrix();
	PrintGridMatrix();
	PrintBlowMapMatrix();
/*
	//this code checking converting between image point to grid point
	//the points i test are black

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
	vector<int> robotSizeArray = cfg.ConvertStringToIntArray(robotSizeString);
	robotHeight = robotSizeArray[0];
	robotWidth = robotSizeArray[1];

	mapResolution = atof(cfg.getValueOfKey("MapResolutionCM").c_str());
	gridResolution = atof(cfg.getValueOfKey("GridResolutionCM").c_str());
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

	for (unsigned int y = 0; y < mapHeight; y++)
	{
		for (unsigned int x = 0; x < mapWidth; x++)
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
						unsigned int offset = ((j * numOfCellsForeachPixel) + ((mapWidth) * i * numOfCellsForeachPixel));
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
			blowMapVector[currPixel + LOFFSET] = WHITE;
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

	//TODO:Check why mapResolution change to 2
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
			gridVector[currPixel + LOFFSET] = WHITE;
		}
	}

	//only for checking
	//lodepng::encode("resources/gridVector.png", gridVector, gridWidth, gridHeight);
	//odepng::encode("resources/a.png", blowMapVector, mapWidth, mapHeight);
}

void Map::setBlowMapMatrix()
{
	std::vector<unsigned char> blowMap;
	unsigned width, height;
	lodepng::decode(blowMap, width, height, blowMapPath);

	int relativelyResolution = gridResolution / mapResolution;
	blowMapHeight = height * mapResolution / gridResolution;
	blowMapWidth = width * mapResolution / gridResolution;
	bool isAtleastOneIsBlack = false;

	blowMapMatrix =  vector<vector<int> >(blowMapHeight, vector<int>(blowMapWidth));

	for (int y = 0; y < (blowMapHeight * relativelyResolution); y += relativelyResolution)
		for (int x = 0; x < (blowMapWidth * relativelyResolution); x += relativelyResolution)
		{
			isAtleastOneIsBlack = false;
			for (int i = y ; (i < y + relativelyResolution)&&(!isAtleastOneIsBlack); i++)
			{
				for (int j = x ; (j < x + relativelyResolution)&&(!isAtleastOneIsBlack); j++)
				{
					if (blowMap[i * width * numOfCellsForeachPixel + j * numOfCellsForeachPixel + ROFFSET] == BLACK
						|| blowMap[i * width * numOfCellsForeachPixel + j * numOfCellsForeachPixel + GOFFSET] == BLACK
						|| blowMap[i * width * numOfCellsForeachPixel + j * numOfCellsForeachPixel + BOFFSET] == BLACK)
					{
						isAtleastOneIsBlack = true;
						(blowMapMatrix[y / relativelyResolution][x / relativelyResolution]) = OCCUPIED;
					}
				}
			}
			if (isAtleastOneIsBlack == false)
			{
				(blowMapMatrix[y / relativelyResolution][x / relativelyResolution]) = FREE;
			}
		}
}


//Return blow map matrix that smaller than original size
vector<vector<int> > Map::getBlowMapMatrix()
{
		return blowMapMatrix;
}


void Map::setGridMatrix()
{
	mapMatrix = vector<vector<int> >(gridHeight, vector<int>(gridWidth));
	unsigned char color;

	for (unsigned int y = 0; y < gridHeight; y++)
	{
		for (unsigned int x = 0; x < gridWidth; x++)
		{
			color = getColorOfCell(gridVector, gridWidth, gridHeight, y, x, 1);
			switch (color)
			{
				case WHITE:
					mapMatrix[y][x] = FREE;
					break;
				case BLACK:
					mapMatrix[y][x] = OCCUPIED;
					break;
				default:
					mapMatrix[y][x] = UNKNOWN;
			}
		}
	}
}


vector<vector<int> > Map::getMapMatrix()
{
		return mapMatrix;
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

void Map::PrintGridMatrix()
{
	for (unsigned int y = 0; y < gridHeight; y++)
		{
			for (unsigned int x = 0; x < gridWidth; x++)
			{
				cout << mapMatrix[y][x];
			}
			cout << endl;
		}
}

void Map::PrintBlowMapMatrix()
{
	for ( int y = 0; y < blowMapHeight; y++)
	{
		for ( int x = 0; x < blowMapWidth; x++)
		{
			cout << blowMapMatrix[y][x];
		}
		cout << endl;
	}
}

Point Map::getRealPointBy(Point gridPoint)
{
	//Each cell in grid , pi 10 in the real world
	return Point(gridPoint.GetX() * gridResolution, gridPoint.GetY() * gridResolution);
}

Point Map::getImagePointBy(Point gridPoint)
{
	return Point(gridPoint.GetX() * (mapWidth/gridWidth), gridPoint.GetY() * (mapHeight/gridHeight) );
}

Point Map::getGridPointBy(Point imagePoint)
{
	return Point(imagePoint.GetX() / (mapWidth/gridWidth), imagePoint.GetY() / (mapHeight/gridHeight) );
}

Map::~Map()
{
}

int Map::getGridValueAt(Point gridPoint)
{
	return getMapMatrix()[gridPoint.GetY()][gridPoint.GetX()];
}
