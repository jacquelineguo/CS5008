#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifndef QUICKSORT_H
#define QUICKSORT_H


void Swap(int* array, int ind1, int ind2);

int Partition(int* data, int low, int high);

void Quicksort(int* data, int low, int high);

void PrintArray(int* array, int num_elems);

int CheckArray(int* array, int num_elems);

#endif
