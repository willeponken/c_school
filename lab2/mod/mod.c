/*
 Copyright 2013 William Wennerström

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//initalizing functions before main
void get_arguments(int argc, char *argv[]);
void modulizer(int start, int end, int mod[], int mod_c);

int main(int argc, char *argv[]) {

	//check argument count (argc)
	if (argc < 2) {
		printf("\nWelcome to mod!\nA litte small useless modulizer\nwritten with <3 in C by willeponken.\nThere was no arguments specified.\nPlease re-run mod with arguments.\n\nAvailable arguments:\n-c [start] [end], ex: '-c 1 100' will count all numbers from 1 to 100.\n-m [mod], ex: '-m 4 5' will modulize with 4 and 5.\n\n");
	} else {
		printf("\nWelcome to mod!\nA litte small useless modulizer\nwritten with <3 in C by willeponken.\n");
		
		//call get_arguments to fetch from argc & argv, which in turn calls the modulizer
		get_arguments(argc, argv);
	}

	return 0;

}

void get_arguments(int argc, char *argv[]) {

	//declare variables
	int index, num_start, num_end, num_mod_c = 0, num_mod[argc];
	char *c_arg = "-c", *m_arg = "-m", *num_char;

	//iterate through the whole argv array
	for (index = 0; index<argc; index++) {

		//set num_char to currect argument variable in the argv array
		num_char = argv[index];
		int get_arg = index;

		//if argument is "-c"
		if(strcmp(num_char, c_arg) == 0) {

			//check the arguments so they are not wrongly written
			if (argv[++get_arg] != c_arg && argv[get_arg] != m_arg) {

				//add start and end number to num_start & num_end
				num_start = atoi(argv[get_arg]);
				num_end = atoi(argv[++get_arg]);
			} 
		//if argument is "-m"
		} else if (strcmp(num_char, m_arg) == 0) {

				//iterate through argv from current index
				for (get_arg = index; get_arg < argc; get_arg++) {

					if (strcmp(argv[get_arg], c_arg) != 0 && strcmp(argv[get_arg], m_arg) != 0) {
						num_mod[num_mod_c] = atoi(argv[get_arg]);
						num_mod_c++;	

					//else, if there is a c_arg, end for loop
					} else if (strcmp(argv[get_arg], c_arg) == 0)
						break;

				}

			}
	}

	modulizer(num_start, num_end, num_mod, num_mod_c);
	return;

}

void modulizer(int start, int end, int mod[], int mod_c) {

	//declare variables
	int num_index, mod_index, num_is = 0, num_isnot = 0;

	//tell the user about start & end values
	printf("\nStart: %d\nEnd: %d\n", start, end);

	for (mod_index = 0; mod_index < mod_c; mod_index++) {

		//tell the user which mod value we are using
		printf("\nUsing the mod value %d:\n", mod[mod_index]);

		//make sure were not about to divide with zero & also that start isn't larger than end
		if (mod[mod_index] != 0 && start <= end) {

			//check each number between start & end
			for (num_index = start; num_index <= end; num_index++) {

				//is num_index divible with mod[mod_index]?
				if (num_index % mod[mod_index] == 0) {

					//tell the user that it is dividable
					printf("%d IS dividable with %d\n", num_index, mod[mod_index]);
					num_is++;

				} else {

					//tell the user that it was not dividable
					printf("%d IS NOT dividable with %d\n", num_index, mod[mod_index]);
					num_isnot++;

				}

			}
		} else if (mod[mod_index] == 0) {

			//tell the user that you cannot divide by zero (kinda)
			printf("'Black holes are where God divided by zero.'\n  — Albert Eintein\n");

		} else if (start > end) {

			//tell the user that the start number is higher than the end number
			printf("Please make sure the start number is less than the end number.\n");

		}
	}

	printf("\nThere was %d not dividable and %d dividable.\nDone, goodbye and have a good day.\n", num_isnot, num_is);
	
	return;
}
