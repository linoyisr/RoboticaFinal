/*
 * LocalizationManager.cpp
 *
 *  Created on: Jun 26, 2015
 *      Author: colman
 */

#include "LocalizationManager.h"
#include <vector>

//TODO:check
double const lowerThreshold = 0.5;
double const upperThreshold = 0.7;

LocalizationManager::LocalizationManager(Location robotLocation, Map* map)
{
	_map = map;

	//create first particle by robot location
	Particle first(robotLocation.GetPoint().GetX(), robotLocation.GetPoint().GetY(), robotLocation.GetYawPoint(),  _map);
	_particles.push_back(first);

	// Create all other particles. Each time we create the particle
	// as the son of the last one we created.
	for(int i = 1; i < 10; i++)
	{
		Particle current = first.genereateNewParticle();
		_particles.push_back(current);
	}

	PrintParticles();
}

LocalizationManager::~LocalizationManager()
{
}

vector<Particle> LocalizationManager::getParticles()
{
	return _particles;
}

void LocalizationManager::Update(Location deltaLocation, float* laserScans)
{
	double currentBelief;

	for(unsigned int i = 0; i < _particles.size(); i ++)
	{
		currentBelief = _particles[i].Update
				(
						deltaLocation.GetPoint().GetX(),
						deltaLocation.GetPoint().GetY(),
						deltaLocation.GetYawPoint(),
						laserScans
				);

		if(currentBelief < lowerThreshold)
		{
			_particles.erase(_particles.begin() + i);
		}

		 else if ((currentBelief > upperThreshold) && _particles.size() < 50)
		{
			Particle newChild = _particles[i].genereateNewParticle();
			_particles.push_back(newChild);
		}
	}

	PrintParticles();
}

Particle LocalizationManager::GetBestParticle()
{
	Particle bestParticle = _particles[0];
	for(unsigned int i = 0; i < _particles.size(); i ++)
		{
			if (_particles[i].getBelief() > bestParticle.getBelief())
			{
				bestParticle = _particles[i];
			}
		}

	return bestParticle;
}

Location LocalizationManager::GetBestLocation()
{
	return GetBestParticle().getLocation();
}

Location LocalizationManager::GetGridBestLocation()
{
	Location bestLocation = GetBestParticle().getLocation();
	Point gridPoint = _map->getGridPointBy(bestLocation.GetPoint());

	return Location(gridPoint, bestLocation.GetYawPoint());
}

void LocalizationManager::PrintParticles()
{
	cout << "particles: " << endl;
	for(unsigned int i = 0; i < _particles.size(); i ++)
	{
		cout << "particle " << i << ':';
		_particles[i].print();
	}
}
