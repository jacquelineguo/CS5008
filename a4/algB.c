#include <stdio.h>
#include <stdlib.h>
#include "algB.h"

void shuffle ( int arr[], int n ) {
  srand (42);
  int i;
  for (i = n-1; i > 0; i--) {
    int j = rand() % (i+1);
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
  }
}

void SwapB(int* array, int ind1, int ind2) {
  int tmp = array[ind1];
  array[ind1] = array[ind2];
  array[ind2] = tmp;
}


int PartitionB(int* data, int low, int high) {
  int pivot = data[low];
  int leftwall = low;
  int i;
  for (i = low + 1; i <= high; i++) {
    if (data[i] < pivot) {
      leftwall++;
      SwapB(data, i, leftwall);
    }
  }
  SwapB(data, low, leftwall);
  return leftwall;
}

void QuicksortB(int* data, int low, int high) {
  if (low < high) {
    int pivot_location = PartitionB(data, low, high);
    QuicksortB(data, low, pivot_location);
    QuicksortB(data, pivot_location+1, high);
  }
}
