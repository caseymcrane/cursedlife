#include "cell.h"

Cell::Cell(int _y, int _x, int s)
{
	y=_y;
	x=_x;
	state=s;
}

void Cell::set_state(int s)
{
	state=s;
}
