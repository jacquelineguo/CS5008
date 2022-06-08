#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "LinkedList_easy.h"


LinkedListNode* CreateLinkedListNode(char *data) {
  LinkedListNodePtr node = (LinkedListNodePtr) malloc(sizeof(LinkedListNode));
  if (node == NULL) {
    return NULL;
  }
  node->payload = data;
  return node;
}

int DestroyLinkedListNode(LinkedListNode *node) {
  while(node != NULL) {
    LinkedListNodePtr cur = node;
    node = node->next;
    free(cur);
  }
}

//int RemoveLLElem(LinkedList list, LinkedListNodePtr ptr);

LinkedList CreateLinkedList() {
  LinkedList ll = (LinkedList) malloc(sizeof(LinkedListHead));
  if (ll == NULL) {
    return NULL;
  }
  return ll;
}
int DestroyLinkedList(LinkedList list) {
  DestroyLinkedListNode(list->head);
  free(list);
}

unsigned int NumElementsInLinkedList(LinkedList list) {
  return list->num_elements;
}

int InsertLinkedList(LinkedList list, Payload_t payload) {
  LinkedListNodePtr node = (LinkedListNodePtr) malloc(sizeof(LinkedListNode));
  if (node == NULL) {
    return 1;
  }
  node->payload = payload;
  //printf("%s\n", (*payload)->value);
  if (list->num_elements == 0) {
    node->next = node->prev = NULL;
    list->head = node;
    list->tail = node;
    return 0;
  }
  node->prev = NULL;
  node->next = list->head;
  list->head->prev = node;
  list->head = node;
  list->num_elements++;
  return 0;
}
int PopLinkedList(LinkedList list, char** dataPtr) {
  if (list->num_elements == 0) {
    return 1;
  }
  LinkedListNodePtr curr = list->head;
  *dataPtr = curr->payload;
  list->head = list->head->next;
  if (list->head == NULL) {
    list->tail = NULL;
  } else {
    list->head->prev = NULL;
  }
  list->num_elements--;
  free(curr);
  return 0;
}

void SortLinkedList(LinkedList list, unsigned int ascending) {
  if (list->num_elements < 2) {
    return;
  }

  int swapped;
  do {
    LinkedListNodePtr curr;
    swapped = 0;
    curr = list->head;
    while (curr->next != NULL) {
      int compare_res = strcmp(curr->payload, curr->next->payload);
      if (ascending) {
        compare_res *= -1;
      }
      if (compare_res < 0) {
        char* tmp;
        tmp = curr->payload;
        curr->payload = curr->next->payload;
        curr->next->payload = tmp;
        swapped = 1;
      }
      curr = curr->next;
    }
  }while(swapped);
}

LLIter CreateLLIter(LinkedList list) {
  if (NumElementsInLinkedList(list) == 0) {
    return NULL;
  }
  LLIter li = (LLIter) malloc(sizeof(LLIterSt));
  if (li == NULL) {
    return NULL;
  }
  li->list = list;
  li->cur_node = list->head;
  return li;
}

int LLIterHasNext(LLIter iter) {
  if (iter->cur_node->next == NULL) {
    return 0;
  }
  return 1;
}

//int LLIterHasPrev(LLIter iter);

int LLIterNext(LLIter iter) {
  if (iter == NULL || iter->cur_node == NULL) {
    return 1;
  }
  if(iter->cur_node->next != NULL) {
    iter->cur_node = iter->cur_node->next;
    return 0;
  }
  return 1;
}

//int LLIterPrev(LLIter iter);

int DestroyLLIter(LLIter iter) {
  free(iter);
  return 0;
}

int LLIterGetPayload(LLIter iter, Payload_t* payload) {
  if (iter == NULL || iter->cur_node == NULL) {
    return 1;
  }
  *payload = iter->cur_node->payload;
  printf("%s\n", iter->cur_node->payload);
  return 0;
}

int LLIterDelete(LLIter iter) {
  if (iter->list->num_elements == 0) {
    return 1;
  }
  LinkedListNodePtr curr = iter->cur_node;
  iter->list->num_elements--;
  if (iter->list->num_elements == 0) {
    iter->cur_node = NULL;
    iter->list->head = iter->list->tail = NULL;
    free(curr->payload);
    free(curr);
    return 1;
  }
  iter->cur_node =(curr->next != NULL) ? curr->next : curr->prev;
  if (curr->prev == NULL) {
    if (curr->next != NULL) {
      curr->next->prev = NULL;
      iter->list->head = curr->next;
    }
  } else if (curr->next == NULL) {
    if (curr->prev != NULL) {
      curr->prev->next = NULL;
      iter->list->tail = curr->prev;
    }
  } else {
    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;
  }
  free(curr->payload);
  free(curr);
  return 0;
}

//int LLIterInsertBefore(LLIter iter, char* payload);
