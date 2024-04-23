/*
 * The Game of Life
 *
 * a cell is born, if it has exactly three neighbours 
 * a cell dies of loneliness, if it has less than two neighbours 
 * a cell dies of overcrowding, if it has more than three neighbours 
 * a cell survives to the next generation, if it does not die of loneliness 
 * or overcrowding 
 *
 * In this version, a 2D array of ints is used.  A 1 cell is on, a 0 cell is off.
 * The game plays a number of steps (given by the input), printing to the screen each time.  'x' printed
 * means on, space means off.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef unsigned char cell_t; 

// Alloca um tabuleiro quadrado de tamanho 'size'
cell_t **allocate_board(int size) 
{
	cell_t ** board = (cell_t **) malloc(sizeof(cell_t*)*size);
	int	i;
	for (i=0; i<size; i++)
		board[i] = (cell_t *) malloc(sizeof(cell_t)*size);
	return board;
}

void free_board(cell_t **board, int size) 
{
  int i;
  for (i=0; i<size; i++)
    free(board[i]);
	free(board);
}

// retorna o número de células 'vivas' adjacentes à célula (i,j)
int adjacent_to(cell_t **board, int size, int i, int j) 
{
	int	k, l, count=0;
	
	int sk = (i>0) ? i-1 : i;
	int ek = (i+1 < size) ? i+1 : i;
	int sl = (j>0) ? j-1 : j;
  int el = (j+1 < size) ? j+1 : j;

	for (k=sk; k<=ek; k++)
		for (l=sl; l<=el; l++)
			count+=board[k][l];
	count-=board[i][j];
	
	return count;
}

// percore as células e aplica as regras do jogo
void play(cell_t **board, cell_t **newboard, int size) 
{
	int	i, j, a;
	/* para cada célula do tabuleiro original (board), constroi outro com as regras
   * aplicadas (newboard) */
#pragma omp parallel for private(a,j)
	for (i=0; i<size; i++)
		for (j=0; j<size; j++) {
			a = adjacent_to (board, size, i, j);  // checa quantas células vivas
                                            // estão próximas da atual
      // regras
			if (a == 2) newboard[i][j] = board[i][j];
			if (a == 3) newboard[i][j] = 1;
			if (a < 2) newboard[i][j] = 0;
			if (a > 3) newboard[i][j] = 0;
		}
}

/* imprime o tabuleiro na saída de erro */
void print(cell_t **board, int size) 
{
	int	i, j;
	/* para cada linha */
	for (j=0; j<size; j++) {
		/* imprime o estado de cada coluna... */
		for (i=0; i<size; i++) 
			fprintf(stderr, "%c", board[i][j] ? 'x' : ' ');
		fprintf(stderr, "\n");
	}
}

/* lê arquivo com o tabuleiro inicial */
void read_file(char *file, cell_t ***board, int *size) 
{
	int	i, j;

	FILE    *f;
	f = fopen(file, "r");
  if (f == NULL) 
  {
    perror(file);
    exit(-1);
  }
  
  fprintf(stdout, "Lendo arquivo... ");

	fscanf(f,"%d", size);
	while (fgetc(f) != '\n') /* no-op */;
	
  *board = allocate_board(*size);

// lê tabuleiro
	char	*s = (char *) malloc(*size+10);
	char c;
	for (j=0; j<*size; j++) {
		/* lê string */
		fgets (s, *size+10,f);
		/* copia string para o tabuleiro */
		for (i=0; i<*size; i++)
		{
			(*board)[i][j] = s[i] == 'x';
		}
	}

  fprintf(stdout, "ok\n");
  fclose(f);
}

int main(int argc, char *argv[])
{
  struct timeval start, stop;
	
  /* Linha de comando */
  if (argc <=2) {
    fprintf(stdout, "Entrada inválida: use %s <arquivo> <passos>\n", argv[0]);
    exit(-1);
  }
  
  int size, steps = strtol(argv[2], NULL, 10);
  cell_t **prev;

  // lê arquivo com o tabuleiro
  read_file(argv[1], &prev, &size);

	cell_t **next = allocate_board (size);
	cell_t **tmp;
	int i,j;
  
  gettimeofday(&start, NULL);

  // laço principal do jogo
	for (i=0; i<steps; i++) {
    // lê o tabuleiro 'prev' e escreve no 'next'
		play(prev,next,size);

    // permuta os tabuleiros
		tmp = next;
		next = prev;
		prev = tmp;
	}

  gettimeofday(&stop, NULL); 

	print(prev,size);
	
  double t = (((double)(stop.tv_sec)*1000.0  + (double)(stop.tv_usec / 1000.0)) - \
                   ((double)(start.tv_sec)*1000.0 + (double)(start.tv_usec / 1000.0)));

  fprintf(stdout, "Tempo decorrido = %g ms\n", t);

  free_board(prev,size);
	free_board(next,size);
}
