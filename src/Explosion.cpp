#include"Explosion.h"

Explosion::Explosion( int X, int Y )
{
	box.x = X + rand() % ( BOSS_WIDTH  + 5 ) * MAGNIFY - 50;
	box.y = Y + rand() % ( BOSS_HEIGHT + 5 ) * MAGNIFY - 50;

	box.w = EXPLOSION_WIDTH;
	box.h = EXPLOSION_HEIGHT;
	frame = 0;
	frame_line = 1;

	random = rand() % 60;

	play_sound = false;
}

void Explosion::update()
{
	if (FINALE)
	{		
		if ( random )
			random--;
		
		if (!random && frame == 0 && !play_sound)
		{
			Mix_PlayChannel( -1, explosion_sound, 0 );
			play_sound = true;
		}

		if ( !random )
			frame++;

		if (frame >= 6)
		{
			frame = 0;
			frame_line++;
		}

		if (frame_line >= 8)
		{
			box.x = rand() % ( SCREEN_WIDTH - 40 );
			box.y = rand() % ( SCREEN_HEIGHT - 40 );
			frame = 0;
			frame_line = 0;
			random = rand() % 60 + 10;
			play_sound = false;
		}
	}

	else
	{
		frame = 0;
		frame_line = 0;
	}
}
