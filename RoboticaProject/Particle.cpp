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


#define RADIUS 0.1
#define MAX_ANGLE 360
#define BEAM_MAX_DISTANCE 3.5

const int maxGoodDistance = 2; //if in the grid, else *10(grid resolution)
const int maxGoodAngle = 5; //if in degrees, else *M_PI/MAX_ANGLE
const double normalizationFactor = 1.3;
const double defaultBelief = 1;
const int beamsInAngle = (floor(1 / BEAM_FOREACH_ANGLE) + 1); //=3

Particle::Particle(double x, double y, double yaw, Map* map)
: Particle::Particle(x, y, yaw, map, defaultBelief)
{
}

Particle::Particle(double x, double y, double yaw, Map* map, double belief)
{
	this->_x = x;
	this->_y = y;
	this->_yaw = yaw;
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

double Particle::Update(double deltaX, double deltaY, double deltaYaw, float* laserScans)
{
	// Update particle location

	_x = fixValueByLimits(_x + (deltaX*10), 0, (map->mapWidth - 1));
	_y = fixValueByLimits(_y + (deltaY*10), 0, (map->mapHeight - 1));

	float currYaw = _yaw + deltaYaw;
	//change negative yaw to be positive (yaw between -180 to 180 - > yae between 0 to 360)
	//_yaw = (currYaw > 0 ? currYaw : 2 * M_PI + currYaw);
	_yaw = _yaw + deltaYaw;

	// Calculate predicted belief by previous belief and probability by move
	 double predictedBelief = belief * probByMove(deltaX, deltaY, deltaYaw);

	// Calculate new belief by normalization, predicted belief and probability by measure
	double newBelief = normalizationFactor *  predictedBelief * probByMeasure(laserScans);
	if (newBelief > 1)
		newBelief = 1;

	belief = newBelief;

	return belief;
}

//As more as the distance is shorter, the yaw is smaller and
double Particle::probByMove(double deltaX, double deltaY, double deltaYaw)
{
	//Calculate the distance between delta x and delta y by Pythagoras sentence
	double distance = sqrt(pow(deltaX, 2) + pow(deltaY, 2));

	//Check the distance relative to some const that represent the maximum of distance we trust
	double distanceProbability = double (maxGoodDistance / distance);

	//probability can be between 0 and 1
	if (distanceProbability > 1)
		distanceProbability = 1;

	//Check the angle relative to some const that represent the maximum of angle we trust
	double yawProbability = double(maxGoodAngle / abs(deltaYaw));

	//probability can be between 0 and 1
	if (yawProbability > 1)
		yawProbability = 1;

	return distanceProbability * yawProbability;
}

double Particle::probByMeasure(float* laserScans)
{
	int numOfErrors = 0;
	int numOfHits = 0;

	// Not necessary to move of all the beams, read  all 2 degrees
	for (int currBeam = 0; currBeam < LASERS_NUMBER; currBeam += 10)
	{
		//TODO: check if work!!!
		double angleForLaser = LaserHelper::indexToRad(currBeam) + _yaw;

		double xForLaser = _x + cos(angleForLaser);
		double yForLaser = _y + sin(angleForLaser);

		//calculate x,y of the obstacle
		int obstacleRealY = floor(_x + (double((laserScans[currBeam]) * yForLaser)));
		int obstacleRealX = floor(_y + (double((laserScans[currBeam]) * xForLaser)));
		Point obstacleRealPoint(obstacleRealX, obstacleRealY);

		//Convert real point of the obstacle to grid point
		Point obastcleGridPoint = map->getGridPointBy(obstacleRealPoint);

		if(laserScans[currBeam] < BEAM_MAX_DISTANCE)
		{
			//Make sure there is no creep from map scope
			if((obastcleGridPoint.GetX() >= 0) && ( obastcleGridPoint.GetX() <= (int)map->gridWidth) &&
			(obastcleGridPoint.GetY() >= 0) && (obastcleGridPoint.GetY() <= (int)map->gridHeight))
			{
				//check if it really obstacle
				if(map->getGridValueAt(obastcleGridPoint) == OCCUPIED)
				{
					numOfHits++;
				}
				else
				{
					numOfErrors++;
				}
			}
			else
			{
				numOfErrors++;
			}
		}
	}
	// Returns the number of hits from the total
	return (numOfHits / (numOfHits + numOfErrors));
}

float Particle::fixValueByLimits(float value, float minValue, float maxValue)
{
	if ((value >= minValue) && (value <= maxValue))
	{
		return value;
	}
	else if (value < minValue)
	{
		return minValue;
	}

	//(value > maxValue )
	else
	{
		return maxValue;
	}
}

//Create next generation for good particle
Particle Particle::genereateNewParticle()
{
	double randomX = getRandomXInRadius();
	double randomY = getRandomYInRadius();
	int randomYaw = getRandomYaw();

	//Create particle with random position in the radius and same map and belief
	return Particle(randomX, randomY, randomYaw, map, belief);
}

double Particle::getRandomXInRadius()
{
	//Add to current x number between -radius and radius
	return _x + getRandom();
}

double Particle::getRandomYInRadius()
{
	//Add to current y number between 0 and radius
	return (_y + getRandom());
}

double Particle::getRandom()
{
    double d = (double)rand() / RAND_MAX;
    return -RADIUS + d * (2*RADIUS);
}

//Return an number between 1 and 360
double Particle::getRandomYaw()
{
	return (rand() % MAX_ANGLE);
}

Location Particle::getLocation()
{
	return Location(Point(_x,_y),_yaw);
}

void Particle::print()
{
	cout << "x: " << _x << " y:" <<_y << " yaw: " << _yaw << " belief: " << belief;
	cout << endl;
}
Particle::~Particle()
{

}


