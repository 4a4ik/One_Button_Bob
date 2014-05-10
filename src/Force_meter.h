#ifndef _FORCE_METER_H
#define _FORCE_METER_H

#include "includes.h"


class Force_meter
{
public:

	//Force_meter(int X, int Y) ;

	void update( int man_x, int man_y, int force, int map_type );

	int x, y, r_x, r_y, width;

};

#endif // _FORCE_METER_H