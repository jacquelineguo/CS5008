#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <locale.h>
#include "queue.h"
#include "stack.h"


void PrintTree(TreeNode* node) {
  int level = node->level;
  while (level > 1) {
    int i;
    TreeNode* tmp = node;
    for (i = 1; i < level; i++) {
      tmp = tmp->parent;
    }
    if (tmp->prev_siblings == NULL) {
      printf("    ");
    } else {
      printf("│   ");
    }
    level--;
  }

  if (level == 1) {
    if (node->prev_siblings != NULL) {
      printf("├── ");
    } else {
      printf("└── ");
    }
  }
  printf("%s\n", node->name);
}

int main() {
  char* dir;
  char* rootName;
  dir = ".";
  rootName = ".";
  struct stat s;
  Queue* q = CreateQueue(100);
  TreeNode* root = CreateTreeNode(dir, rootName, 0);
  Enqueue(q, root);

  int level = 1;
  while (q->rear != q->front) {
    TreeNode* newNode = Dequeue(q);
    dir = newNode->path;
    struct dirent **namelist;
    int num_files;
    num_files = scandir(dir, &namelist, 0, alphasort);
    if (num_files < 0) {
      perror("scandir");
      printf("dir: %s\n", dir);
      return;
    } else {
      int i = 0;
      while (i < num_files) {
        if (namelist[i]->d_name[0] == '.') {
          free(namelist[i]);
          i++;
          continue;
        }
        char *directory;
        char *dname;
        int length = strlen(dir) + strlen(namelist[i]->d_name);
        dname = (char*) malloc(((strlen(namelist[i]->d_name) + \
                                3)*sizeof(char)));
        directory = (char*) malloc(((length + 3)*sizeof(char)));
        if (directory == NULL) {
          printf("Couldn't malloc for filecrawler.directory\n");
          return;
        }
        snprintf(directory, length + 3, "%s/%s", \
                 dir, namelist[i]->d_name);
        snprintf(dname, strlen(namelist[i]->d_name)\
                 + 3, "%s", namelist[i]->d_name);
        AddChild(newNode, directory, dname);
        if (0 == stat(directory, &s)) {
          if (S_ISDIR(s.st_mode)) {
            Enqueue(q, newNode->children);
          }
       } else {
          printf("no stat; %s\n", directory);
        }
        free(namelist[i]);
        i++;
      }
    }
    free(namelist);
    level++;
  }


  Stack* stack = CreateStack(100);
  Push(stack, root);

  while (stack->head > 0) {
    TreeNode* node = Pop(stack);
    if (node == NULL) {
      break;
    }
    PrintTree(node);
    if (node->name != ".") {
      free(node->path);
      free(node->name);
    }
    TreeNode* childNode = node->children;
    while (childNode != NULL) {
      Push(stack, childNode);
      childNode = childNode->next_siblings;
    }
  }
  DestroyStack(stack);
  DestroyQueue(q);
  DestroyTreeNode(root);
}
