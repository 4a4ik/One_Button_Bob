#ifndef _SCORE_H
#define _SCORE_H

#include "includes.h"

class Score
{
    public:

		Score();

		int y, w, h, x1, x2, x3, x4;

		int first, second, third, fourth;

        void update( int map_type, int score );
};

#endif