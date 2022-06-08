#include <stdio.h>
#include <stdlib.h>

typedef struct node Node;

struct node {
  char* data;
  Node* leftChild;
  Node* rightChild;
  Node* parent;
  int visited;
};


struct binaryTree {
  Node* root;
};

typedef struct binaryTree BinaryTree;

#define kStackSize 50
int stack_head = 0;

Node* stack[50];


Node* queue[50];
int front = 0;
int rear = 0;


Node* CreateNode(char* data) {
  Node* newNode = (Node*)malloc(sizeof(Node));
  newNode->data = data;

  newNode->leftChild = NULL;
  newNode->rightChild = NULL;
  newNode->parent = NULL;
  newNode->visited = 0;
  return newNode;
}

void DestroyNode(Node *node) {
  if (node == NULL) return;

  DestroyNode(node->leftChild);
  DestroyNode(node->rightChild);
  //  destroyNode(node->parent);

  // Destroy node
  free(node);
}

// 1 to add the node as a left child;
// 0 to add the node as a right child.
void AddChild(Node *node, Node* child, int leftChild) {
  if (leftChild) {
    node->leftChild = child;
  } else {
    node->rightChild = child;
  }
  child->parent = node;
}

void Push(Node* node) {
  if (node == NULL) return;
  if (stack_head < kStackSize) {
    stack[stack_head++] = node;
  }
  //  return s; // No more call by value, so not returning.
}

Node* Pop() {
  if (stack_head > 0) {
    return stack[--stack_head];
  }
  return NULL;  // sentinel value
}

void EnQueue(Node* node) {
  if (node == NULL) return;
  queue[rear] = node;
  rear++;
}

Node* DeQueue() {
  Node* first = queue[front];
  front++;
  return first;
}

void PrintTreeDFSIter(Node* root) {
  Push(root);
  Node* curr = Pop();

  while (curr != NULL) {
    printf("%s\n", curr->data);
    Push(curr->rightChild);
    Push(curr->leftChild);
    curr = Pop();
  }
}

void PrintTreeBFS(Node* root) {
  Node* curr = root;

  while (curr != NULL) {
    printf("%s\n", curr->data);
    EnQueue(curr->leftChild);
    EnQueue(curr->rightChild);
    curr = DeQueue();
  }
}

void PrintTree(Node* root) {
  if (root == NULL) {
    return;
  }

  printf("%s\n", root->data);
  PrintTree(root->leftChild);
  PrintTree(root->rightChild);
}


int main() {
  Node* root = CreateNode("root");
  Node* n1 = CreateNode("1");
  Node* n2 = CreateNode("2");
  Node* n3 = CreateNode("3");
  Node* n4 = CreateNode("4");
  Node* n5 = CreateNode("5");
  Node* n6 = CreateNode("6");

  AddChild(root, n1, 1);
  AddChild(root, n2, 0);

  AddChild(n1, n3, 1);
  AddChild(n1, n4, 0);

  AddChild(n4, n5, 1);
  AddChild(n4, n6, 0);

  PrintTree(root);

  printf("\n");

  PrintTreeDFSIter(root);

  printf("\n");

  PrintTreeBFS(root);
  return 0;
}
