#include "stack.h"


Stack* CreateStack(int n) {
  Stack* s = (struct stack*) malloc(sizeof(struct stack));
  s->head = 0;
  s->size = n;
  s->stack = (TreeNode**) malloc(n*sizeof(TreeNode*));
  return s;
}


void Push(Stack* s, TreeNode* node) {
  if (node == NULL) return;
  if (s->head < s->size) {
    s->stack[s->head++] = node;
  }
}

TreeNode* Pop(Stack* s) {
  if (s->head > 0) {
    return s->stack[--s->head];
  }
  return NULL;
}

void DestroyStack(Stack* s) {
  free(s->stack);
  free(s);
}
