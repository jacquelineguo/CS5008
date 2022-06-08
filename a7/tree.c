#include "tree.h"

TreeNode* CreateTreeNode(char* path, char* name, int level) {
  TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
  newNode->path = path;
  newNode->name = name;

  newNode->children = NULL;
  newNode->parent = NULL;
  newNode->next_siblings = NULL;
  newNode->prev_siblings = NULL;
  newNode->level = level;
  return newNode;
}

void AddChild(TreeNode* root, char* path, char* name) {
  int newLevel = root->level + 1;
  TreeNode *newNode = CreateTreeNode(path, name, newLevel);
  newNode->parent = root;
  if (root->children == NULL) {
    root->children = newNode;
  } else {
    newNode->next_siblings = root->children;
    root->children->prev_siblings = newNode;
    root->children = newNode;
  }
}

void DestroyTreeNode(TreeNode* node) {
  if (node == NULL) {
    return;
  }
  DestroyTreeNode(node->children);
  DestroyTreeNode(node->next_siblings);

  free(node);
}
