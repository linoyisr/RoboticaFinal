/*
 * Particle.h
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "Map.h"

class Particle
{
public:
	Particle();
	Particle(double x, double y, double yaw, Map* map, double belief);
	virtual ~Particle();
	double belief;
	double getRandomXbyR();
	double getRandomYbyR();
	double getRandomYawByR();
	double getBelief();
	Map* getMap();
	void Update(double delX, double delY, double delYaw, float* laserArray);
	void Print();
private:
	double x;
	double y;
	double yaw;
	Map * map;
	double calculateBeliefByDistance(double distance);
	double calculateBeliefByAngle(double angleDelta);

};

#endif /* PARTICLE_H_ */
