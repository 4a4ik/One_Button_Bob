#ifndef _TILE_H
#define _TILE_H

#include "includes.h"


class Tile
{
public:

	Tile(int X, int Y, int Tile_type) { box.x = X; box.y = Y; tile_type = Tile_type; box.w = TILE_WIDTH; box.h = TILE_HEIGHT; }

	void update();

	SDL_Rect box;

	int tile_type;

	int m_width;
	int m_height;

	int m_currentRow;
	int m_currentFrame;

	int frame;

//	std::string m_textureID;

};

#endif // _TILE_H

