#include"Boomerang.h"

Boomerang::Boomerang(int X, int Y)
{
	box.x = X;
	box.y = Y;
	play_sound = false;
}


void Boomerang::handle_input( int map_type )
{
	if (!shoot)
	{
		shoot = true;
		xVel = 12;

		if (box.x > 0 && map_type != CLICK_BOSS)		Mix_PlayChannel( -1, boomerang_sound, 0 );
	}
}

void Boomerang::update( std::vector<Tile> &tiles, int man_x, bool dead, int map_type)
{
	if (map_type == CLICK_BOSS && !shoot && !dead && man_x > 0 && !FINALE)
	{		
		shoot = true;
		xVel = 12;
		kill = true;
		if (box.x > 0)		Mix_PlayChannel( -1, boomerang_sound, 0 );
	}

	if (map_type == CLICK_SHOOT || map_type == CLICK_BOSS)
	{
		if (dead) box.x = -150;

		if (shoot)
		{
			angle += 30;

			xVel -= 0.4;

			box.x += (int)xVel;

			if (box.x <= man_x + 38) 
			{
				box.x = man_x + 38;
				angle = 0;
				shoot = false;
			}

			if (touches_enemy( box, tiles, col_tile ))
			{
				if (tiles[ col_tile ].type >= BOMB && tiles[ col_tile ].type <= GHOST)
				{
					tiles[ col_tile ].killer = true;
					tiles[ col_tile ].dead = true;
					xVel = -2;
				}
				else if(tiles[ col_tile ].type == BOSS && !kill)
				{
					xVel = -4;
				}
				else if (tiles[ col_tile ].type == BOSS && kill)
				{
					tiles[ col_tile ].hp -= 10;
					xVel = -4;
					tiles[ col_tile ].damaged = true;
					kill = false;

					if (!play_sound)
					{
						Mix_PlayChannel( -1, hurt_sound, 0 );
						play_sound = true;
					}
				}
			}
		}
		else if (!dead)
			box.x = man_x + 38;

		if( angle >= 360 ) angle = 0;
	}
	else
		box.x = -150;
}

SDL_Rect Boomerang::get_box()
{
	return box;
}