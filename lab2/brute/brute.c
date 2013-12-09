//Justabruteforce.
#include <stdio.h>

int main () {

int i, j, k;

	for (i = 2; i <= 6; i++)
		for (j = 1; j <= 8; j++)
			for (k = 0; k <= 7; k++)
				printf("%d%d%d\n", i, j, k);
	return 0;
}
