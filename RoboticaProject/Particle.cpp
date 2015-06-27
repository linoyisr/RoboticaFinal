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
#define BEAM_MAX_DISTANCE 3.5

const int maxGoodDistance = 2; //if in the grid, else *10(grid resolution)
const int maxGoodAngle = 5; //if in degrees, else *M_PI/MAX_ANGLE
const double normalizationFactor = 1.3;
const double defaultBelief = 1;

Particle::Particle( Map* map)
: Particle::Particle(map->gridWidth/2, map->gridHeight/2, 0, map, defaultBelief)
{
}

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

void Particle::Update(double deltaX, double deltaY, double deltaYaw, float* laserScans)
{
	// Update particle location
	x += deltaX;
	y += deltaY;
	yaw += deltaYaw;

	// Calculate predicted belief by previous belief and probability by move
	 double predictedBelief = belief * ProbByMove(deltaX, deltaY, deltaYaw);

	// Calculate new belief by normalization, predicted belief and probability by measure
	double newBelief = normalizationFactor *  predictedBelief * ProbByMeasure(laserScans);

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

double Particle::ProbByMeasure(float* laserScans)
{
	int numOfErrors = 0;
	int numOfHits = 0;

	//TODO: Not necessary to move of all the beams,
	for (int currBeam = 0; currBeam < LASERS_NUMBER; currBeam ++)
	{
		//TODO: check if work!!!
		double angleForLaser = LaserHelper::indexToRad(currBeam) + yaw;

		double xForLaser = x + cos(angleForLaser);
		double yForLaser = y + sin(angleForLaser);

		//calculate x,y of the obstacle
		int obstacleRealY = floor(x + (double((laserScans[currBeam]) * yForLaser)));
		int obstacleRealX = floor(y + (double((laserScans[currBeam]) * xForLaser)));
		Point obstacleRealPoint(obstacleRealX, obstacleRealY);

		//Convert real point of the obstacle to grid point
		Point obastcleGridPoint = map->getRealLocationBy(obstacleRealPoint);

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
	return (double)(numOfHits/(numOfHits + numOfErrors));
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

void Particle::print()
{
	cout << 'x: ' << x << ' y:' << y << ' yaw: ' << yaw << ' belief: ' << belief;
	cout << endl;
}
Particle::~Particle()
{

}


