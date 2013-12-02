#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

	int i = 0;
//check for arguments:
	if (argc < 2) {

	printf("Welcome to mod!\nThere was no arguments specified.\nPlease re-run mod with arguments.\n");

	} else {

		for (i=0; i<argc; i++) {
			//atoi argv[] to int
			char *num_char = argv[i];
			int num_int = atoi(num_char);

			//arg literals
			//-c [start] [end], ex: "-c 1 100" will count all numbers from 1 to 100.
			char *c_arg = "-c";
			//
			char *m_arg = "

			if(strcmp(num_char, c_arg) == 0) {
				int get_arg = i;
				int num_start = atoi(argv[++get_arg]);
				int num_end = atoi(argv[++get_arg]);
				printf("start: %d end: %d int: %d\n", num_start, num_end, num_int);
			}

/*
			if(num_int%15==0){
				printf("%s: %d%%15=%d", argv[i], num_int, num_int%15);
			} else if (num_int%3==0) {
				printf("%s: %d%%3=%d", argv[i], num_int, num_int%3);
			} else if (num_int%5==0) {
				printf("%s: %d%%5=%d", argv[i], num_int, num_int%5);
			} else {
				printf("%s: <0", argv[i]);
			}

			printf("\n");*/
		}
	}

	return 0;
}
