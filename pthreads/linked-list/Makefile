CC  := gcc

CFLAGS  := -O3
LDFLAGS := -pthread

TARGET = intset-seq intset-par1 intset-par2

SOURCE_SEQ = intset.c linkedlist.c
SOURCE_PAR1 = intset.c linkedlist-par1.c
SOURCE_PAR2 = intset.c linkedlist-par2.c


ALL: $(TARGET)

intset-seq: $(SOURCE_SEQ)
	$(CC) $(CFLAGS) $(SOURCE_SEQ) -o intset-seq $(LDFLAGS)

intset-par1: $(SOURCE_PAR1)
	$(CC) $(CFLAGS) $(SOURCE_PAR1) -o intset-par1 $(LDFLAGS)

intset-par2: $(SOURCE_PAR2)
	$(CC) $(CFLAGS) $(SOURCE_PAR2) -o intset-par2 $(LDFLAGS)

clean:
	rm -f $(TARGET) *.o 
