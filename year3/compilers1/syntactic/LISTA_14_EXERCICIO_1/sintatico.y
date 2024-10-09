%{

#include <stdio.h>
#include <string.h>

extern int yylex();
extern int textAnt;
extern int yychar;
extern int eof;
extern int errorLex;
extern int nonlin;
int erroAux = 0;
int errorSint = 0;
int charError;
void yyerror(void *s);

%}
%union {
    struct {
        char *valor;
        int column;
        int line;
        int type;
    } token;
}

%token EOL
%token ADD
%token SUB
%token MUL
%token DIV
%token POW
%token MOD
%token L_PAREN
%token R_PAREN
%token SEN
%token COS
%token TAN
%token ABS
%token ID
%token REAL
%token INT
%token ERRO

%start Start

%left '+' '-'
%left '*' '/'
%right '^'

%%

Start: Exp EOL { errorSint = 0; return 0; }
    | Exp ERRO { erroAux = 1; return 0; }
    | error { if (errorSint == 2) return 0; errorSint = 1; charError = yychar; return 0;  }
;

Exp: Fator { }
    | Exp ADD Fator { } 
    | Exp SUB Fator { }
;

Fator: Termo { }
    | Fator MUL Termo { }
    | Fator DIV Termo { }
    | Fator POW Termo { }
    | Fator MOD Termo { } ;

Termo: L_PAREN Exp R_PAREN { } 
    | ID { }
    | INT { }
    | REAL { }
    | ADD Termo { }
    | SUB Termo { }
    | SEN L_PAREN Exp R_PAREN { }
    | COS L_PAREN Exp R_PAREN { }
    | TAN L_PAREN Exp R_PAREN { }
    | ABS L_PAREN Exp R_PAREN { } ;
%%

void yyerror(void *s) {}

void resetAux() {
    erroAux = 0; 
    errorLex = 0;
    errorSint = 0;
    nonlin = 0;
}

void goToNextLine() {
    while (yylex() != EOL);
}

int main(int argc, char* argv[]) {
    while (!eof) {
        yyparse();
        if (errorSint == 2) {
            if (yychar == EOL) resetAux();
            continue;
        }
        if (errorLex && !erroAux) continue;  
        if (erroAux) { 
            resetAux();
            continue;
        }

        if (textAnt) printf("\n");

        if (!nonlin) {
            resetAux();
            continue;
        }

        if (errorSint == 1) { 

            if (charError == 0 || charError == EOL || charError == YYEMPTY) {  // acabou a linha subitamente
                printf("A expressao terminou de forma inesperada.");
            } else {  
                printf("Erro de sintaxe na coluna [%d]: %s", yylval.token.column, yylval.token.valor);
            }
            errorSint = 2;

        } else if (errorSint == 0) {
            printf("EXPRESSAO CORRETA");
            resetAux();     
        }
        textAnt = 1; 
    } 
    return 0;
}