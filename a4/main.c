#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>
#include "quicksort.h"
#include "algB.h"
#include "algC.h"
#include "algD.h"


int main(int argc, char **argv) {
  if (argc < 2) {
    printf("please input algorithms to run\n");
    exit(0);
  }
  if (strcmp(argv[1], "-all") == 0) {
    argv[1] = "-abcd";
  }
  char num_algs = strlen(argv[1]) - 1;
  if (num_algs < 1) {
    printf("please input more than one algorithm\n");
    exit(0);
  }
  
  const int size = 6;
  int num_elems[6] = {16, 64, 128, 512, 1024, 2048};

  printf("             16      64     128     512    1024    2048\n");
  printf("-------------------------------------------------------\n");
  int x;
  for (x = 1; x < num_algs+1; x++){
    char algo = toupper(argv[1][x]);
    printf("Alg %c: ", algo);
    int i, j;
    for (i = 0; i < size; i++) {
      int* integers = (int*)malloc(sizeof(int) * num_elems[i]);
      srand(42);
      for (j = 0; j < num_elems[i]; j++) {
        integers[j] = (rand() % 90) + 10;
      }
      
      struct timeval begin, end;
      
      gettimeofday(&begin, NULL);
      if (algo == 'A') {
        //PrintArray(integers, 12);
        Quicksort(integers, 0, num_elems[i]-1);
        //CheckArray(integers, num_elems[i]);
      }else if (algo == 'B') {
        //        PrintArray(integers, 12);
        shuffle(integers, num_elems[i]-1);
        QuicksortB(integers, 0, num_elems[i]-1);
        //CheckArray(integers, num_elems[i]-1);
      }else if (algo == 'C') {
        //        PrintArray(integers, 12);
        QuicksortC(integers, 0, num_elems[i]-1);
        //CheckArray(integers, num_elems[i]);
      }else if (algo == 'D') {
        //PrintArray(integers, 12);
        QuicksortD(integers, 0, num_elems[i]-1);
        //        CheckArray(integers, num_elems[i]);
      }
      gettimeofday(&end, NULL);
      long micros = (end.tv_usec - begin.tv_usec);
      
      printf("     %d", micros);
      free(integers);
    }
    printf("\n");
  }
}
