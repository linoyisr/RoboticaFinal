/*
 * Particle.cpp
 */

#include "Particle.h"
#include "Map.h"
#include <math.h>
#include <cmath>
#include <stdlib.h>

#define RADIUS 1
#define UNLIKELY_DISTANCE 1
#define MAX_ANGLE 360
#define TRUST_ISSUES 0.3
#define UNLIKELY_ANGLE M_PI / 2

Particle::Particle()
{
	this->map = new Map();
	this->x = map->mapWidth/2;
	this->y = map->mapHeight/2;
	this->yaw = yaw;
	this->belief = 1;

}

Particle::~Particle() {
	// TODO Auto-generated destructor stub
}

Particle::Particle(double x, double y, double yaw, Map* map, double belief)
{
	this->x = x;
	this->y = y;
	this->yaw = yaw;
	this->map = map;
	this->belief = belief;
}

double Particle::getRandomXbyR()
{
	return this->x + (rand() % (RADIUS*2) - RADIUS);
}
double Particle::getRandomYbyR()
{
	return this->y + (rand() % (RADIUS*2) - RADIUS);
}
double Particle::getRandomYawByR()
{
	return this->yaw + (rand() % MAX_ANGLE);
}
double Particle::getBelief()
{
	return this->belief;
}
Map* Particle::getMap()
{
	return map;
}

double Particle::calculateBeliefByDistance(double distance)
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
}

void Particle::Update(double delX, double delY, double delYaw, float* laserArray)
{
	double distance = sqrt(pow(delX,2) + pow(delY,2));

	cout << "before cala belief" << endl;
	// Calculate predicted belief
	double predictedBelief = this->belief * calculateBeliefByDistance(distance) * calculateBeliefByAngle(abs(delYaw));

	// Update new location
	this->x += delX;
	this->y += delY;
	this->yaw += delYaw;

	try
	{
	predictedBelief = predictedBelief * this->map->UpdateMap(this->x, this->y, this->yaw, laserArray);
	}
	catch(exception e)
	{
		cout << e.what() << endl;
	}

	this->belief = predictedBelief;
}

void Particle::Print()
{
	this->map->PrintMatrix();
}


