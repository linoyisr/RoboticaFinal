/*
 * Particle.h
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "Map.h"

class Particle
{
public:
	Particle(double x, double y, double yaw, Map* map);
	Particle(double x, double y, double yaw, Map* map, double belief);
	virtual ~Particle();
	double getBelief();
	Map* getMap();
	void Update(double delX, double delY, double delYaw, float* laserArray);
	double getRandomXInRadius();
	double getRandomYInRadius();
	double getRandomYaw();
	Particle * genereateNewParticle();

	void Print();
private:
	double x;
	double y;
	double yaw;
	double belief;
	Map * map;
	double ProbByMove(double deltaX, double deltaY, double deltaYaw);
	double ProbByMeasure(float* laserArray);
};

#endif /* PARTICLE_H_ */
