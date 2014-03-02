#include"Level.h"

Level::Level()
{

	width = 640;
	height = 480;

	bg.x = -width / 2;
	bg.y = 0;

	camera.x = 0;
	camera.y = 0;
	camera.w = SCREEN_WIDTH;
	camera.h = SCREEN_HEIGHT;

	bg_name = "bg";		
};


void Level::move( double xVel, double yVel )
{
	bg.x -= (int)xVel;
	bg.y -= (int)yVel;

	if( bg.x <= -width - 5)
		bg.x = width;

	if( bg.x >= width + 5 )
		bg.x = -width;
}

