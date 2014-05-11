#ifndef _PLAYER_H
#define _PLAYER_H

#include "includes.h"
#include"Tiles.h"

class Player
{
public:

	Player(int X, int Y) ;

	void handle_input( int type, SDL_Scancode key_code, int map_type );
	void update( std::vector<Tile> &tiles, int map_type, bool ending  );

	SDL_Rect box;
	SDL_Rect get_box();

	bool dead, restart, jump, pressed, go_right, play_sound;

	int shake;

	float xVel, yVel, force;

	int col_tile, start_x, start_y;

	int level_x, level_y;

	int m_currentRow;
	int m_currentFrame;

	int frame, frame_line, time_check;
};

#endif // _PLAYER_H

