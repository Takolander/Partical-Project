#include "Screen.h"

Screen::Screen(): m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer(NULL)
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
	m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);

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
	m_buffer = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];

	//Set memory values
	memset(m_buffer, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));

	//Looping all pixels and altering values
	for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++)
	{
		m_buffer[i] = 0x0000FF;
	}
	
	//Update texture and renderer
	SDL_UpdateTexture(m_texture, NULL, m_buffer, SCREEN_WIDTH * sizeof(Uint32));
	SDL_RenderClear(m_renderer);
	SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
	SDL_RenderPresent(m_renderer);
	
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
	//Destroys all pointers
	delete[] m_buffer;
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyTexture(m_texture);
	SDL_DestroyWindow(m_window);

	//Quit SDL
	SDL_Quit();
}
