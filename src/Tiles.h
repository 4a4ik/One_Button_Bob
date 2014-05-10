#ifndef _TILES_H
#define _TILES_H

#include"includes.h"

class Tile
{
public:

	Tile( int X, int Y, int W, int H, int Type );

	int type, img_num, frame, random;

	unsigned int time_check;

	int start_x, start_y, frame_line, hp, start_hp;

	bool killer, go_up, go_down, go_left, dead, damaged, shake, play_sound;

	SDL_Rect box;

	void update( const int &man_x, bool restart  );

	void restart();

	SDL_Rect get_box();

};

bool touches_wall( SDL_Rect &box, std::vector<Tile> &tiles, int &col_box );
bool touches_enemy( SDL_Rect &box, std::vector<Tile> &tiles, int &col_box );
bool touches_ledder( SDL_Rect &box, std::vector<Tile> &tiles );
bool set_tiles( std::vector<Tile> &tiles, int level_num );
void save_tiles( std::vector<Tile> &tiles, int level_num );
void change_tiles( std::vector<Tile> &tiles, int x, int y, int type, int action );

#endif  //  _TILES_H