#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifndef ALGB_H
#define ALGB_H

void shuffle ( int arr[], int n );

void SwapB(int* array, int ind1, int ind2);

int PartitionB(int* data, int low, int high);

void QuicksortB(int* data, int low, int high);

#endif
