LEX_FILE = lex.l
YACC_FILE = parser.y
OUTPUT_FILE = dcmat
CPP_FILES = commands.cpp hash.cpp ast.cpp
HEADER_FILES = commands.hpp ast.hpp hash.hpp

all: $(OUTPUT_FILE)

$(OUTPUT_FILE): lex.yy.c parser.tab.c $(CPP_FILES) $(HEADER_FILES)
	g++ -o $(OUTPUT_FILE) lex.yy.c parser.tab.c $(CPP_FILES) -I.

lex.yy.c: $(LEX_FILE)
	flex $(LEX_FILE)

parser.tab.c: $(YACC_FILE)
	bison -d $(YACC_FILE)

clean:
	rm -f *.yy.c *.tab.c *.tab.h $(OUTPUT_FILE)
