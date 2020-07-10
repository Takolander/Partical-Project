#include "Screen.h"

Screen::Screen(): m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer1(NULL), m_buffer2(NULL)
{

}

bool Screen::init()
{
	//Initalize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		return false;
	}

	//Create window pointer
	m_window = SDL_CreateWindow("Partical Fire Explosion", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	//Check if window pointer is NULL
	if (m_window == NULL)
	{
		SDL_Quit();
		return false;
	}

	//Renderer and Texture creation
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
	m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);

	//Error check
	if (m_renderer == NULL)
	{
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}

	if (m_texture == NULL)
	{
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}

	//Memory for pixels
	m_buffer1 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
	m_buffer2 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];

	//Set memory values
	memset(m_buffer1, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
	memset(m_buffer2, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
	
	return true;
}

bool Screen::processEvents()
{
	//Create event
	SDL_Event event;

	//Checks for quit event
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			 return false;
		}
	}

	return true;
}

void Screen::close()
{
	//Destroy all pointers
	delete[] m_buffer1;
	delete[] m_buffer2;
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyTexture(m_texture);
	SDL_DestroyWindow(m_window);

	//Quit SDL
	SDL_Quit();
}

void Screen::update()
{
	//Update texture and renderer
	SDL_UpdateTexture(m_texture, NULL, m_buffer1, SCREEN_WIDTH * sizeof(Uint32));
	SDL_RenderClear(m_renderer);
	SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
	SDL_RenderPresent(m_renderer);
}

void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue)
{
	//Error prevention
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
	{
		return;
	}

	//Sets color of pixel
	Uint32 color = 0;

	color += red;
	color <<= 8;
	color += green;
	color <<= 8;
	color += blue;
	color <<= 8;
	color += 0xFF;

	m_buffer1[(y * SCREEN_WIDTH) + x] = color;
}

void Screen::boxBlur()
{
	//Swaping buffer1 and buffer2
	Uint32 *temp = m_buffer1;

	m_buffer1 = m_buffer2;
	m_buffer2 = temp;

	//Loop the screen
	for (int y = 0; y < SCREEN_HEIGHT; y++)
	{
		for (int x = 0; x < SCREEN_WIDTH; x++)
		{
			//Total color values
			int redTotal = 0;
			int greenTotal = 0;
			int blueTotal = 0;

			for (int row = -1; row <= 1; row++)
			{
				for (int col = -1; col <= 1; col++)
				{
					/* 0 0 0
					*  0 1 0
					*  0 0 0
					*/
					int currentX = x + col;
					int currentY = y + row;

					//Check that we are not outside the window
					if (currentX >= 0 && currentX < SCREEN_WIDTH && currentY >= 0 && currentY < SCREEN_HEIGHT)
					{
						//Extract red, green and blue values
						Uint32 color = m_buffer2[currentY * SCREEN_WIDTH + currentX];

						Uint8 red = color >> 24;
						Uint8 green = color >> 16;
						Uint8 blue = color >> 8;

						redTotal += red;
						greenTotal += green;
						blueTotal += blue;
					}
				}
			}

			Uint8 red = redTotal / 9;
			Uint8 green = greenTotal / 9;
			Uint8 blue = blueTotal / 9;

			setPixel(x, y, red, green, blue);
		}
	}
}