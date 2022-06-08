#include <stdio.h>

#include "linkedlist.h"

void Sort(LinkedListPtr list) {
  if (list->num_elements < 2) {
    return;
  }
  int swapped;
  do {
    swapped = 0;
    LinkedListNodePtr node = list->head;
    while (node->next != NULL) {
      if (node->data > node->next->data) {
        int tmp = node->data;
        node->data = node->next->data;
        node->next->data = tmp;
        swapped = 1;
      }
      node = node->next;
    }
  }while(swapped);
}
