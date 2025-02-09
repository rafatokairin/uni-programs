%option noyywrap
%{
    #include <stdio.h>
    #include <stdbool.h>
    #include <stdlib.h>
    #include "parser.tab.h"
    #include <iostream>
    #include <iomanip>
    #include <string>
    #include <vector>
    #include <queue>
    #include <stack>
    #include <cstring>
    #include <cmath>
    extern bool is_lex;
    extern bool quit_prog;
%}

%%
"about"               { return ABOUT; }
"abs"                 { return ABS; }
"axis"                { return AXIS; }
"cos"                 { return COS; }
"determinant"         { return DETERMINANT; }
"erase"               { return ERASE; }
"float"               { return FLOAT; }
"h_view"              { return H_VIEW; }
"integral_steps"      { return INTEGRAL_STEPS; }
"integrate"           { return INTEGRATE; }
"linear_system"       { return LINEAR_SYSTEM; }
"matrix"              { return MATRIX; }
"off"                 { return OFF; }
"on"                  { return ON; }
"plot"                { return PLOT; }
"precision"           { return PRECISION; }
"quit"                { return QUIT; }
"reset"               { return RESET; }
"rpn"                 { return RPN; }
"sen"                 { return SEN; }
"set"                 { return SET; }
"settings"            { return SETTINGS; }
"show"                { return SHOW; }
"solve"               { return SOLVE; }
"sum"                 { return SUM; }
"symbols"             { return SYMBOLS; }
"tan"                 { return TAN; }
"v_view"              { return V_VIEW; }

[Xx]                  { return VAR; }
[Pp][Ii]              { return PI; }
[Ee]                  { return E; }
[0-9]+                { yylval.intValue = atoi(yytext); return INT; }
[0-9]+\.[0-9]+        { yylval.floatValue = atof(yytext); return REAL; }
[a-zA-Z][_0-9a-zA-Z]* { yylval.stringValue = strdup(yytext); return IDENTIFIER; }

"+"                   { return ADD; }
"-"                   { return SUB; }
"*"                   { return MUL; }
"/"                   { return DIV; }
"^"                   { return POW; }
"%"                   { return REST; }
"("                   { return LPAREN; }
")"                   { return RPAREN; }
"="                   { return EQUAL; }
":="                  { return ASSIGN; }
":"                   { return COLON; }
"["                   { return LBRACKET; }
"]"                   { return RBRACKET; }
";"                   { return SEMICOLON; }
","                   { return COMMA; }
"\n"                  { return EOL; }
[ \t]+                { }
.                     { if (!quit_prog) { std::cout << "\nInvalid Symbol: " << yytext << "\n\n"; is_lex = true; quit_prog = true; } }
%%