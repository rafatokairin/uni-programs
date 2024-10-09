%option noyywrap
%option yylineno

%{
#include <stdlib.h>
#include <string.h>
#include <sintatico.tab.h>

extern YYSTYPE yylval;
extern int erroSintatico;

int eof = 0;
int yycolumn = 1;
int errorLex = 0;
int textAnt = 0;
int nonlin = 0;
char invalid[256] = "";

void printErrorLex() {
    if (strlen(invalid) < 1) return;
    if (textAnt) printf("\n");
    printf("Caractere(s) invalido(s) -> [%s]", invalid);
    textAnt = 1;
    memset(invalid, '\0', sizeof(invalid));
}

void addToUnion() {
    yylval.token.valor = strdup(yytext);
    yylval.token.column = yycolumn;
    yylval.token.line = yylineno;
    nonlin = 1;
}

%}

%%

<<EOF>> { 
    eof = 1;      
    if (errorLex) {
        printErrorLex();
        return ERRO;
    } 
    return EOL;
}

\n {
    yycolumn = 1; 
    if (errorLex) {
        printErrorLex();
        return ERRO; 
    }
    return EOL; 
}

[ \t] { yycolumn += strlen(yytext); }
(([0-9]+"."[0-9]*)|([0-9]*"."[0-9]+)) { 
    addToUnion();
    yylval.token.type = REAL;
    yycolumn += strlen(yytext);
    return REAL; }
[0-9]+ {  
    addToUnion();
    yylval.token.type = INT;
    yycolumn += strlen(yytext); 
    return INT; }
"+" { 
    addToUnion();
    yylval.token.type = ADD;
    yycolumn += strlen(yytext); 
    return ADD; }
"*" { 
    addToUnion(); 
    yylval.token.type = MUL;
    yycolumn += strlen(yytext); 
    return MUL; }
"-" { 
    addToUnion(); 
    yylval.token.type = SUB;
    yycolumn += strlen(yytext); 
    return SUB; }
"/" {
    addToUnion(); 
    yylval.token.type = DIV;
    yycolumn += strlen(yytext); 
    return DIV; }
"^" {
    addToUnion(); 
    yylval.token.type = POW;
    yycolumn += strlen(yytext); 
    return POW; }
"%" {
    addToUnion(); 
    yylval.token.type = MOD;
    yycolumn += strlen(yytext); 
    return MOD; }
"(" {
    addToUnion(); 
    yylval.token.type = L_PAREN;
    yycolumn += strlen(yytext); 
    return L_PAREN; }
")" {
    addToUnion(); 
    yylval.token.type = R_PAREN;
    yycolumn += strlen(yytext); 
    return R_PAREN; }
"sen" {
    addToUnion(); 
    yylval.token.type = SEN;
    yycolumn += strlen(yytext); 
    return SEN; }
"cos" {
    addToUnion(); 
    yylval.token.type = COS;
    yycolumn += strlen(yytext); 
    return COS; }
"tan" {
    addToUnion(); 
    yylval.token.type = TAN;
    yycolumn += strlen(yytext); 
    return TAN; }
"abs" {
    addToUnion(); 
    yylval.token.type = ABS;
    yycolumn += strlen(yytext); 
    return ABS; }
([a-zA-Z]+[a-zA-Z0-9]*) {
    addToUnion();
    yylval.token.type = ID;
    yycolumn += strlen(yytext); 
    return ID; }
. { 
    errorLex = 1; 
    if (strlen(invalid) != 0) strcat(invalid, ",");
    strncat(invalid, yytext, 1);
    yycolumn += strlen(yytext);
    nonlin = 1;
}
%%
