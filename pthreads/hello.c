
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


int thread_count; 

void *hellothread(void *id)
{
  int my_id = (int)id;

  fprintf(stdout, "Hello from thread %d (total of %d threads)\n",
                             my_id, thread_count);

  return NULL;
}



int main(int argc, char *argv[])
{
  pthread_t *thread_handles;

  thread_count = strtol(argv[1], NULL, 10);
  thread_handles = malloc(thread_count*sizeof(pthread_t));

  /* FORK Cria as threads informadas na linha de comando */
  int i;
  for (i=0; i<thread_count; i++) {
    if (pthread_create(&thread_handles[i], NULL, hellothread, (void *)i) != 0) {
      fprintf(stderr, "Nao consegui criar a thread\n");
      exit(-1);
    }
  }

  /* JOIN */
  for (i=0; i<thread_count; i++)
  {
    pthread_join(thread_handles[i], NULL);
  }

  free(thread_handles);

  return 0;
}
