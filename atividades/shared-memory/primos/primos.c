/*
 * Programa que computa a quantidade de números primos dado uma faixa de
 * valores.
 *
 * Entrada:    
 *      . primeiro número
 *      . último número
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>


/*
 * Dado um número 'num', retorna se é primo ou não. O algoritmo faz algumas
 * otimizações, como ignorar os pares e fazer a checagem apenas até a raiz
 * quadrada de 'num'.
 */
int ehPrimo(unsigned long num)
{
  unsigned long i;

  // 0 e 1 -> não primo, retorna
  if (num == 0 || num == 1) return 0;
  // 2 e 3, já retorna positivamente
  else if (num == 2 || num == 3) return 1;

  // se for múltiplo de 2 ou 3, já retorna negativamente
  if (num % 2 == 0 || num % 3 == 0) return 0;

  // passe pelos número checando se alguns deles divide 'num' (processo é
  // feito apenas até a raiz quadrada de 'num')
  for (i=5; i*i<=num; i+=2)
    if ((num % i) == 0) return 0;

  return 1;
}
 
/* 
 * Programa principal
 * Parâmetros: <primeiro_numero> <segundo_numero>
 */
int main(int argc, char *argv[])
{
  unsigned long i;
  unsigned long primeiro, ultimo;
  int nthreads;
  struct timeval start, stop;
  
  /* Linha de comando */
  if (argc <=2) {
    fprintf(stdout, "Entrada inválida: use %s <primeiro> <último>\n", argv[0]);
    exit(-1);
  }
  primeiro = strtol(argv[1], NULL, 10);
  ultimo = strtol(argv[2], NULL, 10);
 
  // número total de primos encontrado
  int nPrimes = 0;

  // região principal
  gettimeofday(&start, NULL);

  // para cada número da faixa dada, checa quantos são primos
  for (i=primeiro; i<=ultimo; i++)
    if (ehPrimo(i)) nPrimes++;
  
  gettimeofday(&stop, NULL); 


  fprintf(stderr, "Número de primos: %d\n", nPrimes);
  
  double t = (((double)(stop.tv_sec)*1000.0  + (double)(stop.tv_usec / 1000.0)) - \
                   ((double)(start.tv_sec)*1000.0 + (double)(start.tv_usec / 1000.0)));

  fprintf(stdout, "Tempo decorrido = %g ms\n", t);
  
  return 0;
}
 
