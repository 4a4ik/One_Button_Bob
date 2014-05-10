#ifndef EXPLOSION_H_INCLUDED
#define EXPLOSION_H_INCLUDED

#include"includes.h"

class Explosion
{
public:

	Explosion(int X, int Y);

	int boss_x, boss_y, random;

	unsigned int time_check;

	SDL_Rect box;

	int frame, frame_line;

	bool play_sound;

	void update( bool ending );

};


#endif // EXPLOSION_H_INCLUDED