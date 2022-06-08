#include <stdio.h>
#include <stdlib.h>

int main() {

  int stringLength = 7;

  //Fixed (*stringOnHeap * stringLength) to (sizeof(char) * stringLength)
  char *stringOnHeap = (char *) malloc((sizeof(char) * stringLength) + 1);

  stringOnHeap[0] = 'e';
  stringOnHeap[1] = 'x';
  stringOnHeap[2] = 'a';
  stringOnHeap[3] = 'm';
  stringOnHeap[4] = 'p';
  stringOnHeap[5] = 'l';
  stringOnHeap[6] = 'e';
  stringOnHeap[7] = '\0';

  printf("%s\n", stringOnHeap);

  //Fixed free memory, added free(stringOnHeap)
  free(stringOnHeap);
  return 0;
}
