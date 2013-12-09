//Maybe the smallest bruteforce ever?

#include <stdio.h>

main ()
  for (i = 2; i <= 6; i++)
    for (j = 1; j <= 8; j++)
      for (k = 0; k <= 7; k++)
        printf("%d%d%d", i, j, k);
