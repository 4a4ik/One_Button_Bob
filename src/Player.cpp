#include "Player.h"
#include "Tiles.h"
#include "includes.h"

#define MAN_XPEED 3
#define GRAVITY_SPEED 0.5f
#define JUMP_SPEED -7

Player::Player(int X, int Y) 
{
	box.x = start_x = X; 
	box.y = start_y = Y; 
	box.w = MAN_WIDTH * MAGNIFY; 
	box.h = MAN_HEIGHT * MAGNIFY; 

	level_x = level_y = 0;
	frame = shake = 0;

	frame_line = 3;

	go_right = true;

	sound = dead = jump = pressed = restart = false;
}

void Player::handle_input( int type, SDL_Scancode key_code, int map_type )
{
	/*
	if( type == 1 && !dead)
	{
		switch (key_code)
		{
			case SDL_SCANCODE_UP: yVel = JUMP_SPEED; break;
		//	case SDL_SCANCODE_DOWN: yVel += 2; break;
			case SDL_SCANCODE_LEFT: xVel = -MAN_XPEED; break;
			case SDL_SCANCODE_RIGHT: xVel = MAN_XPEED; break;
		}
	}
	else if( type == 0 && !dead)
	{
		switch (key_code)
		{
		//	case SDL_SCANCODE_UP: yVel += 2; break;
		//	case SDL_SCANCODE_DOWN: yVel -= 2; break;
			case SDL_SCANCODE_LEFT: xVel = 0; break;
			case SDL_SCANCODE_RIGHT: xVel = 0; break;
		}
	}*/

	if (type == 3 && !dead )		pressed = true;

	else if (type == 4 && !dead)		pressed = false;

	if (type == 4 && !jump && !dead && ( map_type == CLICK_JUMP || map_type == CLICK_JUMP_STOP ) )
	{
		yVel = -force * 0.9f;
		xVel = force * 0.35f;
		jump = true;
		force = 0;
		Mix_PlayChannel( -1, jump_sound, 0 );  
	}
}

SDL_Rect Player::get_box()
{
	return box;
}

void Player::update( std::vector<Tile> &tiles, int map_type, bool ending )
{	
	if (ending || map_type == CLICK_LEDDER || map_type == CLICK_SHOOT || map_type == CLICK_JUMP || map_type == CLICK_STOP )
		go_right = true;

	if (map_type == CLICK_BOSS && pressed && !FINALE)
	{
		go_right = !go_right;
		pressed = false;
	}
	if (!ending && map_type != CLICK_JUMP_STOP && map_type != CLICK_ACCELERATE)
	{
		if (go_right)  xVel =  MAN_XPEED;
		if (!go_right) xVel = -MAN_XPEED;
	}

	if (map_type == CLICK_JUMP_STOP && jump)		xVel = MAN_XPEED;

	if (!dead)			frame = int(((SDL_GetTicks() / 200) % 2));

	if (force <= 12 && pressed && ( map_type == CLICK_JUMP || map_type == CLICK_JUMP_STOP ))			
		force += 0.3f;

	if (pressed && map_type == CLICK_STOP)			xVel = 0;

	if (pressed && map_type == CLICK_ACCELERATE)
	{
		xVel += 1.2f;
		pressed = false;
	}

	else if (map_type == CLICK_ACCELERATE && xVel >= 0)			xVel -= 0.2f;

	// Move man RIGHT
	if (!dead && !ending && map_type != END)			box.x += (int)xVel;

	//Off the screen
	if( box.x < 0 || touches_wall( box, tiles, col_tile ) )
		box.x -= (int)xVel;

	box.y += (int)yVel;

	if( !touches_wall( box, tiles, col_tile ) )			yVel += GRAVITY_SPEED;

	if ( touches_wall( box, tiles, col_tile ) )
	{
		tiles[ col_tile ].dead = true;

		//IF fall
		if ( yVel > 0 )					box.y = (int)tiles[ col_tile ].box.y - box.h;

		else if ( yVel < 0 )			box.y = tiles[ col_tile ].box.y + tiles[ col_tile ].box.h;	

		yVel = 0;

		if (jump)
		{
			xVel = 0; 
			jump = false;
		}
	}

	if (touches_ledder( box, tiles ) && pressed)
	{
		if (box.y >= 210)		box.y = 188;
		else if (box.y < 210)		box.y = 287;
		pressed = false;
	}

	if( ( box.y >= SCREEN_HEIGHT - 185 || touches_enemy( box, tiles, col_tile  ) ) && !dead && !FINALE)
	{
		dead = true;
		shake = 1;

		tiles[ col_tile ].killer = 1;
		frame = 0;
		force = 0;
	}

	if (dead)
	{
		force = 0;
		pressed = false;
		if (!sound)      
		{
				Mix_PlayChannel( -1, dead_sound, 0 ); 
				sound = true;
		}

		xVel = 0;
		yVel = 0;
		if ( int((SDL_GetTicks() / 100) % 2) != time_check )
		{
			time_check = int((SDL_GetTicks() / 100) % 2);

			frame++;

			frame_line = 2;

			if( frame >= 7 )
			{
				dead = false;
				restart = true;
				sound = false;
			}
		}
	}

	if (restart)
	{
		go_right = true;
		frame = 0;
		box.x = start_x;
		box.y = start_y;
		xVel = 0;
		yVel = 0;

		if (map_type == CLICK_SHOOT || map_type == CLICK_BOSS)
			frame_line = 3;
		else
			frame_line = 1;
	}

	if( shake )
	{
		level_x = rand() % 10 - 5;
		level_y = rand() % 10 - 5;
		shake++;

		if( shake >= 30 ) 
		{
			level_x = 0;
			level_y = 0;
			shake = 0;
		}
	}
}