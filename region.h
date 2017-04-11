#ifndef REGION_H
#define REGION_H

class Region {
	
	int xMin, xMax, yMin, yMax;
	Cell* cells;
	
	public:
	
	Region(int, int, int, int);
	int width();
	int height();
	void paint_region();
	Region combine(Region&);
};

#endif
