/*
 * LocalizationManager.cpp
 *
 *  Created on: Jun 26, 2015
 *      Author: colman
 */

#include "LocalizationManager.h"
#include <vector>

//TODO:check
double const lowerThreshold = 0.3;
double const upperThreshold = 0.7;

LocalizationManager::LocalizationManager(Location* robotLocation, Map* map)
{
	_map = map;

	//create first particle by robot location
	Particle first(robotLocation->GetPoint()->GetX(), robotLocation->GetPoint()->GetY(), robotLocation->GetYawPoint(),  _map);
	_particles.push_back(&first);

}

LocalizationManager::~LocalizationManager()
{
}

vector<Particle*> LocalizationManager::getParticles()
{
	return _particles;
}

void LocalizationManager::Update(Location deltaLocation, float* laserScans)
{
	for(unsigned int i = 0; i < _particles.size(); i ++)
	{
		_particles[i]->Update(deltaLocation.GetPoint()->GetX(), deltaLocation.GetPoint()->GetY(), deltaLocation.GetYawPoint(),laserScans);

		double particleBelief = _particles[i]->getBelief();

		if(particleBelief >= upperThreshold)
		{
			Particle* newChild = _particles[i]->genereateNewParticle();
			_particles.push_back(newChild);
		}

		else if(particleBelief <= lowerThreshold)
		{
			_particles.erase(_particles.begin() + i);
		}
	}
}

void LocalizationManager::PrintParticles()
{
	for(unsigned int i = 0; i < _particles.size(); i ++)
	{
		cout << "particle " << i << ':';
		_particles[i]->print();
	}
}
