%option noyywrap
%{
    #include "linearscan.tab.h"
    #include <stdio.h>
    #include <stdbool.h>
    #include <stdlib.h>    
%}

%%
[0-9]+     { yylval.integer = atoi(yytext); return INT; };
"vr"[0-9]+ { yylval.s = strdup(yytext); return ID; };
"="        { return EQUAL; };
"K"        { return K; };
"-->"      { return ARROW; };
[\n]       { return EOL; };
[ ]        { };
"\0"       { };
"\t"       { };
.          { };
%%