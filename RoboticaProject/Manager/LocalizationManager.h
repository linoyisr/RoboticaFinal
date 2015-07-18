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

public:
	LocalizationManager(Location robotLocation, Map* map);
	virtual ~LocalizationManager();
	void Update(Location deltaLocation, float* laserScans);
	vector<Particle> getParticles();
	Location GetBestLocation();
	Location GetGridBestLocation();
	void PrintParticles();
	vector<Particle> _particles;
};

#endif /* LOCALIZATIONMANAGER_H_ */
