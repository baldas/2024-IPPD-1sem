
CC = gcc

CFLAGS = -O3
LDFLAGS = -fopenmp

TARGET = primos.x 

SOURCE = primos.c

ALL: $(TARGET)

primos.x: $(SOURCE)
	$(CC) $(CFLAGS) $< -o$@ $(LDFLAGS)

clean:
	rm -f $(TARGET) *.o
