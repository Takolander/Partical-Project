#include <SDL.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "Screen.h"
#include "Swarm.h"
//Must have because of error with undefined symbol
#undef main

int main()
{
	//Start randomizer
	srand(time(NULL));

	Screen screen;

	//Error checking
	if (screen.init() == false) 
	{
		std::cout << "Error initialising SDL!" << std::endl;
	}

	Swarm swarm;

	//Event loop
	while (true)
	{
		int elapsed = SDL_GetTicks();

		swarm.update(elapsed);

		//Randomize values of RGB
		unsigned char green = (unsigned char)((1 + sin(elapsed * 0.0001)) * 128);
		unsigned char red = (unsigned char)((1 + sin(elapsed * 0.0002)) * 128);
		unsigned char blue = (unsigned char)((1 + sin(elapsed * 0.0003)) * 128);

		//Pointer to array of random particles
		const Particle* const pParticles = swarm.getParticles();

		//Add particles to screen
		for (int i = 0; i < Swarm::NPARTICLES; i++)
		{
			Particle particle = pParticles[i];

			int x = (particle.m_x + 1) * Screen::SCREEN_WIDTH / 2;
			int y = particle.m_y * Screen::SCREEN_WIDTH / 2 + Screen::SCREEN_HEIGHT /2;

			screen.setPixel(x, y, red, green, blue);
		}

		//Blur particles
		screen.boxBlur();

		//Draw the screen
		screen.update();

		//Check for messages/events
		if (screen.processEvents() == false) 
		{
			break;
		}
	}

	screen.close();

	return 0;
}