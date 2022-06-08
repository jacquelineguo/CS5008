#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

#define N 5
#define THINKING 2
#define HUNGRY 1
#define EATING 0

// state[i] is the state of philosopher I
int state[N];
int phil[N] = { 0, 1, 2, 3, 4 };
int forks[N];

int times_eaten[N] = {0};

sem_t pile_semaphore; 
sem_t fork_semaphores[N]; 

void eat(int phnum) {
  state[phnum] = EATING;
  times_eaten[phnum]++;
  printf("Philosopher %d is eating! \n", phnum);
  sleep(5);
}

void take_forks(int phnum) {
  state[phnum] = HUNGRY;

  printf("Philosopher %d is Hungry\n", phnum);
  int left_fork = (phnum - 1) % N;

  printf("Philosopher %d is waiting for hte left fork...\n", phnum);
  //  sem_wait(&fork_semaphores[left_fork]);
  sem_wait(&pile_semaphore);
  printf("Philosopher %d has the left fork.\n", phnum);  
  /*
  while (1) {
  if (forks[left_fork] == -1) {
      printf("Philsopher %d is taking %d fork (left)\n", phnum, left_fork);
      forks[left_fork] = phnum;
      break;
    } else {
      printf("Someone else has this fork!\n");
    }
  sleep(1);
  }*/
  
  int right_fork = phnum;
  printf("Philosopher %d is waiting for hte right fork...\n", phnum);
  //  sem_wait(&fork_semaphores[right_fork]);
  sem_wait(&pile_semaphore);
  printf("Philosopher %d has the right fork\n", phnum);
  
  /*
  while (1) {
  if (forks[right_fork] == -1) {
      printf("Philsopher %d is taking %d fork (right)\n", phnum, right_fork);
      forks[right_fork] = phnum;
      break;
    } else {
      printf("Someone else has this fork!\n");
    }

    sleep(1);
  }
  */

}

void put_forks(int phnum) {
  printf("Philosopher %d putting left fork %d\n",
         phnum, (phnum - 1) % N);
  //  forks[phnum-1 % N] = -1;
  int left_fork = (phnum - 1) % N;
  //  sem_post(&fork_semaphores[left_fork]);
  sem_post(&pile_semaphore);
  printf("Philosopher %d putting right fork %d\n",
         phnum, (phnum) % N);
  
  //  forks[phnum + 1 %N] = -1;
  //  sem_post(&fork_semaphores[phnum]);
  sem_post(&pile_semaphore);
  
  printf("Philosopher %d is thinking\n", phnum);
  state[phnum] = THINKING;
}

void* philosopher(void* num) {
  while (1) {
    int* i = num;
    sleep(1);
    take_forks(*i);
    sleep(0);
    eat(*i);
    sleep(0);
    put_forks(*i);
    printf("Philosopher %d has eaten %d times\n", *i, times_eaten[*i]);
  }
}

int main() {
  int i;
  pthread_t thread_id[N];

  for (i = 0; i < N; i++) {
    sem_init(&fork_semaphores[i], 0, 1);
    forks[i] = -1;
  }

  sem_init(&pile_semaphore, 0, N);
  
  for (i = 0; i < N; i++) {
    // create philosopher threads
    pthread_create(&thread_id[i], NULL,
                   philosopher, &phil[i]);

    printf("Philosopher %d is thinking\n", i + 1);
  }

  for (i = 0; i < N; i++) {
    pthread_join(thread_id[i], NULL);
  }
}
