#include <stdio.h>
#include <stdlib.h>
#include "algD.h"

int cut_off = 120;

void InsertionSort(int* data, int low, int high) {
  int i;
  for (i = high; i > low; i--) {
    if (data[i] < data[i-1]) Swap(data, i-1, i);
  }
  for (i = low+2; i<=high; i++) {
    int j = i;
    int value = data[i];
    while (value < data[j-1]) {
      data[j] = data[j-1];
      j--;
    }
    data[j] = value;
  }
}

void QuicksortD(int* data, int low, int high) {
  if (high-low <= cut_off) {
    InsertionSort(data, low, high);
    return;
  }
  if (low < high) {
    int pivot_location = Partition(data, low, high);
    QuicksortD(data, low, pivot_location);
    QuicksortD(data, pivot_location+1, high);
  }
}
