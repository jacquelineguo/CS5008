#include <stdio.h>
#include "linkedlist.h"
#include <stdlib.h>

LinkedListPtr CreateLinkedList() {
  LinkedListPtr list = (LinkedListPtr)malloc(sizeof(struct ll_node));
  if (list == NULL) {
    return (LinkedListPtr) NULL;
  }

  list->num_elements = 0;
  list->head = NULL;
  list->tail = NULL;

  return list;
}

void DestroyLinkedList(LinkedListPtr list) {
  LinkedListNodePtr node = list->head;
  while (node != NULL) {
    LinkedListNodePtr toFree = node;
    node = node->next;
    DestroyLinkedListNode(toFree);
  }
  list->head = NULL;
  list->tail = NULL;
  list->num_elements = 0;
  free(list);
}

unsigned int NumElementsInLinkedList(LinkedListPtr list) {
  return list->num_elements;
}

int InsertLinkedList(LinkedListPtr list, int data) {
  LinkedListNodePtr new_node = CreateLinkedListNode(data);
  if (new_node == NULL) {
    return 1;
  }
  if (list->num_elements == 0) {
    list->head = new_node;
    list->tail = new_node;
    new_node->next = new_node->prev = NULL;
    list->num_elements = 1;
    return 0;
  }
  if (list->num_elements > 0) {
    LinkedListNodePtr temp = list->head;
    temp->prev = new_node;
    list->head = new_node;
    new_node->next = temp;
    new_node->prev = NULL;
    list->num_elements++;
    return 0;
  }
  return 0;
}

int AppendLinkedList(LinkedListPtr list, int data) {
  LinkedListNodePtr new_node = CreateLinkedListNode(data);
  if (new_node == NULL) {
    return 1;
  }
  if (list->num_elements == 0) {
    list->head = new_node;
    list->tail = new_node;
    new_node->next = new_node->prev = NULL;
    list->num_elements = 1;
    return 0;
  }
  if (list->num_elements > 0) {
    LinkedListNodePtr temp = list->tail;
    list->tail = new_node;
    temp->next = new_node;
    new_node->prev = temp;
    new_node->next = NULL;
    list->num_elements++;
  }
  return 0;
}

int PrintLinkedList(LinkedListPtr list) {
  if (list == NULL) {
    return 1;
  }
  LinkedListNodePtr node = list->head;

  while (node != NULL) {
    printf("%d", node->data);
    node = node->next;
    if (node != NULL) {
      printf("->");
    }
  }
  printf("\n");
  return 0;
}

LinkedListNode* CreateLinkedListNode(int data) {
  LinkedListNodePtr node = (LinkedListNodePtr)malloc(sizeof(struct ll_node));
  if (node == NULL) {
    return NULL;
  }
  node->data = data;
  node->next = NULL;
  node->prev = NULL;
  return node;
}

int DestroyLinkedListNode(LinkedListNode *node) {
  node->next = NULL;
  node->prev = NULL;
  free(node);
  return 0;
}

int RemoveLLElem(LinkedListPtr list, LinkedListNodePtr ptr) {
  if (ptr == NULL || list->num_elements == 0) {
    return 1;
  }
  LinkedListNodePtr tmp = list->head;
  int ptrInList = 0;
  while (tmp != NULL) {
    if (tmp == ptr) {
      ptrInList = 1;
      break;
    }
    tmp = tmp->next;
  }
  if (!ptrInList) {
    return 1;
  }

  if (ptr->prev == NULL) {
    if (ptr->next == NULL) {
      list->tail = NULL;
      list->head = NULL;
    } else {
      list->head = ptr->next;
      list->head->prev = NULL;
    }
  } else {
    if (ptr->next == NULL) {
      list->tail = ptr->prev;
      list->tail->next = NULL;
    } else {
      ptr->prev->next = ptr->next;
      ptr->next->prev = ptr->prev;
    }
  }
  list->num_elements--;
  return DestroyLinkedListNode(ptr);
}
