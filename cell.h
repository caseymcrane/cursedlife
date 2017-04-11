#ifndef CELL_H
#define CELL_H

class Cell {
	
	int x;
	int y;
	int state;
	
public:
	
	Cell(int, int, int);
	//Cell* getCell(int, int);
	void set_state(int);

};

#endif
