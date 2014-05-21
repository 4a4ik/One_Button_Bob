#ifndef _GAME_H
#define _GAME_H

#include"includes.h"

class Game
{
public:

	int clicks;

	bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handle_events();

	void update();
	void clean();

	bool Running, pause;

	int map_type, level;
		
	std::string level_name;

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
};


#endif 