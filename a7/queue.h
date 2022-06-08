#ifndef QUEUE_H
#define QUEUE_H
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"


typedef struct queue Queue;

struct queue {
  TreeNode** queue;
  int front;
  int rear;
  int length;
};

Queue* CreateQueue(int n);

void Enqueue(Queue* q, TreeNode* node);

TreeNode* Dequeue(Queue* q);

void DestroyQueue(Queue* q);

#endif
