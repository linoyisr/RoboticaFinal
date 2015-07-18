/*
 * Particle.h
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "Map.h"
#include "Location.h"
class Particle
{
public:
	Particle(Map* map);
	Particle(double x, double y, double yaw, Map* map);
	Particle(double x, double y, double yaw, Map* map, double belief);
	virtual ~Particle();
	double getBelief();
	Map* getMap();
	double Update(double delX, double delY, double delYaw, float* laserScans);
	double getRandomXInRadius();
	double getRandomYInRadius();
	double getRandomYaw();
	Location getLocation();
	Particle genereateNewParticle();

	void print();

private:
	double _x;
	double _y;
	double _yaw;
	double belief;
	Map * map;
	double ProbByMove(double deltaX, double deltaY, double deltaYaw);
	double ProbByMeasure(float* laserScans);
	double getAngleByIndex(int index);
	double getRadianByIndex(int index);
	double laserIndexToLaserAngle(int index);
};

#endif /* PARTICLE_H_ */
