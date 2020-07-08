#include "Particle.h"
#include <stdlib.h>

Particle::Particle() 
{
	m_x = (2.0 * rand()) / RAND_MAX - 1;
	m_y = (2.0 * rand()) / RAND_MAX - 1;
}

Particle::~Particle() 
{

}