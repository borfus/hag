#include <ncurses.h>
#include <panel.h>
#include <string.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include "level_generator_1.h"
#include "gui.h"

/* Put all the windows */
void init_wins(WINDOW **wins, struct winsize w) //int n)
{	
	int x, y, i, width, height;
	char label[80];

	//HEIGHT WIDTH Y X (order of inputs for newwin)
	//storing the height and width of the terminal
	int NLINES = w.ws_row;
	int NCOLS = w.ws_col;

	//top left	
	wins[0] = newwin(NLINES*.75, NCOLS/2, 0, 0);
	sprintf(label, "Window Number %d", 1);
	win_show(wins[0], label, 1);
	
	//bottom 
	wins[1] = newwin(NLINES*.25, NCOLS, NLINES*.75, 0);
	sprintf(label, "%i %i", (int)(NLINES*.75)*15, 0);
	win_show(wins[1], label, 2);
	
	//top right
	wins[2] = newwin(NLINES*.75, NCOLS/2, 0, NCOLS*.5);
	sprintf(label, "%i %f", 0, ((int)NCOLS*.5*15));
	win_show(wins[2], label, 3);
}

/* Show the window with a border and a label */
void win_show(WINDOW *win, char *label, int label_color)
{	int startx, starty, height, width;

	getbegyx(win, starty, startx);
	getmaxyx(win, height, width);

	box(win, 0, 0);
	mvwaddch(win, 2, 0, ACS_LTEE); 
	mvwaddch(win, 2, width - 1, ACS_RTEE); 
	
}

void print_in_window(WINDOW *win, int starty, int startx, int width, char *string, chtype color, bool mid)
{	int length, x, y;
	float temp;

	if(win == NULL)
		win = stdscr;
	getyx(win, y, x);
	if(startx != 0)
		x = startx;
	if(starty != 0)
		y = starty;
	if(width == 0)
		width = 80;

	length = strlen(string);
	if (mid) {
		temp = (width - length)/ 2;
	} else {
		temp = 0;
		startx = 1;
	}
	x = startx + (int)temp;
	wattron(win, color);
	mvwprintw(win, y, x, "%s", string);
	wattroff(win, color);
	refresh();
}
