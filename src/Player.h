#ifndef _PLAYER_H
#define _PLAYER_H

#include "includes.h"


class Player
{
public:

	Player(float X, float Y) { x = X; y = Y; m_width = 38; m_height = 48; };

	void handle_input( int type, SDL_Scancode key_code );
	void update();
	void show();

	float x, y, xVel, yVel;

	int m_width;
	int m_height;

	int m_currentRow;
	int m_currentFrame;

	int frame;

//	std::string m_textureID;

};

#endif // _PLAYER_H

