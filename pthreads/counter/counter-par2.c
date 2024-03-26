#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#include <pthread.h>

volatile unsigned long counter=0;

unsigned long limit = 0xFFFFFFFD;

pthread_mutex_t mutex;

int thread_count; 

void *counterthread(void *arg) {
  int myid = (int)arg;

  unsigned long block = limit/thread_count;
  
  unsigned long my_i = myid*block;

  unsigned int i;
  for (i=my_i; i<my_i+block; i++) {
    pthread_mutex_lock(&mutex);
    counter++;
    pthread_mutex_unlock(&mutex);
  }

//  printf("Returning from thread %d\n", myid);

  return NULL;
}

int main(int argc, char *argv[])
{
  struct timeval start, stop;
  pthread_t *thread_handles;
  
  thread_count = strtol(argv[1], NULL, 10);
  thread_handles = malloc(thread_count*sizeof(pthread_t));

 pthread_mutex_init(&mutex, NULL); 

  unsigned long i;

  gettimeofday(&start, NULL);

  // FORK
  for (i=0; i<thread_count; i++) {
    if (pthread_create(&thread_handles[i], NULL, counterthread, (void *)i) != 0) {
      fprintf(stderr, "Nao consegui criar a thread\n");
      exit(-1);
    }
  }
  
  /* JOIN */
  for (i=0; i<thread_count; i++)
  {
    pthread_join(thread_handles[i], NULL);
  }
  

  gettimeofday(&stop, NULL);

  printf("counter = %lx\n", counter);
  double temp = \
               (((double)(stop.tv_sec)*1000.0 + (double)(stop.tv_usec/1000.0)) - \
                ((double)(start.tv_sec)*1000.0 + (double)(start.tv_usec/1000.0)));
  printf("Time elapsed = %g ms\n", temp);

  pthread_mutex_destroy(&mutex);

  return 0;
}
