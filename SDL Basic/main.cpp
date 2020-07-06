#include <iostream>
#include <SDL.h>
//Must have because of error otherwise
#undef main

int main()
{
	//Constants for window size
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;

	//Initalize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL init failed!" << std::endl;
		return 1;
	}

	//Create window pointer
	SDL_Window* window = SDL_CreateWindow("Partical Fire Explosion", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	//Check if window pointer is NULL
	if (window == NULL)
	{
		SDL_Quit();
		return 2;
	}
	
	bool quit = false;

	SDL_Event event;

	//Event loop
	while (!quit)
	{
		//Update particals
		//Draw particals
		//Check for messages/events

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
		}
	}

	//Destroys window pointer
	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}