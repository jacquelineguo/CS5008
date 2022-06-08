#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int num_args, char**args) {
  if (num_args != 2) {
    // TODO(adrienne or student): Print how to use this or what good input is
    printf("Need more or less args\n");
    exit(0);
  }

  const char* delim = " ";

  const int kBufferSize = 150;
  char buffer[kBufferSize];

  while (1) {
    printf("Enter your command > ");
    // stdin, stdout, stderr
    fgets(buffer, kBufferSize, stdin);
    printf("input was: %s\n", buffer);

    char* rest = buffer;

    char* token = strtok_r(buffer, delim, &rest);

    while (token != NULL) {
      printf("%s\n", token);
      token = strtok_r(NULL, delim, &rest);
    }

  }
  return 0;
}
