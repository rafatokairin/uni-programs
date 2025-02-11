%option noyywrap
%{
    #include "regalloc.tab.h"
    #include <stdio.h>
    #include <stdbool.h>
    #include <stdlib.h>    
%}

%%
[0-9]+ {yylval.integer = atoi(yytext); return INT;}
"Grafo" { return GRAPH;}
"=" {return EQUAL;}
"K" {return K;}
":" {return COLON;}
"-->" {return ARROW;}
[\n] {return EOL;}
[ ] {};
"\0" {}
"\t" {};
%%