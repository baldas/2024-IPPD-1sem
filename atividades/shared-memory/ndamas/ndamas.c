// C program to solve N Queen Problem using backtracking
 
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

// variáveis globais
static int nSolutions = 0;    // total de soluções (saída)
static int TamTabuleiro;      // tamanho do tabuleiro (entrada)

 

/*
 * Checa se é permitido colocar a dama em uma determinada posição dada por
 * (row,col)
 * 
 * Return falso (0) se não é permitido e 1 caso contrário
 */
int isSafe(int *board, int row, int col)
{
  int i, j;

  // Checa a fileira (esquerda)
  for (i = 0; i < col; i++)
    if (board[i] == row)
      return 0;     // oops, já há uma dama lá
 
  // Checa a diagonal superior esquerda
  for (i = row-1, j = col-1; i >= 0 && j >= 0; i--, j--)
    if (board[j] == i)
      return 0;
 
  // Checa a diagonal inferior esquerda
  for (i = row+1, j = col-1; j >= 0 && i < TamTabuleiro; i++, j--)
    if (board[j] == i)
      return 0;
 
  return 1;
}

/*
 * Dado um tabuleiro e uma coluna específica, checa para cada
 * fileira onde é possível colocar uma dama
 */
void solveNQ(int *board, int col)
{

  /*
   * Passa por todas as fileiras da coluna atual
   */
  for (int i = 0; i < TamTabuleiro; i++) {
        
    // podemos colocar a dama na i-ésima fileira da coluna?
    if (isSafe(board, i, col)) {
  
      // Sim, então colocamos
      board[col] = i;
             
      // já passamos da última coluna e não tivemos problema -> solução encontrada
      if (col == TamTabuleiro-1) {
        nSolutions++;
      }
      else 
      // checa recursivamente a próxima coluna
        solveNQ(board, col + 1);
    }
  }
 
}
 

/*
 * Programa principal - entrada: N (tamanho do tabuleiro)
 */
int main(int argc, char *argv[])
{
  int i;
  int *board;
  struct timeval start, stop;
  
  if (argc <=1) {
    fprintf(stdout, "É necessário especificar o tamanho do tabuleiro\n");
    exit(-1);
  }
  TamTabuleiro = strtol(argv[1], NULL, 10);
  
  board = (int *)malloc(TamTabuleiro*sizeof(int));
//  memset(board,-1,TamTabuleiro*sizeof(int));

  gettimeofday(&start, NULL);
 
  // resolver o problema para o tamanho de tabuleiro requisitado, começando da
  // primeira coluna
  solveNQ(board,0);
  
  gettimeofday(&stop, NULL); 


  fprintf(stdout, "Número total de soluções: %d\n", nSolutions);
  
  double t = (((double)(stop.tv_sec)*1000.0  + (double)(stop.tv_usec / 1000.0)) - \
                   ((double)(start.tv_sec)*1000.0 + (double)(start.tv_usec / 1000.0)));

  fprintf(stdout, "Tempo decorrido = %g ms\n", t);
  
  free(board);
  return 0;
}
