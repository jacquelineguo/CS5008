#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "Hashtable_easy.h"

uint64_t Hash(unsigned char* str) {
  return FNVHashInt64(FNVHash64(str, strlen(str)));
}

void sort(char* string) {
  char temp;
  int i, j;
  int n = strlen(string);
  for (i = 0; i < n-1; i++) {
    for (j = i+1; j < n; j++) {
      if (string[i] > string[j]) {
        temp = string[i];
        string[i] = string[j];
        string[j] = temp;
      }
    }
  }
}

void ValueFreeFn(void* value);


int main() {
  int stopped = 10;
  FILE *file;
  int bufferLength = 255;
  char buffer[bufferLength];
  Hashtable ht;
  HTKeyValue kv, old_kv;
  ht = CreateHashtable(4000000);
  
  file = fopen("words.txt", "r");
  if (file) {
    while(fgets(buffer, bufferLength, file)) {
      char* string = (char *)malloc(strlen(buffer) + 1);
      size_t i;
      for (i=0; i<strlen(buffer); i++) {
        string[i] = buffer[i];
      }
      string[i] = '\0';
      kv.value = string;
      sort(string);
      kv.key = Hash(string);
      PutInHashtable(ht, kv, &old_kv);
      //printf("%s\n", string);
      if (stopped-- == 0) {
        break;
      }
    }
    fclose(file);
  }
  PrintHashtable(ht);
  
  DestroyHashtable(ht, &ValueFreeFn);
  return 0;
}

void ValueFreeFn(void* value) {
  free(value);
}
