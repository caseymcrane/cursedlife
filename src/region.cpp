#include <algorithm>
#include "cell.h"
#include "region.h"
#include <stdlib.h>
#include <stdio.h>
#include <curses.h>

Region::Region(int _xMin, int _xMax, int _yMin, int _yMax)
{
	xMin=_xMin;
	xMax=_xMax;
	yMin=_yMin;
	yMax=_yMax;
}

int Region::width()
{
	return xMax-xMin;
}

int Region::height()
{
	return yMax-yMin;
}

Region Region::combine(Region& r)
{
	int rW=(r.xMax-r.xMin);
	int rH=(r.yMax-r.yMin);
	int width = xMax-xMin;
	int height = yMax-yMin;
	if((abs(r.xMax-xMin)<(rW+width))&&(abs(r.yMax-yMin)<(rH+height)))
	{
		Region c(std::min(xMin,r.xMin),std::max(xMax,r.xMax),std::min(yMin,r.yMin),std::max(yMax,r.yMax));
		//Region& n = c;
		return c;
	}
	return r;
}

void Region::paint_region()
{
	for(int y=yMin;y<=yMax;y++)
	{
		for(int x=xMin;x<=xMax;x++)
		{
			mvaddch(y,x,'R');
		}
	}
}
