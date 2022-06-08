#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <math.h>
#include <signal.h>
#define MAXARGS 5
#define MAXLINE 80

char* commands[3] = {"cd", "help", "game"};


void* cd(char* input) {
  int result;
  result = chdir(input);
  if (result == 0) {
    printf("Changed directory to: %s\n", input);
  } else {
    printf("Unable to find the directory\n");
  }
}

void* help() {
  printf("\nexit: Exit the shell.\n");
  printf("\nhelp: Display information about builtin commands.\n");
  printf("\ncd: Change the current directory to provided directory\n");
  printf("\ngame: Generate a dancing DONUT for 5 seconds.\n");
}

void* game() {
  float A = 0, B = 0;
  float i, j;
  int k;
  float z[1760];
  char b[1760];
  printf("\x1b[2J");
  time_t endwait = time(NULL) + 5;
  while (time(NULL) < endwait) {
    memset(b, 32, 1760);
    memset(z, 0, 7040);
    for (j = 0; j < 6.28; j += 0.07) {
      for (i = 0; i < 6.28; i += 0.02) {
        float c = sin(i);
        float d = cos(j);
        float e = sin(A);
        float f = sin(j);
        float g = cos(A);
        float h = d + 2;
        float D = 1 / (c * h * e + f * g + 5);
        float l = cos(i);
        float m = cos(B);
        float n = sin(B);
        float t = c * h * g - f * e;
        int x = 40 + 30 * D * (l * h * m - t * n);
        int y= 12 + 15 * D * (l * h * n + t * m);
        int o = x + 80 * y;
        int N = 8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n);
        if (22 > y && y > 0 && x > 0 && 80 > x && D > z[o]) {
          z[o] = D;
          b[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
        }
      }
    }
    printf("\x1b[H");
    for (k = 0; k < 1761; k++) {
      putchar(k % 80 ? b[k] : 10);
      A += 0.00004;
      B += 0.00002;
    }
    usleep(30000);
  }
}

void* kexit() {
  printf("\nexiting...\n");
  exit(0);
}

void* (*command_functions[3])() = {cd, help, game};

/***
 **  Wrapper of fork(). Checks for fork errors, quits on error.
 **/
pid_t Fork(void) {
  pid_t pid;
  if ((pid = fork()) < 0) {
    fprintf(stderr, "%s: %s\n", "fork error", strerror(errno));
    exit(0);
  }
  return pid;
}

/***
 **  Wrapper of fgets. Checks and quits on Unix error.
 **/
char* Fgets(char *ptr, int n, FILE *stream) {
  char *rptr;
  if (((rptr = fgets(ptr, n, stream)) == NULL) && ferror(stream)) {
    fprintf(stderr, "%s\n", "fgets error");
    exit(0);
  }
  return rptr;
}

// Is the command one built into the shell?
// That is, that the *shell* has implemented?
// If so, execute it here
int builtin_command(char** argv) {
  int i = 0;
  // Loop through
  while (i < 3) {
    int res = strcmp(commands[i], argv[0]);
    if (res == 0) {
      // call the right function.
      if (strcmp("cd", argv[0]) == 0) {
        (*command_functions[i])(argv[1]);  // some argument
      } else {
        (*command_functions[i])();
      }
      return 1;
    }
    i++;
  }
  return 0;
}



void eval(char *cmdline, char** argv) {
  pid_t pid; /* Process id */

  if (argv[0] == NULL)
    return; /* Ignore empty lines */

  if (strcmp("exit", argv[0]) == 0) {
    kexit();
  }
  pid = Fork();
  if (pid == 0) {
    if (!builtin_command(argv)) {
      // Check that the command/program exists in Unix (ie /bin/) OR (see below)
      // Create a child process
      // Run the program/command (execve...)--
      // what is the result of exec if the command is bogus?

      int res = execve(argv[0], argv, NULL);
      // see run_ls.c for an example
      if (res < 0) {
        // print error message
        printf("Command not found--Did you mean something else?\n");
        exit(0);
      }
    } else {
      // What do we do if it *IS* a command built into the shell?
      exit(0);
    }
  } else {
    wait(NULL);
  }
  return;
}

int main() {
  char cmdline[MAXLINE]; /* command line buffer */
  while (1) {
    // Print command prompt
    printf("k-sea-shell> ");
    // Read input from user
    Fgets(cmdline, MAXLINE, stdin);
    // If we get the eof, quit the program/shell
    if (feof(stdin))
      exit(0);

    char *argv[MAXARGS]; /* Argument list execve() */
    char buf[MAXLINE]; /* Holds modified command line */
    char* token;
    strcpy(buf, cmdline);
    // Split buf into args
    int i = 0;
    char *p =  strtok(buf, " \n");
    while (p != NULL) {
      token = malloc(strlen(p)*sizeof(char));
      token = strcpy(token, p);
      argv[i++] = token;
      p = strtok(NULL, " \n");
    }
    argv[i] = NULL;
    // Otherwise, evaluate the input and execute.
    eval(cmdline, argv);
    int j = 0;
    for (j = 0; j < MAXARGS; j++) {
      if (argv[j] == NULL) {
        break;
      }
      free(argv[j]);
    }
    if (argv) {
      free(argv);
    }
  }
}
