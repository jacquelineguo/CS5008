#include <stdio.h>
#include <stdlib.h>

int G = 0;

int *
returnStatic(void)
{
  static int n;

  return &n;
}

void printPointerTarget1(const int *p)
{
  //*p = 5;
  //*((int *) p) = 5
  printf("%d\n", *p);
}

void
printPointerTarget(const int *p)
{
  //*p = 5;  /* produces compile-time error */
  *((int *) p) = 5;
  printf("%d\n", *p);
}

void doubler(int x) {
  x *= 2;
}

void doubler1(int *x) {
  *x *= 2;
}

int main(int argc, char **argv) {

  int y;
  y = 1;
  doubler(y);
  printf("%d\n", y);
  doubler1(&y);
  printf("%d\n", y);

  int *pointerToInt;
  double *pointerToDouble;
  char *pointerToChar;
  char *pointerToPointerToChar;

  static int s;
  int a;
  int *p;
  
  p = malloc(sizeof(int));

  printf("&G   = %p\n", (void *) &G);
  printf("&s   = %p\n", (void *) &s);
  printf("&a   = %p\n", (void *) &a);
  printf("&p   = %p\n", (void *) &p);
  printf("p    = %p\n", (void *) p);
  printf("main = %p\n", (void *) main);

  free(p);
  return 0;
    // (*p)++;  increment the value pointed to p
    // *p++;  increment p itself

  
}
