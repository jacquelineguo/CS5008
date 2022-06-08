#include "queue.h"

Queue* CreateQueue(int n) {
  Queue* queue = (struct queue*) malloc(sizeof(struct queue));
  queue->front = 0;
  queue->rear = 0;
  queue->length = n;
  queue->queue = (TreeNode**) malloc(n*sizeof(TreeNode*));
  return queue;
}

void Enqueue(Queue* q, TreeNode* node) {
  if (node == NULL) return;
  q->queue[q->rear] = node;
  q->rear++;
}

TreeNode* Dequeue(Queue* q) {
  TreeNode* first = q->queue[q->front];
  q->front = (q->front+1) % q->length;
  return first;
}

void DestroyQueue(Queue* q) {
  free(q->queue);
  free(q);
}
