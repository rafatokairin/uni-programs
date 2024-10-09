%option noyywrap
%option yylineno

%{
#include <sintatico.tab.h>
extern YYSTYPE yylval;
int eof = 0;
int textAnt = 0;
int yycolumn = 1;

void addUniao() {
    yylval.token.valor = strdup(yytext);
    yylval.token.column = yycolumn;
    yylval.token.line = yylineno;
}
%}

%%
<<EOF>> { eof = 1; return 0; }
"$" { return EOL; }
"int" { addUniao(); yycolumn += strlen(yytext); return INT; } 
"char" { addUniao(); yycolumn += strlen(yytext); return CHAR; }
"float" { addUniao(); yycolumn += strlen(yytext); return FLOAT; }
"," { addUniao(); yycolumn++; return COMMA; }
" " { yycolumn++; }
\n { yycolumn = 1; }
[a-z]+ { addUniao(); yycolumn += strlen(yytext); return ID; }

. { 
    if (textAnt) printf("\n");
    printf("error:lexical:%d:%d: %s", yylineno, yycolumn, yytext);
    yycolumn += strlen(yytext);
    exit(1);
}
%%