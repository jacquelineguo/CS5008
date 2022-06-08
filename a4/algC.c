#include <stdio.h>
#include <stdlib.h>
#include "algC.h"

int medianPivot(int* data, int low, int high) {
  int mid = low + (high - low)/2;
  if (data[high] < data[low]) Swap(data, low, high);
  if (data[mid] < data[low]) Swap(data, low, mid);
  if (data[high] < data[mid]) Swap(data, mid, high);
  return mid;
}
int PartitionC(int* data, int low, int high) {
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

void QuicksortC(int* data, int low, int high) {
  int median = medianPivot(data, low, high);
  Swap(data, low, median);
  if (low < high){
    int pivot_location = PartitionC(data, low, high);
    QuicksortC(data, low, pivot_location);
    QuicksortC(data, pivot_location+1, high);
  }
}
