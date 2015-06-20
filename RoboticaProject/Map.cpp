/*
 * Map.cpp
 */

#include "Map.h"
#include "LaserHelper.h"
#include "math.h"

Map::Map()
{
	for (int i = 0; i< HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			this->matrix[i][j] = UNKNOWN;
		}
	}
}

Map::~Map()
{
}

void Map::Print() {
	// TODO Auto-generated constructor stub
	for (int i = 0; i< HEIGHT; i++){
		for (int j = 0; j < WIDTH; j++){
			cout<<this->matrix[i][j];
		}
		cout<<endl;
	}
}

void Map::SetClearCell(Point pnt)
{
	this->matrix[pnt.GetX()][pnt.GetY()] = FREE;
}

void Map::SetOccupiedCell(Point pnt)
{
	this->matrix[pnt.GetX()][pnt.GetY()] = OCCUPIED;
}

Point* Map::ConvertPositionToPoint(Point position)
{
	return (new Point(position.GetX()/RESOLUTION + WIDTH/2,HEIGHT/2 + position.GetY()/RESOLUTION));
}

int Map::GetCellValue(Point pnt)
{
	int a = 0;
	int x = pnt.GetX();
	int y = pnt.GetY();

	try
	{
		a = matrix[x][y];
	}
	catch (exception e)
	{
		int b = 0;
		cout << "I dfkghwesukghwe" << b <<endl;
	}
	return a;
}

Point* Map::RealObstacleLocation(Point p, double yaw, double angle, double dist)
{
	return NULL;
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
					SetClearCell(*pnt);
				}
				else if (GetCellValue(*pnt) == UNKNOWN)
				{
					hitCounter++;
					SetClearCell(*pnt);
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
					SetClearCell(*pnt);

				}
				else if (GetCellValue(*pnt) == UNKNOWN)
				{
					hitCounter++;
					SetClearCell(*pnt);
				}
			}
		}
	}
	//TODO:change!!!
	cout << "plzzzzzzzzzzzz" << endl;
	this->Print();
	return (float)(hitCounter/(hitCounter + missCounter));
}

int Map::getValueByResolution(float range)
{
	return (int)(floor((range * 100)/5));
}

