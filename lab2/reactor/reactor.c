#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

//declare the functions before main
int draw_menu(void);
int draw_arena(int btn_pl1, int btn_pl2);

int main(void) {
	
	//init ncurses
	initscr();
	//disable line buffering
	raw();
	//get F1, F2 etc...
	keypad(stdscr, TRUE);
	//don't echo any input
	noecho();

	//call menu
	draw_menu();

	//refresh screen
	refresh();
	endwin();

	return 0;
}


//the draw_env function, this will draw the enviroment, and
//also have responsibility for getting user input for each enviroment
int draw_menu(void) {

	int row,col;

	int btn_pl1, btn_pl2;

	getmaxyx(stdscr, row, col);

	int pl_declared = 0;

	while(pl_declared == 0) {

		//declare variables
		char welcome_pl1[]="Welcome to reactor, please input Player 1's button";	
		char welcome_pl2[]="Now input Player 2's button";
		char declared_btn[]="Is this correct? (y/n (c to cancel))";

		clear();

		//bold text
		attron(A_BOLD);

		//get player 1's button
		mvprintw(row/2, (col-strlen(welcome_pl1))/2, "%s", welcome_pl1);
		btn_pl1 = getch();

		clear();
	
		//get player 2's button
		mvprintw(row/2, (col-strlen(welcome_pl2))/2, "%s", welcome_pl2);
		btn_pl2 = getch();

		clear();

		//print player buttons and ask if it's correct
		mvprintw(row/2, (col-strlen(declared_btn))/2, "%s", declared_btn);
		//turn bold text off
		attroff(A_BOLD);
		//print declared player buttons, subtracting with 23 because
		//that is the number of letters between btn_pl1 & btn_pl2
		mvprintw(row/2+1, (col-((floor(log10(abs(btn_pl1))))+(floor(log10(abs(btn_pl2)))))-23)/2, "Player 1: %d & Player 2: %d", btn_pl1, btn_pl2);

		//ask if correct, if yes; end while loop, if cancel end program & if any other
		//button (no etc.) then keep looping
		switch(getch()) {
			//yes (y)
			case 121:
				pl_declared = 1;
				draw_arena(btn_pl1, btn_pl2);
				return 0;
				break;
			//cancel (c)
			case 99:
				endwin();
				return 0;
				break;
			//other button (n etc.)
			default:
				break;
		}
	}
	return 0;
}


int draw_arena(int btn_pl1, int btn_pl2) {

	//declare variables
	int row,col;
	//get max y & x value
	getmaxyx(stdscr, row, col);

	clear();



	return 0;
}
