%{
    #include <iostream>
    #include <string.h>
    #include <stdbool.h>
    #include <vector>
    #include <stack>
    #include "linearscan.hpp"
    extern int yylex();
    extern char* yytext;
    void yyerror(std::string s);
    extern LS* linearScan;
%}

%union {
    int integer;
    char* s;
}

%token <integer> INT;
%token <s>ID;
%token EQUAL;
%token K;
%token ARROW;
%token EOL;

%type <integer> val;

%start start

%%
start: 
    K EQUAL val EOL set { linearScan->k = $3; }

set:
    reg EOL set {}
    | reg {}

reg: 
    ID ARROW val val { linearScan->addReg($1, $3, $4); }

val: 
    INT { $$ = $1; }
%%

void yyerror(std::string s) {
    std::cout << "Error: " << s << std::endl;
}

int main(int argc, char **argv){
    yyparse();
    handleLinearScan();
    return 0;
}