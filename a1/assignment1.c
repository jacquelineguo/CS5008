#include <stdio.h>


// Problem 2 - Print Rectangles

/*
 * This function print a rectangle with the given width and height.
 */
void PrintRectangle(int width, int height) {
  int i;
  int j;
  for (i = 0; i < height; i++) {
    for (j = 0; j < width; j++) {
      if (i == 0 || i == (height -1)) {
        printf("^");
      }
      else {
        if (j == 0 || j == width - 1) {
          printf("^");
        }
        else {
          printf(" ");
        }
      }
    }
    printf("\n");
  }
}

/*
 * This function prints a fancy rectangle with width, height, a given symbol, and if it's filled.
 */
void PrintFancyRectangle(int width, int height, char* symbol, int fill) {
  int i;
  int j;
  for (i = 0; i < height; i++) {
    for (j = 0; j < width; j++) {
      if (fill == 1) {
        printf(symbol);
      }
      else {
        if (i == 0 || i == height - 1) {
          printf(symbol); 
        }
        else {
	  if (j == 0 || j == width - 1) {
	    printf(symbol);
	  }
	  else {
	    printf(" ");
	  }
	}
      }
    }
    printf("\n");
  }
}

int main () {
  // Problem 1 - Print Victory

  // Method 1
  printf("VICTORY!\n");
  printf("VICTORY!\n");
  printf("VICTORY!\n");
  printf("\n");

  // Method 2
  int i;
  for (i = 0; i <3; i++) {
    printf("VICTORY!\n");
  }
  printf("\n");

  // Method 3
  int n = 0;
  while (n < 3) {
    printf("VICTORY!\n");
    n++;
  }
  printf("\n");
  
  PrintRectangle(3, 4);
  printf("\n");

  PrintFancyRectangle(3, 4, "+", 0);
  printf("\n");

  PrintFancyRectangle(5, 5, "#", 1);
}
