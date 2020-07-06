#include <iostream>
#include <SDL.h>
#undef main

int main()
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
	{
		std::cout << "SDL init failed!" << std::endl;
		return 1;
	}

	std::cout << "SDL inint succeeded!" << std::endl;

	SDL_Quit();

	return 0;
}