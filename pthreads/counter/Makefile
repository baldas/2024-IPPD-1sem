
CC = gcc

CFLAGS = -O3
LDFLAGS = -pthread

TARGET = count-seq.x count-par1.x count-par2.x count-par3.x

SOURCE_SEQ = counter.c
SOURCE_PAR1 = counter-par1.c
SOURCE_PAR2 = counter-par2.c
SOURCE_PAR3 = counter-par3.c

ALL: $(TARGET)

count-seq.x: $(SOURCE_SEQ)
	$(CC) $(CFLAGS) $< -o$@ $(LDFLAGS)

count-par1.x: $(SOURCE_PAR1)
	$(CC) $(CFLAGS) $< -o$@ $(LDFLAGS)

count-par2.x: $(SOURCE_PAR2)
	$(CC) $(CFLAGS) $< -o$@ $(LDFLAGS)

count-par3.x: $(SOURCE_PAR3)
	$(CC) $(CFLAGS) $< -o$@ $(LDFLAGS)

clean:
	rm -f $(TARGET) *.o
