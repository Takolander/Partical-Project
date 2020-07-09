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

	Swarm swarm;

	//Error checking
	if (screen.init() == false) 
	{
		std::cout << "Error initialising SDL!" << std::endl;
	}

	//Event loop
	while (true)
	{
		//Update particals
		
		//Draw particals
		int elapsed = SDL_GetTicks();

		screen.clear();
		swarm.update(elapsed);

		//Randomize values of RGB
		unsigned char green = (1 + sin(elapsed * 0.001)) * 128;
		unsigned char red = (1 + sin(elapsed * 0.002)) * 128;
		unsigned char blue = (1 + sin(elapsed * 0.003)) * 128;

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