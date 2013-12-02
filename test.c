#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

	int i = 0;
	if (argc < 2) {
	printf("Welcome to mod!\nThere was no arguments specified.\nPlease re-run mod with arguments.\n");
	} else {

	for (i=0; i<argc; i++) {

		char *num_char = argv[i];
		int num_int = atoi(num_char);

		if(num_int%15==0){
			printf("%s: %d%%15=%d", argv[i], num_int, num_int%15);
		} else if (num_int%3==0) {
			printf("%s: %d%%3=%d", argv[i], num_int, num_int%3);
		} else if (num_int%5==0) {
			printf("%s: %d%%5=%d", argv[i], num_int, num_int%5);
		} else {
			printf("%s: <0", argv[i]);
		}

		printf("\n");
	}}

	return 0;
}
