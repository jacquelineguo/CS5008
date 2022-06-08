#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sort.h"
#include "linkedlist.h"


int main() {
  int min_val = 1;
  int max_val = 100;
  srand(time(0));
  int value = (min_val + (rand() % (max_val - min_val + 1)));
  
  LinkedListPtr list = CreateLinkedList();
  unsigned int num_elements = 50;
  LinkedListNodePtr node = CreateLinkedListNode(value);
  list->head = node;
  list->tail = node;
  list->num_elements = 1;
  unsigned int i;
  for (i = 0; i < num_elements - 1; i++) {
    int value = (min_val + (rand() % (max_val - min_val + 1)));
    AppendLinkedList(list, value);
  }

  PrintLinkedList(list);

  Sort(list);

  PrintLinkedList(list);
  DestroyLinkedList(list);
  return 0;
}
