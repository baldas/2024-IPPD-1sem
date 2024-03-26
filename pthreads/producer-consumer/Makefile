CC  := gcc

CFLAGS  := -O3
LDFLAGS := -pthread

TARGET := prodcon.x 

SOURCE := prodcon.c buffer.c


ALL: $(TARGET)

prodcon.x: $(SOURCE)
	$(CC) $(CFLAGS) $^ -o prodcon.x $(LDFLAGS)


clean:
	rm -f $(TARGET) *.o 
