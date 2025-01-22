TARGET = barb
CC = gcc
CFLAGS = -Wall -pthread -O2
SRC = barb.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)