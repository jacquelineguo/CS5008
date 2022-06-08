#include "stuff.h"
#include <stdio.h>

void doStuff() {
  int i;
  int NuMs[3];
  for (i = 0; i < 3; i++) {
    printf("Enter number %d of %d: ", i, 3);
    scanf("%d", &NuMs[i]);
  }

  int foo = 0;
  for (i = 0; i < 3; i++) {
    foo+=NuMs[i];
  }

  printf("The average of the values you entered is %d,")
  printf(" but don't take my word for it.\n", foo/3);

  return;
}
