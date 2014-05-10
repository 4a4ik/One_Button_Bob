#include"Font.h"

Font::Font()
{
	x3 = 25;
	x2 = x3 + SCORE_W + 15;
	x1 = x2 + SCORE_W + 15;
	
	y = 5;

	w = SCORE_W;
	h = SCORE_H;

	first = second = third = 0;
}

void Font::update( int map_type, int score )
{
	first = score % 10;
	second = score / 10 % 10;
	third = score / 100 % 10;

    if ( map_type == END )
	{
		x3 = 435;
		y = 230;
		
		x2 = x3 + SCORE_W + 15;
		x1 = x2 + SCORE_W + 15;
	}
}
