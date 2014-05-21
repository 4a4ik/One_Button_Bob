#include"Force_meter.h"

void Force_meter::update( int man_x, int man_y, int force, int map_type )
{
	width = force;

	if (map_type == CLICK_JUMP || map_type == CLICK_JUMP_STOP )
	{
		x = man_x - 8;
		y = man_y - 30;

		r_x = x + 4;
		r_y = y + 4;
	}
	else if (map_type == CLICK_BOSS)
	{
		x = 20;
		y = 60;

		r_x = x + 8;
		r_y = y + 8;
	}
	else		x = -100;
}