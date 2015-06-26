/*
 * Particle.cpp
 */

#include "Particle.h"
#include "Map.h"
#include <math.h>
#include <cmath>
#include <stdlib.h>
using namespace std;

#define RADIUS 1
#define UNLIKELY_DISTANCE 1
#define MAX_ANGLE 360
#define TRUST_ISSUES 0.3
#define UNLIKELY_ANGLE M_PI / 2

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
/*

double Particle::calculateBeliefByDistance(double distance, double deltaYaw)
{
	if (distance >= UNLIKELY_DISTANCE)
	{
		return TRUST_ISSUES;
	}
	else
	{
		return (UNLIKELY_DISTANCE - distance);
	}
}

double Particle::calculateBeliefByAngle(double angleDelta)
{
	if (angleDelta >= UNLIKELY_ANGLE)
	{
		// TODO: we have a problem!!!!
		return TRUST_ISSUES;
	}
	else
	{
		return (UNLIKELY_ANGLE - angleDelta);
	}
}*/

void Particle::Update(double deltaX, double deltaY, double deltaYaw, float* laserArray)
{
	// Update particle location
	this->x += deltaX;
	this->y += deltaY;
	this->yaw += deltaYaw;

	// Calculate predicted belief by previous belief and probability by move
	 double predictedBelief = belief * ProbByMove(deltaX, deltaY, deltaYaw);

	// Calculate new belief by normalization, predicted belief and probability by measure
	double newBelief = normalizationFactor *  predictedBelief * ProbByMeasure(laserArray);

	this->belief = newBelief;
}

double Particle::ProbByMove(double deltaX, double deltaY, double deltaYaw)
{
	//Calculate the distance between delta x and delta y by Pythagoras sentence
	double distance = sqrt(pow(deltaX, 2) + pow(deltaY, 2));

	//TODO: need to calc
	double distanceProbability ;
	double yawProbability ;


	return yawProbability * distanceProbability;
}

//TODO: need to calc
double Particle::ProbByMeasure(float* laserArray)
{
	return 0;
}

//Create next generation for good particle
Particle * Particle::genereateNewParticle()
{
	int randomX = getRandomXByRadius();
	int randomY = getRandomYByRadius();
	int randomYaw = getRandomYawByRadius();

	//Create particle with random position in the radius and same map and belief
	return new Particle(randomX, randomY, randomYaw,map, belief);
}

double Particle::getRandomXByRadius()
{
	return x + (rand() % (RADIUS*2) - RADIUS);
}
double Particle::getRandomYByRadius()
{
	return y + (rand() % (RADIUS*2) - RADIUS);
}
double Particle::getRandomYawByRadius()
{
	return yaw + (rand() % MAX_ANGLE);
}

void Particle::Print()
{
	this->map->PrintMatrix();
}

Particle::~Particle()
{

}


