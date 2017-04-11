/*
 * main.cpp
 * 
 * Copyright 2017 Unknown <casey@ozma>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <iostream>
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>

#include "cell.h"
#include "region.h"


//here we do all the miscellaneous curses setup and return
//the character we'll be using for curses_input
int init_curses()
{
	//set the screen to curses mode
	initscr();
	
	//don't echo what the user types to the console
	noecho();
	
	//allows characters typed by the user to bypass most character
	//processing and be immediately available to the program
	cbreak();
	
	//lets us take keypad input
	keypad(stdscr, true);
	
	//makes the cursor invisible
	//curs_set(0);
	
	//we need this to update the screen. our getch() input
	//loop down below will also do that, but we haven't set that up
	//at this point
	refresh();
	
	//we have to initialize ch, so we set it to the value curses
	//expects when there's no input.
	int ch = ERR;
	
	return ch;	
}

int rule[2][9] = {	{-1, 3,-1,-1,-1,-1,-1,-1,-1},
					{ 0, 1, 4, 5, 6, 7, 8,-1,-1}};

/*
class Cell {
	
	int x;
	int y;
	int state;
	
public:
	
	Cell(int, int, int);
	//Cell* getCell(int, int);
	void set_state(int);

};

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
*/

int neighbors(int y,int x)
{
	int n = 0;
	
	for (int i=-1;i<=1;i++) 
	{ 
		for(int j=-1;j<=1;j++)
		{
			if(mvinch(y+i,x+j)=='*') n++;
		}
	}
	
	if(mvinch(y,x)=='*') n--;
	return n;
}

void gen(int yMax,int xMax)
{
	for(int x=0; x<yMax; x++)
	{
		for(int y=0; y<yMax; y++)
		{
			for(int i=0; i<9; i++)
			{
				if((mvinch(y,x)=='*')&&(neighbors(y,x)==rule[1][i]))
				{
					mvaddch(y,x,' ');
				}
				if((mvinch(y,x)==' ')&&(neighbors(y,x)==rule[0][i]))
				{
					mvaddch(y,x,'*');
				}
			}
		}
	}
}

int main(int argc, char **argv)
{

	int ch = init_curses();
	
	int cy=1;
	int cx=1;
	
	//this is our main input loop. we lazily use while(1) with the
	//expectation that the user will just ctrl+C if they want to quit
	while(1)
{
	
	ch=getch();
	
	switch(ch)
	{
		case KEY_UP:
			cy--;
			break;
		case KEY_DOWN:
			cy++;
			break;
		case KEY_LEFT:
			cx--;
			break;
		case KEY_RIGHT:
			cx++;
			break;
		case 'f':
			mvprintw(2,2,"%s","hello");
			break;
		case 'z':
			mvaddch(cy,cx,'*');
			break;
		case '.':
			//gen(60,60);
			break;
		/*
		case 'a':
			Region r(cx-1,cx+1,cy-1,cy+1);
			r.paint_region();
			break;
		case 's':
			Region q(cx-2,cx,cy-2,cy);
			q.paint_region();
			break;
		*/
		case 'd':
			Region a(cx-1,cx+1,cy-1,cy+1);
			Region b(cx-2,cx,cy-2,cy);
			a.combine(b).paint_region();	
			break;	
	}
	move(cy,cx);
}
	return 0;
}

