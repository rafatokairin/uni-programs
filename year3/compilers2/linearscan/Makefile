LEX_FILE = linearscan.l
YACC_FILE = linearscan.y
OUTPUT_FILE = linearscan
HEADER_FILE = linearscan.hpp
CPP_FILE = linearscan.cpp

all: $(OUTPUT_FILE)

$(OUTPUT_FILE): lex.yy.c linearscan.tab.c $(CPP_FILE) $(HEADER_FILE)
	g++ -o $(OUTPUT_FILE) lex.yy.c linearscan.tab.c $(CPP_FILE) -I.

lex.yy.c: $(LEX_FILE)
	flex $(LEX_FILE)

linearscan.tab.c: $(YACC_FILE)
	bison -d $(YACC_FILE)

clean:
	rm -f *.yy.c *.tab.c *.tab.h $(OUTPUT_FILE)