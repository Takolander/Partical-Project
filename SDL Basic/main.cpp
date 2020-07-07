#include <iostream>
#include <SDL.h>
#include "Screen.h"
//Must have because of error with undefined symbol
#undef main

int main()
{
	Screen screen;

	if (screen.init() == false) 
	{
		std::cout << "Error initialising SDL!" << std::endl;
	}

	//Event loop
	while (true)
	{
		//Update particals
		//Draw particals
		//Check for messages/events

		if (screen.processEvents() == false) 
		{
			break;
		}
	}

	screen.close();

	return 0;
}