all: lex.yy.c
	gcc -o lexico lex.yy.c -ll

lex.yy.c: lexico.l
	flex ./lexico.l

clean:
	rm -rf lexico