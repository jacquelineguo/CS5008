#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "quicksort.h"

void Swap(int* array, int ind1, int ind2) {
  int tmp = array[ind1];
  array[ind1] = array[ind2];
  array[ind2] = tmp;
}


int Partition(int* data, int low, int high) {
  int pivot = data[low];
  int leftwall = low;
  int i;
  for (i = low + 1; i <= high; i++) {
    if (data[i] < pivot) {
      leftwall++;
      Swap(data, i, leftwall); 
    }
  }
  Swap(data, low, leftwall);
  return leftwall;
}

void Quicksort(int* data, int low, int high) {
  if (low < high) {
    int pivot_location = Partition(data, low, high);
    Quicksort(data, low, pivot_location);
    Quicksort(data, pivot_location+1, high);
  }
}

void PrintArray(int* array, int num_elems) {
  int i;
  printf("[");
  for (i = 0; i < num_elems; i++) {
    printf("%d ", array[i]);
  }
  printf("]\n");
}

int CheckArray(int* array, int num_elems) {
  int i;
  for (i = 1; i < num_elems; i++) {
    if (array[i] < array[i - 1]) {
      printf("NOT SORTED!!!\n");
      return 0;
    }
  }
  printf("SORTED!!\n");
  return 1;
}

