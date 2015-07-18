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

#define RADIUS 4
#define MAX_ANGLE 360
#define BEAM_MAX_DISTANCE 3.5

const int maxGoodDistance = 2; //if in the grid, else *10(grid resolution)
const int maxGoodAngle = 5; //if in degrees, else *M_PI/MAX_ANGLE
const double normalizationFactor = 1.3;
const double defaultBelief = 1;
const int beamsInAngle = (floor(1 / BEAM_FOREACH_ANGLE) + 1); //3
/*
Particle::Particle( Map* map)
: Particle::Particle(map->gridWidth/2, map->gridHeight/2, 0, map, defaultBelief)
{
}*/

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
	_x += deltaX;
	_y += deltaY;
	_yaw += deltaYaw;

	// Calculate predicted belief by previous belief and probability by move
	 double predictedBelief = belief * ProbByMove(deltaX, deltaY, deltaYaw);

	// Calculate new belief by normalization, predicted belief and probability by measure
	double newBelief = normalizationFactor *  predictedBelief * ProbByMeasure(laserScans);
	if (newBelief > 1)
		newBelief = 1;

	belief = newBelief;

	return belief;
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
{/*
	int numOfErrors = 0;
	int numOfHits = 0;

	// Not necessary to move of all the beams, read  all 2 degrees
	for (int currBeam = 0; currBeam < LASERS_NUMBER; currBeam += (beamsInAngle*2))
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
*/

	double numOfErrors = 0;
	double numOfHits = 0;

	for (int i=0; i< LASERS_NUMBER; i+= (beamsInAngle*2))
	{
		double laserAngle = laserIndexToLaserAngle(i);
		double distanceFromObstacle = laserScans[i] / 4;
		double obstacleXPos = (_x) + (distanceFromObstacle * cos(_yaw + laserAngle));
		double obstacleYPos = (_y) + (distanceFromObstacle * sin(_yaw + laserAngle));

		//check if it really obstacle
		int obstacleCellValue = map->getBlowMapMatrix()[obstacleYPos][obstacleXPos];

		// If the distance is tot much big, probably is not really obstacle
		// If the distance is too much small it can be the robot
		if (distanceFromObstacle < 5.0 && distanceFromObstacle > 0.5)
		{
			switch (obstacleCellValue)
			{
				case FREE:
					numOfErrors ++;
					break;
				case OCCUPIED:
					numOfHits ++;
					break;
				default:
					break;
			}
		}
	}
	//TODO:delete
	return 1;
	// Returns the number of hits from the total
	return (numOfHits / (numOfHits + numOfErrors));
}

double Particle::getAngleByIndex(int index)
{
	return ((double)index * BEAM_FOREACH_ANGLE - 30);
}

double Particle::getRadianByIndex(int index)
{
	return (getAngleByIndex(index) * M_PI / HALF_CYCLE);
}

double Particle::laserIndexToLaserAngle(int index)
{
	return ((index * 0.36 - 120) / HALF_CYCLE) * M_PI;
}

//Create next generation for good particle
Particle Particle::genereateNewParticle()
{
	int randomX = getRandomXInRadius();
	int randomY = getRandomYInRadius();
	int randomYaw = getRandomYaw();

	//Create particle with random position in the radius and same map and belief
	return Particle(randomX, randomY, randomYaw, map, belief);
}

double Particle::getRandomXInRadius()
{
	//Add to current x number between -radius and radius
	return _x +(rand() % (2*RADIUS)) - RADIUS;
}
double Particle::getRandomYInRadius()
{
	//Add to current y number between 0 and radius
	return _y +(rand() % (2*RADIUS)) - RADIUS;
}
//Return an number between 1 and 360
double Particle::getRandomYaw()
{
	return (rand() % MAX_ANGLE);
}

Location Particle::getLocation()
{
	return Location(_x,_y,_yaw);
}

void Particle::print()
{
	cout << "x: " << _x << " y:" <<_y << " yaw: " << _yaw << " belief: " << belief;
	cout << endl;
}
Particle::~Particle()
{

}


