#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>

//declare the functions before main
int draw_menu(void);
int draw_arena(int btn_pl1, int btn_pl2);
int wait_for(int time_delay);
void reset_terminal_mode();
void set_conio_terminal_mode();
int kbhit();
int nb_getch();
//termios
struct termios orig_termios;

int main(void) {
	
	//declare variables
	int row,col;
	initscr(); //init ncurses
	getmaxyx(stdscr, row, col); //get largest y & x coordinates
	//check color support & terminal size
	if (has_colors() == FALSE) {
		endwin();
		printf("No terminal color support\n");
		exit(1);
	} else if (row < 20 || col < 80) {
		endwin();
		printf("Too small terminal window, please restart with a larger window (x: %d, y: %d\n", col, row);
		exit(1);
	}
	
	start_color(); //enable color
	raw(); //disable line buffering
	keypad(stdscr, TRUE); //get F1, F2 etc...
	noecho(); //don't echo any input
	curs_set(0); //hide the cursor

	//call menu
	draw_menu();

	endwin();
	return 0;
}


//the draw_env function, this will draw the enviroment, and
//also have responsibility for getting user input for each enviroment
int draw_menu(void) {

	//declare variables
	const char welcome_pl1[]="Welcome to reactor, please input Player 1's button";	
	const char welcome_pl2[]="Now input Player 2's button";
	const char declared_btn[]="Is this correct? (y/n (c to cancel))";
	const char creator_txt[]="Written with <3 by willeponken";
	int row, col, btn_pl1, btn_pl2, pl_declared = 0;

	//insert max y & x coordinates to row & col
	getmaxyx(stdscr, row, col);

	while(pl_declared == 0) {

		clear();

		attron(A_BOLD); //bold text
		//get player 1's button
		mvprintw(row/2, (col-strlen(welcome_pl1))/2, "%s", welcome_pl1);
		mvprintw(1, (col-strlen(creator_txt))/2, "%s", creator_txt);
		btn_pl1 = getch();

		clear();
	
		//get player 2's button
		mvprintw(row/2, (col-strlen(welcome_pl2))/2, "%s", welcome_pl2);
		mvprintw(1, (col-strlen(creator_txt))/2, "%s", creator_txt);
		btn_pl2 = getch();

		clear();

		//print player buttons and ask if it's correct
		mvprintw(row/2, (col-strlen(declared_btn))/2, "%s", declared_btn);
		mvprintw(1, (col-strlen(creator_txt))/2, "%s", creator_txt);
		attroff(A_BOLD); //turn bold text off
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
				break;
			//cancel (c)
			case 99:
				endwin();
				exit(0);
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
	int row, col, i;
	//some beautiful ascii art (the button)
	const char *btn_ascii[]={"              .,-:;//;:=,", "          . :H@@@MM@M#H/.,+%;,", "       ,/X+ +M@@M@MM%=,-%HMMM@X/,", "     -+@MM; $M@@MH+-,;XMMMM@MMMM@+-", "    ;@M@@M- XM@X;. -+XXXXXHHH@M@M#@/.", "  ,%MM@@MH ,@%=             .---=-=:=,.", "  =@#@@@MX.,                -%HX$$%%%:;", " =-./@M@M$                   .;@MMMM@MM:", " X@/ -$MM/                    . +MM@@@M$", ",@M@H: :@:                    . =X#@@@@-", ",@@@MMX, .                    /H- ;@M@M=", ".H@@@@M@+,                    %MM+..%#$.", " /MMMM@MMH/.                  XM@MH; =;", "  /%+%$XHH@$=              , .H@@@@MX,", "   .=--------.           -%H.,@@@@@MX,", "   .%MM@@@HHHXX$$$%+- .:$MMX =M@@MM%.", "     =XMMM@MM@MM#H;,-+HMM@M+ /MMMX=", "       =%@M@M#@$-.=$@MM@@@M; %M%=", "         ,:+$+-,/H#MMMMMMM@= =,", "               =++%%%%+/:-."};
	//other texts
	const char win_txt[]="Winner!";
	const char loser_txt[]="Loser!";
	const char play_again_txt[]="Do you wish to play again? (y/n)";
	const char creator_txt[]="Written with <3 by willeponken";
	//get max y & x value
	getmaxyx(stdscr, row, col);

	while(1) {

		clear();

		//print ascii array
		for(i=0; i<20;i++){
			mvprintw((row-20)/2+i, (col-40)/2, "%s\n", btn_ascii[i]);
		}

		//print player names & buttons & creator text
		mvprintw(row-1, 1, "Player 1 (%d)", btn_pl1);
		mvprintw(row-1, col-(floor(log10(abs(btn_pl2))))-13, "Player 2 (%d)", btn_pl2);
		mvprintw(1, (col-strlen(creator_txt))/2, "%s", creator_txt);

		refresh();

		//time to play
		//declare random number
		srand(time(NULL)); //seed for rand
		int wait_until = time(0) + (rand() % 10) + 2;
		//declare other variables
		int painted_ascii = 0;

		set_conio_terminal_mode();

		while(!kbhit()) {
			if(wait_until <= time(0) && painted_ascii == 0) {
				for(i=0; i<20;i++){
					init_pair(1, COLOR_RED, COLOR_BLACK);
					attron(COLOR_PAIR(1));
					mvprintw((row-20)/2+i, (col-40)/2, "%s\n", btn_ascii[i]);
					attroff(COLOR_PAIR(1));
				}
			painted_ascii = 1;
			refresh();
			}
		}
		
		int btn_int, cont_game = 1, cont_ask = 1;
		
		while (cont_game == 1) {
		
			btn_int = nb_getch();

			if(btn_int == btn_pl1 && wait_until > time(0)) {
				mvprintw(row/2, (col-40-strlen(loser_txt))/4, "%s", loser_txt);
				mvprintw(row/2, col-(col-40)/4-(strlen(win_txt)/2), "%s", win_txt);
				cont_game = 0;
			} else if(btn_int == btn_pl2 && wait_until > time(0)) {
				mvprintw(row/2, (col-40-strlen(win_txt))/4, "%s", win_txt);
				mvprintw(row/2, col-(col-40)/4-(strlen(loser_txt)/2), "%s", loser_txt);
				cont_game = 0;
			} else if(btn_int == btn_pl1 && wait_until <= time(0)) {
				mvprintw(row/2, (col-40-strlen(win_txt))/4, "%s", win_txt);
				mvprintw(row/2, col-(col-40)/4-(strlen(loser_txt)/2), "%s", loser_txt);
				cont_game = 0;
			} else if(btn_int == btn_pl2 && wait_until <= time(0)) {
				mvprintw(row/2, (col-40-strlen(loser_txt))/4, "%s", loser_txt);
				mvprintw(row/2, col-(col-40)/4-(strlen(win_txt)/2), "%s", win_txt);
				cont_game = 0;
			}
		}

		mvprintw(row-1, (col-strlen(play_again_txt))/2, "%s", play_again_txt);
		
		refresh();

		while (cont_ask == 1) {

			btn_int = nb_getch();
				
				//n (exit)
				if (btn_int == 110) {
					endwin();
					exit(0);
				//y (replay)
				} else if (btn_int == 121)
					cont_ask = 0;

		}
	}
	return 0;
}


//everything below, from "reset_terminal_mode" to  "getch" 
//is for creating a non-blocking I/O to be able to handle both
//the keyboard input and also the timer (using termios)
void reset_terminal_mode() {
	tcsetattr(0, TCSANOW, &orig_termios);
	system("reset"); //quick bugfix because the pipe isn't closed properly
}

void set_conio_terminal_mode() {
	struct termios new_termios;

	//make a copy of orig_termios
	tcgetattr(0, &orig_termios);
	memcpy(&new_termios, &orig_termios, sizeof(new_termios));
	
	//close pipe at exit
	atexit(reset_terminal_mode);
	cfmakeraw(&new_termios);
	tcsetattr(0, TCSANOW, &new_termios);
}

int kbhit() {
	struct timeval tv = {0L, 0L};
	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(0, &fds);
	return select(1, &fds, NULL, NULL, &tv);
}

int nb_getch() {
	int r;
	unsigned char c;
	if((r = read(0, &c, sizeof(c))) < 0) {
		return r;
	} else {
		return c;
	}
}
