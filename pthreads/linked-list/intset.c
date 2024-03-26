#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>

#include "linkedlist.h"


/* shared variable - pointer to the shared linked list */
list_node_t *linked_list;



/* main structure used to communicate parameters to a thread */
typedef struct thr_parms {
  long int id;            /* thread id, starting from 0 */
  long int operations;    /* number of total operations to be performed */
  long int set_size;      /* number of elements initially in the set */
  long int upd_rate;      /* update rate (0-100) */

  unsigned short seed[3]; /* used for safe random number generation */

  /* used for statistics */
  long int num_search;    /* number of searches performed and ... */
  long int num_found;     /* ... number of elements found */
  long int num_adds;      /* number of additions */
  long int num_removes;   /* number of deletes */
} thr_parms_t;


/*
 * Initialize seed buffer used for random number generation.
 * Each thread will have its own (initialized by main thread).
 */
void seed_init(unsigned short *seed)
{
  seed[0] = (unsigned short)rand();
  seed[1] = (unsigned short)rand();
  seed[2] = (unsigned short)rand();
}


/*
 * Populates the set with random numbers.
 */
void intset_init(long int size, unsigned short *seed)
{
  int i;
  for (i=0; i<size; i++)
    list_add(linked_list, (int)(erand48(seed)*size*2));
}


/*
 * Each thread executes this code.
 * 
 * Basically, each thread stays in a loop according to the number of
 * operations and: 
 *   1) randomly chooses the operation (according to the update rate specified
 *   by the used)
 *   2) perform the operation
 *
 * Statistics for the operations are stored in the thread's structure.
 *
 */
void *intset_exercise(void *arg)
{
  thr_parms_t *parms = (thr_parms_t *)arg;
  fprintf(stdout, "[%ld]: %ld\n", parms->id, parms->operations);

  /* control variables */
  int add_or_remove;  /* 0 -> remove; 1 -> add */
  int update_chance;  /* change (0-100) that we will update the list */
  int value;          /* value to be inserted/removed/searched */
  int last_value;     /* last value added - we used it for the next removal */

  add_or_remove = 1; /* addition */
  while (parms->operations--)
  {
    /* See if we need to update */
    update_chance = (int)(erand48(parms->seed)*100);
    /* Draw a number */
    value = (int)(erand48(parms->seed)*parms->set_size*2);

    if (update_chance < parms->upd_rate) {
      if (add_or_remove) { 
        list_add(linked_list, value);
          
        last_value = value;  /* remember the last value */
        parms->num_adds++;
      }
      else {
        list_remove(linked_list, last_value);
        parms->num_removes++;
      }
      /* if current operation is addition, next will be removal (and
       * vice-versa) */
      add_or_remove ^= 1; 
    }
    else {
      parms->num_found += list_contain(linked_list, value);
      parms->num_search++;
    }
  }

  return NULL;
}


/*
 * Input parameters:
 *    <#ops> <set_size> <update_rate> <num_threads>
 *
*/
int main(int argc, char *argv[])
{
  int i;
  pthread_t *thread_handles;
  struct timeval start, end;
  double elapsed_time;

  long int num_operations;
  long int set_size;
  long int num_threads;
  long int update_rate;
  
  unsigned short main_seed[3]; 


  if (argc <= 4) {
    fprintf(stderr, "Invalid parameter number: use <numop> <setsize> <update> <#threads>\n");
    exit(-1);
  }

  num_operations = strtol(argv[1], NULL, 10);
  set_size = strtol(argv[2], NULL, 10);
  update_rate = strtol(argv[3], NULL, 10);
  num_threads = strtol(argv[4], NULL, 10);

  // TODO: validate the input

  
  thread_handles = malloc(num_threads*sizeof(pthread_t));


  fprintf(stdout, "Number of threads = %ld\n\n", num_threads);

  srand(0);
  seed_init(main_seed);
  list_init(&linked_list);
  intset_init(set_size, main_seed);


  /* print the initial contents of the list and size */
  fprintf(stdout, "=============== Initial state ===============\n");
  //list_print(linked_list);
  fprintf(stdout, "list size = %zu\n", list_size(linked_list));
  fprintf(stdout, "=============================================\n");

  /* allocate and initialize the contents of the structure passed to 
   * each thread */
  thr_parms_t *thread_parms;
  thread_parms = malloc(num_threads*sizeof(thr_parms_t));

  for (i=0; i<num_threads; i++) {
    thread_parms[i].id = i;
    thread_parms[i].operations = num_operations/num_threads;
    thread_parms[i].set_size = set_size;
    thread_parms[i].upd_rate = update_rate;
    seed_init(thread_parms[i].seed);
    thread_parms[i].num_search = 0;
    thread_parms[i].num_found = 0;
    thread_parms[i].num_adds = 0;
    thread_parms[i].num_removes = 0;
  }


  gettimeofday(&start, NULL);

  for (i=0; i<num_threads; i++) {
    if (pthread_create(&thread_handles[i], NULL, intset_exercise, (void *) (&thread_parms[i]))) {
      fprintf(stderr, "Error spawning thread\n");
      exit(-1);
    }
  }

  long int num_search = 0;
  long int num_found = 0;
  long int num_adds = 0;
  long int num_removes = 0;

  for (i=0; i<num_threads; i++) {
    pthread_join(thread_handles[i], NULL);
    num_search += thread_parms[i].num_search;
    num_found += thread_parms[i].num_found;
    num_adds += thread_parms[i].num_adds;
    num_removes += thread_parms[i].num_removes;
  }
  
  gettimeofday(&end, NULL);
  
  /* print the contents of the list afterwards */
  fprintf(stdout, "=============== Final state ===============\n");
//  list_print(linked_list);
  fprintf(stdout, "list size = %zu\n", list_size(linked_list));
  fprintf(stdout, "=============================================\n\n");
  fprintf(stdout, "Operations: [add, remove, search] = %ld, %ld, %ld\n", 
      num_adds, num_removes, num_search);
  fprintf(stdout, "Number of elements found = %ld\n", num_found);

  elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;

  fprintf(stdout, "Elapsed time: %g s\n", elapsed_time); 
  fprintf(stdout, "Throughput: %g ops/s\n", (num_adds+num_removes+num_search)/elapsed_time);


  free(thread_handles);
  
  return 0;
}
