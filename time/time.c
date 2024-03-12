#include <stdio.h>
#include <sys/time.h>


int main()
{

  struct timeval start, end;

  // Começo da minha medição
   gettimeofday(&start, NULL);
  
  /// carga de trabalho
   volatile int x = 0;
   for (x=0; x<1000000000; x++);

  // Fim da minha medição
   gettimeofday(&end, NULL);

  int duration;
  duration = (end.tv_sec*1000 + end.tv_usec/1000) - (start.tv_sec*1000 + start.tv_usec/1000);
  printf("Tempo = %d ms\n", duration);

  return 0;
}
