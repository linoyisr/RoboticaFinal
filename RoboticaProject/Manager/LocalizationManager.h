/*
 * LocalizationManager.h
 *
 *  Created on: Jun 26, 2015
 *      Author: colman
 */

#include <vector>
#include "../Particle.h"
#include "../Location.h"

#ifndef LOCALIZATIONMANAGER_H_
#define LOCALIZATIONMANAGER_H_

class LocalizationManager {
private:
	Map *_map;
	vector<Particle*> _particles;
public:
	LocalizationManager(Location* robotLocation, Map* map);
	virtual ~LocalizationManager();
	void Update(Location deltaLocation, float* laserScans);
	vector<Particle*> getParticles();
	void PrintParticles();
};

#endif /* LOCALIZATIONMANAGER_H_ */
