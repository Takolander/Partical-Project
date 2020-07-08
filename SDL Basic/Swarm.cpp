#include "Swarm.h"

Swarm::Swarm() 
{
	m_pParticles = new Particle[NPARTICLES];
}

Swarm::~Swarm() 
{
	delete[] m_pParticles;
}