#ifndef _FONT_H
#define _FONT_H

#include "includes.h"

//Texture wrapper class
class Font
{
    public:
		//Initializes variables
		Font();

		int y, w, h, x1, x2, x3;

		int first, second, third;

        //Deallocates texture
        void update( int map_type, int score );
};

#endif