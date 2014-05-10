#ifndef BOOMERANG_H_INCLUDED
#define BOOMERANG_H_INCLUDED

#include"includes.h"
#include "Tiles.h"

class Boomerang
{
public:

	Boomerang(int X, int Y);

	double angle, xVel;

	unsigned int time_check;

	int col_tile;

	bool shoot, kill, play_sound;

	SDL_Rect box;

	void handle_input( int map_type );

	void update( std::vector<Tile> &tiles, int man_x, bool dead,  int map_type );

	SDL_Rect get_box();
};


#endif // BOOMERANG_H_INCLUDED