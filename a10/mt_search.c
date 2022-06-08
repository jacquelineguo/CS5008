#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

// ****************************
// This code is provided as an *optional* framework to use to
// write your multi-threaded search code for Assignment 10.
//
// Feel free to change anything you want to in this.
// ****************************


// ===================================================
// Global Variables
// ===================================================

#define MAX_NUM_RESULTS 100
int num_lines;
int section_size;
int num_threads;

// Array of numbers to search
int* data;

// Number to be found
int target;

int finishedRead = 0;

// Array of indices of target number
int results[MAX_NUM_RESULTS];
int numThreads[MAX_NUM_RESULTS];
// Number of results we have so far
int num_results = 0;


// Used for synchronization.
// I encourage you to rename this something more meaningful.
pthread_mutex_t lock;
sem_t semaphore;


// ===================================================
// Functions
// ===================================================

// The function that each thread will run
// to look for the target value in the array.
// The argument provided is a pointer to the array
// where this thread should start looking for the target.
// (This can be either the index OR the address. Your choice.)
// Each thread will look at a max of section_size elements.
void* DoSearch(void* start_address) {
  while (1) {
    sleep(1);  // try to yield to other threads
    sem_wait(&semaphore);  // wait for the semaphore
    // If it's this threads turn, then print it's ID
    if (finishedRead) {
      break;
    }
    // If it's not our time, release the semaphore and keep waiting
    sem_post(&semaphore);
  }
  int MyThreadNum = *(int *)(&start_address);
  section_size = num_lines/num_threads+1;
  int start = MyThreadNum * section_size;
  int end = ((MyThreadNum+1) * section_size) - 1;
  if (end >= num_lines) {
    end = num_lines -1;
  }
  int i;
  pthread_mutex_lock(&lock);
  for (i = start; i <= end; i++) {
    if (target == data[i]) {
      results[num_results] = i+1;
      numThreads[num_results] = MyThreadNum;
      num_results++;
    }
  }
  pthread_mutex_unlock(&lock);


  sem_post(&semaphore);
  // pthread_exit(NULL);
  return NULL;
}

// Creates all the threads and starts them running.
// Makes sure the thread IDs are stored in the global threads array.
void MakeThreads(pthread_t* threads) {
  int i;
  int ret;
  long MyThreadNum = 0;
  for (i = 0; i < num_threads; i++) {
    ret = pthread_create(&threads[i], NULL, DoSearch, (void*) MyThreadNum);
    MyThreadNum++;
  }
}

// Opens the file called filename.
// Reads line by line, adding each number to the
// global data array.
void ReadFile(char* filename, int num_lines) {
  int i = 0;
  FILE *file;
  file = fopen(filename, "r");
  for (i = 0; i <= num_lines; i++) {
    fscanf(file, "%d", &data[i]);
  }
  // for (i=0; i<=num_results; i++) {
  //    printf("%d was found on line %d", data[i], i+1);
  // }
  finishedRead = 1;
  fclose(file);
}

// Prints out the results, stored in the
// global "results" array.
void PrintResults() {
  int i = 0;
  for (i = 0; i < num_results; i++) {
    printf("Thread %d: %d was found on line %d\n",
           "numThreads[i]+1, target, results[i]");
  }
}


int main(int num_args, char* args[]) {
  // START HERE
  // Read in the arguments and populate global variables.
  char* filename = args[1];
  target = atoi(args[2]);
  num_threads = atoi(args[3]);
  num_lines = atoi(args[4]);

  data = malloc(sizeof(int)*100);
  sem_init(&semaphore, 0, 1);
  pthread_mutex_init(&lock, NULL);
  // Create the threads
  pthread_t threads[num_threads];
  MakeThreads(threads);

  // Read the file
  ReadFile(filename, num_lines);

  // Wait for threads to finish doing their job
  int i;
  for (i = 0; i < num_threads; i++) {
    pthread_join(threads[i], NULL);
  }
  // Print out the results
  PrintResults();

  // Clean up everything!
  // Free everything you malloc'd.
  // Don't forget to destroy the semaphore and mutex, which
  // get malloc'd when you create them.

  pthread_mutex_destroy(&lock);
  sem_destroy(&semaphore);
  free(data);
  // pthread_exit(NULL);
}
