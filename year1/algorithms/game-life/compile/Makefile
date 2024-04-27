PROJ_NAME = main

STUDENT = rafatokairin

CC = gcc
CFLAGS = -ggdb -O0 -std=c99 -fstack-protector-all -Werror=implicit-function-declaration
LDFLAGS=-O0 -g

SRCDIR = ./compile ../headers ../src

SRC = $(foreach dir,$(SRCDIR),$(wildcard $(dir)/*.c))

OBJ = $(SRC:.c=.o)

EXEC = main

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ) -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

pack: $(PROJ_NAME)
	rm -f ../$(STUDENT).zip
	echo $(STUDENT)
	date >> .entrega
	cd ..; zip $(STUDENT).zip -r src/*.c src/*.h src/Makefile LEIA-ME.txt .entrega