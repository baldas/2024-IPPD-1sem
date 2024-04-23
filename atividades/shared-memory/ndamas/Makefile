
CC = gcc

CFLAGS = -O3
LDFLAGS = -fopenmp

TARGET = ndamas.x ndamas-par.x 

SOURCE = ndamas.c
SOURCE_PAR = ndamas-solucao.c

ALL: $(TARGET)

ndamas.x: $(SOURCE)
	$(CC) $(CFLAGS) $< -o$@ $(LDFLAGS)

ndamas-par.x: $(SOURCE_PAR)
	$(CC) $(CFLAGS) $< -o$@ $(LDFLAGS)

clean:
	rm -f $(TARGET) *.o
