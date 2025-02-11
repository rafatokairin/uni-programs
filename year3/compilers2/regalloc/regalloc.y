%{
    #include <string>
    #include <vector>
    #include <iostream>
    #include <iostream>
    #include <string.h>
    #include <stdbool.h>
    #include <vector>
    #include <stack>
    #include "regalloc.hpp"
    extern int yylex();
    extern char* yytext;
    void yyerror(std::string s);
    void spillError();
    bool spill = false;
    std::vector<int> interf;
    extern Grafo* grafo;
%}

%union {
    int integer;
    char* s;
}

%token <integer> INT;
%token <s>GRAPH;
%token EQUAL;
%token K;
%token COLON;
%token ARROW;
%token EOL;

%type <integer> val;

%start start

%%
start: 
    GRAPH val COLON EOL set EOL virtualReg { grafo->g = $2; }

set: 
    K EQUAL val { grafo->cor = $3; }

virtualReg: 
    interf EOL virtualReg
    | interf
                
interf:
    val ARROW reg {
        handleInterference(grafo, $1, interf);
        interf.clear();
    }

reg: 
    reg val { interf.push_back($2); }
    | val { interf.push_back($1); }

val:
    INT { $$ = $1; }
%%

void yyerror(std::string s) {
    std::cout << "Error: " << s << std::endl;
}

int main(int argc, char **argv){
    yyparse();
    handleGrafo();
    return 0;
}