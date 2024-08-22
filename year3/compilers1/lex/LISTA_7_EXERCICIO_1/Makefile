PROJ_NAME = main.l

FLEX=flex
BISON=bison
CC=gcc
CFLAGS=
LIBS=

PROGRAMA = l7e1

$(PROGRAMA): $(PROJ_NAME)
	$(FLEX) $(PROJ_NAME)
	$(CC) lex.yy.c $(LIBS) -o $(PROGRAMA)

clean:
	rm -f lex.yy.c
	rm -f l7e1