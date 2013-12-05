/*

This project is just a test for how you can
get variables for the program using the
variables from the main function. (argc & 
argv)

Using the arguments declared upon start, you
are able to modulize between a number of 
defined numbers, and also declare which
number to modulize with.

Many improvements could be done, one could be
using functions instead of just having one
gigantic main. And also make everything more 
fool proof.

Written by William Wennerström (willeponken).
You are free to do what ever you like with it,
althought I would like if you add my name if
the code in any way helped you, but thats
not necessary.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {

	int i = 0;
	int num_start = 0;
	int num_end = 0;
	int num_mod = 0;
	int num_is = 0;
	int num_isnot = 0;

	//check for arguments:
	if (argc < 2) {

		printf("\nWelcome to mod!\nA litte small useless modulizer \nwritten with <3 in C by willeponken.\nThere was no arguments specified.\nPlease re-run mod with arguments.\n\nAvailable arguments:\n-c [start] [end], ex: '-c 1 100' will count all numbers from 1 to 100.\n-m [mod], ex: '-m 4' will modulize with 4.\n\n");

	} else {

		printf("\nWelcome to mod!\nA litte small useless modulizer \nwritten with <3 in C by willeponken.\n");

		for (i=0; i<argc; i++) {
			//atoi argv[] to int
			char *num_char = argv[i];
			//for debugging: int num_int = atoi(num_char);

			//arg literals
			//-c [start] [end], ex: "-c 1 100" will count all numbers from 1 to 100.
			char *c_arg = "-c";
			//-m [mod], ex: "-m 4" will modulize with 4.
			char *m_arg = "-m";

			//find arg in string, then get variables
			//c_arg:
			if(strcmp(num_char, c_arg) == 0) {
				int get_arg = i;

				num_start = atoi(argv[++get_arg]);
				num_end = atoi(argv[++get_arg]);
				//for debugging: printf("start: %d end: %d int: %d\n", num_start, num_end, num_int);
			}

			//m_arg:
			if(strcmp(num_char, m_arg) == 0) {
				int get_arg = i;
				num_mod = atoi(argv[++get_arg]);
				//for debugging: printf("mod: %d\n", num_mod);
			}
		}

		printf("\nValues specified: \nStart: %d\nEnd: %d\nMod: %d\n\n", num_start, num_end, num_mod);

		//make sure were not about to divide with zero
		if(num_mod != 0 && num_start <= num_end) {
			printf("Will now test specified values:\n");
			
				//for each number between num_start & num_end (with num_start & num_end)
				for(i=num_start; i<=num_end; i++) {
					
				//check if dividable
				if(i%num_mod == 0) {
					printf("%d IS dividable with %d\n", i, num_mod);
					num_is++;
				} else {
					printf("%d IS NOT dividable with %d\n", i, num_mod);
					num_isnot++;
				}
			}
		} else if(num_mod == 0) {
			printf("Nope, nope and NOPE, mod != 0!\n");
		} else if(num_start > num_end) {
			printf("Please make sure the start number is less than the end number.\n");
		}

		printf("\nThere was %d not dividable and %d dividable.\nDone, goodbye and have a good day.\n", num_isnot, num_is);

	}

	return 0;
}
