#include "Particle.h"
#include <stdlib.h>
#include <math.h>
#define M_PI 3.14159265358979323846

Particle::Particle() : m_x(0), m_y(0)
{
	init();
}

void Particle::init()
{
	m_x = 0;
	m_y = 0;
	m_direction = (2 * M_PI * rand()) / RAND_MAX;
	m_speed = (0.04 * rand()) / RAND_MAX;

	m_speed *= m_speed;
}

Particle::~Particle() 
{

}

void Particle::update(int interval)
{
	//Add a curv element to the direction
	m_direction += interval * 0.0003;

	//Update x and y posistion of particle
	double xspeed = m_speed * cos(m_direction);
	double yspeed = m_speed * sin(m_direction);

	m_x += xspeed * interval;
	m_y += yspeed * interval;

	//Check if pixels come of screen
	if (m_x < -1 || m_x > 1 || m_y < -1 || m_y > 1)
	{
		init();
	}

	//Random pixels will be reinitilized
	if (rand() < RAND_MAX/100)
	{
		init();
	}
}