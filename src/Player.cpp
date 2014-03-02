#include "Player.h"


void Player::handle_input( int type, SDL_Scancode key_code )
{

	if( type == 1 )
	{
		switch (key_code)
		{
			case SDL_SCANCODE_UP: yVel -= 2; break;
			case SDL_SCANCODE_DOWN: yVel += 2; break;
			case SDL_SCANCODE_LEFT: xVel -= 2; break;
			case SDL_SCANCODE_RIGHT: xVel += 2; break;
		}
		
	}
	else if( type == 0 )
	{
		switch (key_code)
		{
			case SDL_SCANCODE_UP: yVel += 2; break;
			case SDL_SCANCODE_DOWN: yVel -= 2; break;
			case SDL_SCANCODE_LEFT: xVel += 2; break;
			case SDL_SCANCODE_RIGHT: xVel -= 2; break;
		}
	}
}

void Player::update()
{
	/*
	x += xVel;
	y += yVel;
	*/

	frame = int(((SDL_GetTicks() / 100) % 3));

}

void Player::show()
{

}