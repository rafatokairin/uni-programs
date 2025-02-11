LEX_FILE = regalloc.l
YACC_FILE = regalloc.y
OUTPUT_FILE = regalloc
HEADER_FILE = regalloc.hpp
SRC_FILES = regalloc.cpp

all: $(OUTPUT_FILE)

$(OUTPUT_FILE): lex.yy.c regalloc.tab.c $(HEADER_FILE) $(SRC_FILES)
	g++ -o $(OUTPUT_FILE) lex.yy.c regalloc.tab.c $(SRC_FILES) -I.

lex.yy.c: $(LEX_FILE)
	flex $(LEX_FILE)

regalloc.tab.c: $(YACC_FILE)
	bison -d $(YACC_FILE)

clean:
	rm -f *.yy.c *.tab.c *.tab.h $(OUTPUT_FILE)
