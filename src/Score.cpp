#include"Score.h"

Score::Score()
{
	x4 = 25;
	x3 = x4 + SCORE_W + 15;
	x2 = x3 + SCORE_W + 15;
	x1 = x2 + SCORE_W + 15;
	
	x4 = 25 - SCORE_W * 3 - 15 * 3;

	y = 5;

	w = SCORE_W;
	h = SCORE_H;

	fourth = first = second = third = 0;
}

void Score::update( int map_type, int score )
{
	first = score % 10;
	second = score / 10 % 10;
	third = score / 100 % 10;
	fourth = score / 1000 % 10;

	if ( map_type == END )
	{
		y = 230;
		if (score >= 1000)			x4 = 405;
		else						x4 = 390;
	}

	else if (score >= 1000)		x4 = 25;

	else if (score >= 100)		x4 = 25 - SCORE_W - 15;

	else if (score >= 10)		x4 = 25 - SCORE_W * 2 - 15 * 2;

	x3 = x4 + SCORE_W + 15;
	x2 = x3 + SCORE_W + 15;
	x1 = x2 + SCORE_W + 15;
}
