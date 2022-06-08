#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Print an array contains integer

void print(int arr[], int size) {
  int i;
  for (i = 0; i < size; i++) {
    printf("%d\n", arr[i]);
  }
}

// Replace the number in an array which is larger than the ceiling number

void replace(int arr[], int size, int ceiling) {
  int i;
  if (size > 0) {
    for (i = 0; i < size; i++) {
      if (arr[i] > ceiling) {
        arr[i] = ceiling;
      }
      else {
        arr[i] = arr[i];
      }
    }
  }
    print(arr, size);
}

// Swap the middle and the last integer in an array

void swap_mid_back(int arr[], int size) {
  if (size > 0) {
    int div = 2;
    int middle = size / div;
    int temp = arr[middle];
    arr[middle] = arr[size - 1];
    arr[size - 1] = temp;
    print(arr, size);
  }
}

// Replace the digits in a string with '*'

void replace_digit(char input[], int size) {
  int i = 0;
  while (input[i] != '\0') {
    if (isdigit(input[i])) {
      input[i] = '*';
      }
    i++;
  }
  printf("%s\n", input);
}

int main() {
  // Declaing
  int arr[] = {2, 3, 4, 6, 9};
  int size = 5;
  int num = 3;
  replace(arr, size, num);
  int arr1[] = {2, 5, 6, 8, 9};
  swap_mid_back(arr1, size);
  char line[] = "The part failed 58% of the time";
  replace_digit(line, strlen(line));
  return 0;
}
