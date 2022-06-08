#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"


typedef struct stack Stack;

struct stack {
  TreeNode** stack;
  int head;
  int size;
};

Stack* CreateStack(int n);

void Push(Stack* s, TreeNode* node);

TreeNode* Pop(Stack* s);

void DestroyStack(Stack* s);

#endif
