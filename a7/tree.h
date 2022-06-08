#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifndef _TREE_H_
#define _TREE_H_

typedef struct tree_node TreeNode;

struct tree_node {
  char* path;
  char* name;
  TreeNode* children;
  TreeNode* parent;
  TreeNode* next_siblings;
  TreeNode* prev_siblings;
  int level;
};

TreeNode* CreateTreeNode(char* path, char* name, int level);

void AddChild(TreeNode* root, char* path, char* name);

void DestroyTreeNode(TreeNode* node);

#endif
