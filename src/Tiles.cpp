#include"Tiles.h"

Tile::Tile( int X, int Y, int W, int H, int Type )
{
	box.x = start_x = X;
	box.y = start_y = Y;

	box.w = W; 
	box.h = H; 
	type = Type;

	frame_line = 1;
	frame =	time_check = random = 0;

	start_hp = hp = 146;

	random = rand() % 30 + 3;

	play_sound = go_left = damaged = go_down = go_up  = dead = false;
}

void Tile::update( const int &man_x, bool restart )
{

	if ( type == TORCH )
	{
		frame = int(((SDL_GetTicks() / 60) % 4));
	}
	else if ( type == LAVA )
	{
		if ( int((SDL_GetTicks() / 100) % 2) != time_check )
		{
			time_check = int((SDL_GetTicks() / 100) % 2);

			if ( random )
				random--;
		
			if ( !random )
				frame++;

			if( frame >= 14 )
				frame = 0;
		}

		if ( !frame && !random )
		{
			random = rand() % 30 + 3;
		}
	}
	else if ( type == ARROW )
	{
		if ( man_x >= box.x - 70 && box.y <= SCREEN_HEIGHT || box.y != start_y )
			box.y += 8;
	}

	else if ( type == BOMB && dead && box.x >= 0 )
	{
		if (!play_sound)
		{
			Mix_PlayChannel( -1, explosion_sound, 0 ); 
			play_sound = true;
		}
		if ( int((SDL_GetTicks() / 60) % 2) != time_check )
		{
			time_check = int((SDL_GetTicks() / 60) % 2);

			frame++;

			if( frame >= 8 )
			{
				box.x = -100;
				frame = 0;
			}
		}
	}
	else if ( type == BAT )
	{
		if (dead && box.x > -50)
		{
			if ( int((SDL_GetTicks() / 40) % 2) != time_check )
			{
				time_check = int((SDL_GetTicks() / 40) % 2);

				frame++;

				if( frame >= 5 )
				{
					frame = 0;
					box.x = -50;
				}
			}
		}
		else if (box.x > -50)
		{
			frame = int((SDL_GetTicks() / 200) % 2);

			box.x -= 3;

			if (go_up)
				box.y -= 1;
			else
				box.y += 1;

			if (box.y <= start_y - 10)
				go_up = false;

			else if (box.y >= start_y + 10)
				go_up = true;
		}
	}
	else if ( type == GHOST )
	{
		if (dead)
		{
			if ( int((SDL_GetTicks() / 90) % 2) != time_check && frame >= 0 )
			{
				time_check = int((SDL_GetTicks() / 90) % 2);

				frame--;
				if (!frame)
					box.x = -100;
			}
		}
		else if ( man_x >= box.x - 150 )
		{
			if (!play_sound)
			{
				Mix_PlayChannel( -1, ghost_sound, 0 );
				play_sound = true;
			}

			if ( int((SDL_GetTicks() / 90) % 2) != time_check && frame <= 2 )
			{
				time_check = int((SDL_GetTicks() / 90) % 2);

				frame++;
			}

			if (go_up)
				box.y -= 1;
			else
				box.y += 1;

			if (box.y <= start_y - 5)
				go_up = false;

			else if (box.y >= start_y + 5)
				go_up = true;
		}
	}
	else if ( type == PLATFORM )
	{
		if (dead)
		{
			if ( int((SDL_GetTicks() / 50) % 2) != time_check )
			{
				time_check = int((SDL_GetTicks() / 50) % 2);

				frame++;
				if (frame >= 10)
					box.x = -100;
			}
		}
	}
	else if ( type == SPIKE_CEILING)
	{
		box.y++;
	}
	else if (type == ROCK && !FINALE)
	{
		if (man_x >= box.x - 25 && man_x <= box.x + box.w && !go_down )
			go_down = true;
		
		if (go_down)	box.y += 8;

		if (box.y >= SCREEN_HEIGHT)
		{
			go_down = false;
			box.y = start_y;
		}
	}

	else if (type == BOSS)
	{
		if (hp > 0)
		{
			frame = int((SDL_GetTicks() / 200) % 2);

			if (!damaged)
			{
				if (go_up)		box.y -= 2;
				else			box.y += 2;

				if (box.y <= start_y - 20)
				{
						go_up = false;
						play_sound = false;
				}
				else if (box.y >= start_y)
				{
					shake = true;
					go_up = true;
					if (!play_sound)
					{
						Mix_PlayChannel( -1, boss_jump_sound, 0 );
						play_sound = true;
					}
				}
			}
			else
			{
				if (box.y < start_y)			box.y += 2;
				else
				{
					if (go_left)		box.x -= 4;
					else				box.x += 4;

					if (box.x <= start_x - 80)		go_left = false;
					if (box.x >= start_x && !go_left)	
					{
						damaged = false;
						go_left = true;
						go_up = true;
					}
				}
			}
		}
		else
		{
			if (!play_sound && box.y <= start_y + 5 )
			{
					Mix_PlayChannel( -1, boss_dead_sound, 0 );
					play_sound = true;
			}

			if (box.y >= start_y + 50 && box.y <= start_y + 55)
			{
				play_sound = false;
			}

			if (box.y >= start_y + 200 && !play_sound)
			{
				Mix_PlayChannel( -1, boss_dead_sound2, 0 );
				play_sound = true;
			}

			if (box.y <= SCREEN_HEIGHT + 50)
			{
				if ( int((SDL_GetTicks() / 40) % 2) != time_check )
				{
					time_check = int((SDL_GetTicks() / 40) % 2);

					box.y += 1;
				}
			}
			else
				dead = true;
		}
	}
}

void Tile::restart()
{
	box.x = start_x;
	box.y = start_y;

	go_down = play_sound = dead = false;

	if (type == GHOST || type == PLATFORM)
		frame = 0;

	hp = start_hp;
}

SDL_Rect Tile::get_box()
{
	return box;
}