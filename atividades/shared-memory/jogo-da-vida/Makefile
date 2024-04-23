
CC = gcc

CFLAGS = -O3
LDFLAGS = -fopenmp

TARGET = vida.x 

SOURCE = vida.c

ALL: $(TARGET)

vida.x: $(SOURCE)
	$(CC) $(CFLAGS) $< -o$@ $(LDFLAGS)

clean:
	rm -f $(TARGET) *.o
