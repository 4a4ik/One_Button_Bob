#ifndef BACKGROUND_H_INCLUDED
#define BACKGROUND_H_INCLUDED

#include"TextureManager.h"
#include"includes.h"


class Level
{
public:

	Level();

	SDL_Rect camera;
	SDL_Rect bg;

	int width, height;
	bool flip;
	std::string bg_name;

	void move( double xVel, double yVel );
};

#endif // BACKGROUND_H_INCLUDED