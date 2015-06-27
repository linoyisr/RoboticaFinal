/*
 * Particle.cpp
 */

#include "Particle.h"
#include "LaserHelper.h"
#include "pngUtil.h"
#include "Map.h"
#include <math.h>
#include <cmath>
#include <stdlib.h>
using namespace std;


//#define UNLIKELY_DISTANCE 1
//#define TRUST_ISSUES 0.3
//#define UNLIKELY_ANGLE M_PI / 2

#define RADIUS 1
#define MAX_ANGLE 360
#define BEAMS_FOREACH_CHECK 6
#define LASERS_NUMBER 666
#define BEAM_MAX_DISTANCE 3.5
#define MAPPING_START_POINT 5
#define MAPPING_END_POINT (BEAM_MAX_DISTANCE*100)/2.5 //resolution

const int maxGoodDistance = 2; //if in the grid, else *10(grid resolution)
const int maxGoodAngle = 5; //if in degrees, else *M_PI/MAX_ANGLE
const double normalizationFactor = 1.3;
const double defaultBelief = 1;

Particle::Particle(double x, double y, double yaw, Map* map)
: Particle::Particle(x, y, yaw, map, defaultBelief)
{
}

Particle::Particle(double x, double y, double yaw, Map* map, double belief)
{
	this->x = x;
	this->y = y;
	this->yaw = yaw;
	this->map = map;
	this->belief = belief;
}

double Particle::getBelief()
{
	return belief;
}
Map* Particle::getMap()
{
	return map;
}

void Particle::Update(double deltaX, double deltaY, double deltaYaw, float* laserArray)
{
	// Update particle location
	x += deltaX;
	y += deltaY;
	yaw += deltaYaw;

	// Calculate predicted belief by previous belief and probability by move
	 double predictedBelief = belief * ProbByMove(deltaX, deltaY, deltaYaw);

	// Calculate new belief by normalization, predicted belief and probability by measure
	double newBelief = normalizationFactor *  predictedBelief * ProbByMeasure(laserArray);

	belief = newBelief;
}

//As more as the distance is shorter, the yaw is smaller and
double Particle::ProbByMove(double deltaX, double deltaY, double deltaYaw)
{
	//Calculate the distance between delta x and delta y by Pythagoras sentence
	double distance = sqrt(pow(deltaX, 2) + pow(deltaY, 2));

	//TODO:: check maxGoodDistance
	//Check the distance relative to some const that represent the maximum of distance we trust
	double distanceProbability = double (maxGoodDistance / distance);

	//probability can be between 0 and 1
	if (distanceProbability > 1)
		distanceProbability = 1;

	//TODO:: check maxGoodAngle
	//Check the angle relative to some const that represent the maximum of angle we trust
	double yawProbability = double(maxGoodAngle / abs(deltaYaw));

	//probability can be between 0 and 1
	if (yawProbability > 1)
		yawProbability = 1;

	return distanceProbability * yawProbability;
}

double Particle::ProbByMeasure(float* laserArray)
{
	double angleForLaser;
	float xForLaser;
	float yForLaser;
	int numOfErrors = 0;
	int numOfHits = 0;

	for (int currBeam = 0; currBeam < LASERS_NUMBER; currBeam += BEAMS_FOREACH_CHECK)
	{
		if (laserArray[currBeam] > BEAM_MAX_DISTANCE)
		{
			for (int curr_distance = MAPPING_START_POINT; curr_distance <= MAPPING_END_POINT; curr_distance+= 2.5)
			{
				angleForLaser = LaserHelper::indexToRad(currBeam) + yaw;
				xForLaser = x + (curr_distance * cos(angleForLaser));
				yForLaser = y + (curr_distance * sin(angleForLaser));
/*
				Point* point = new Point(xForLaser, yForLaser);
				Point gridPoint = map->getGridLocationBy(*point);
				int value = map->getGridValueAt(gridPoint);

				if (value == FREE)
				{
					numOfHits++;
				}
				else if (value == OCCUPIED)
				{
					numOfErrors++;
					SetFreeCell(*pnt);
				}
				else if (value == UNKNOWN)
				{
					numOfHits++;
					SetFreeCell(*pnt);
				}
			}

		}
		else
		{
			int distance = getValueByResolution(laserArray[currBeam]);

			if (distance < 5)
			{
				distance = 5;
			}

			angleForLaser = LaserHelper::indexToRad(currBeam) + yaw;
			xForLaser = x + (distance * cos(angleForLaser));
			yForLaser = y + (distance * sin(angleForLaser));

			Point* pnt = new Point(xForLaser, yForLaser);
			pnt = ConvertPositionToPoint(*pnt);

			pnt->PrintPoint();
			cout << "when occupied" << endl;

			if (GetCellValue(*pnt) == FREE)
			{
				cout << "clear" << endl;
				numOfErrors++;
				SetOccupiedCell(*pnt);
			}
			else if (GetCellValue(*pnt) == OCCUPIED)
			{
				cout << "occupied" << endl;
				numOfHits++;
			}
			else if (GetCellValue(*pnt) == UNKNOWN)
			{
				cout << "unknown" << endl;
				numOfHits++;
				SetOccupiedCell(*pnt);
			}

			cout << "check if got into the for " << endl;
			for (int curr_distance = distance-5; curr_distance >= MAPPING_START_POINT; curr_distance-= RESOLUTION )
			{

				angleForLaser = LaserHelper::indexToRad(currBeam) + yaw;
				yForLaser = y + (curr_distance * sin(angleForLaser));
				xForLaser = x + (curr_distance * cos(angleForLaser));

				Point* pnt = new Point(xForLaser, yForLaser);
				pnt = ConvertPositionToPoint(*pnt);

				pnt->PrintPoint();
				cout << "when clear2" << endl;

				if (GetCellValue(*pnt) == FREE)
				{
					numOfHits++;
				}
				else if (GetCellValue(*pnt) == OCCUPIED)
				{
					numOfErrors++;
					SetClearCell(*pnt);

				}
				else if (GetCellValue(*pnt) == UNKNOWN)
				{
					numOfHits++;
					SetClearCell(*pnt);
				}*/
			}
		}
	}

	return (float)(numOfHits/(numOfHits + numOfErrors));
}

//Create next generation for good particle
Particle * Particle::genereateNewParticle()
{
	int randomX = getRandomXInRadius();
	int randomY = getRandomYInRadius();
	int randomYaw = getRandomYaw();

	//Create particle with random position in the radius and same map and belief
	return new Particle(randomX, randomY, randomYaw, map, belief);
}

double Particle::getRandomXInRadius()
{
	//Add to current x number between 0 and radius
	return x + ((double)(rand() / RAND_MAX) + RADIUS - 1);
}
double Particle::getRandomYInRadius()
{
	//Add to current y number between 0 and radius
	return y+ ((double)(rand() / RAND_MAX) + RADIUS - 1);
}
//Return an number between 1 and 360
double Particle::getRandomYaw()
{
	return (rand() % MAX_ANGLE);
}

void Particle::Print()
{
	this->map->PrintGridMatrix();
}

Particle::~Particle()
{

}


