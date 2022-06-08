#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "a2.h"


// YOUR CODE GOES HERE

// Print the string <first> <middle> <last>
//  e.g. if first = "Ben", middle = "Ivan",
//  and last = "Bitdiddle, then print:
//  "Ben Ivan Bitdiddle".
//
//  If the middle name is NULL, then print:
//  "Ben Bitdiddle"
//
//  name: a pointer to a Name
void Big(Name *name) {
  printf("%s ", name->first);
  if (name->middle != NULL) {
    printf("%s ", name->middle);
  }
  printf("%s", name->last);
}

// Print the string <last>, <first>
//  e.g. if first = "Ben", middle = "Ivan",
//  and last = "Bitdiddle, then print:
//  "Bitdiddle, Ben".
//
// name: a pointer to a Name
void Last(Name *name) {
  printf("%s", name->last);
  printf(", ");
  printf("%s", name->first);
}

// Print the string <first> <last>
//  e.g. if first = "Ben", middle = "Ivan",
//  and last = "Bitdiddle, then print:
//  "Ben Bitdiddle".
//
// name: a pointer to a Name
void Reg(Name *name) {
  printf("%s ", name->first);
  printf("%s", name->last);
}

// Print the string <first> <middle-initial>. <last>
//  e.g. if first = "Ben", middle = "Ivan",
//  and last = "Bitdiddle, then print:
//  "Ben I. Bitdiddle".
//
// If middle name is NULL, print:
// "Ben Bitdiddle"
//
// name: a pointer to a Name
void Mid(Name *name) {
  printf("%s ", name->first);
  if (name->middle != NULL) {
    printf("%c", name->middle[0]);
    printf("%s ", ".");
  }
  printf("%s", name->last);
}

// Print the first name only.
//  e.g. if first = "Ben", middle = "Ivan",
//  and last = "Bitdiddle, then print:
//  "Ben".
//
// name: a pointer to a Name
void Small(Name *name){
  printf("%s", name->first);
}

// Given a format char, print the given
// name in the format specified by char.
// The mapping is shown below:
// B -> 'big' format
// L -> 'last' format
// R -> 'reg' format
// M -> 'mid' format
// S -> 'small' format
//
// name: a pointer to a Name
// format: a char indicating the format to use (case doesn't matter)
void FormatName(Name *name, char format){
  switch(toupper(format)){
  case 'B': 
    Big(name);
    break;
  case 'L': 
    Last(name);
    break;
  case 'R': 
    Reg(name);
    break;
  case 'M':
    Mid(name);
    break;
  case 'S':
    Small(name);
    break;
  }
}

// Given a name, a format and a destination array,
// put the properly formatted name in the destination
// array, not printing anything on the screen.
//
// The mapping is shown below:
// B -> 'big' format
// L -> 'last' format
// R -> 'reg' format
// M -> 'mid' format
// S -> 'small' format
//
// name: a pointer to a Name
// format: a char indicating the format to use (case doesn't matter)
// dest: a pointer to an array that is guaranteed to be big enough
// to hold the formatted name
void FillName(Name *name, char format, char *dest) {
  switch (toupper(format)) {
  case 'B':
    strcat(dest, name->first);
    strcat(dest, " ");
    if (name->middle != NULL) {
      strcat(dest, name->middle);
      strcat(dest, " ");
    }
    strcat(dest, name->last);
    break;
  case 'L':
    strcat(dest, name->last);
    strcat(dest, " ");
    strcat(dest, name->first);
    break;
  case 'R':
    strcat(dest, name->first);
    strcat(dest, " ");
    strcat(dest, name->last);
    break;
  case 'M':
    strcat(dest, name->first);
    strcat(dest, " ");
    if (name->middle != NULL) {
      size_t cur_len = strlen(dest);
      dest[cur_len] = name->middle[0];
      strcat(dest, ". ");
    }
    strcat(dest, name->last);
    break;
  case 'S':
    strcat(dest, name->first);
    break;
  }
}
