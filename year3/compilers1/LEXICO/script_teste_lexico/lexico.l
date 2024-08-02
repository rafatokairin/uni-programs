%option noyywrap
%option yylineno
%x com
%{
int yycolumnno = 1, lin, col, end = 0;
void updateColumn() {
    end = 1;
    yycolumnno += strlen(yytext);
}
void acceptAction(const char* token) {
    if (end) printf("\n");
    printf("%s", token);
    updateColumn();
}
%}

%%
"void" { acceptAction("VOID"); }
"int" { acceptAction("INT"); }
"char" { acceptAction("CHAR"); }
"return" { acceptAction("RETURN"); }
"break" { acceptAction("BREAK"); }
"switch" { acceptAction("SWITCH"); }
"case" { acceptAction("CASE"); }
"default" { acceptAction("DEFAULT"); }
"do" { acceptAction("DO"); }
"while" { acceptAction("WHILE"); }
"for" { acceptAction("FOR"); }
"if" { acceptAction("IF"); }
"else" { acceptAction("ELSE"); }
"typedef" { acceptAction("TYPEDEF"); }
"struct" { acceptAction("STRUCT"); }
"+" { acceptAction("PLUS"); }
"-" { acceptAction("MINUS"); }
"*" { acceptAction("MULTIPLY"); }
"/" { acceptAction("DIV"); }
"%" { acceptAction("REMAINDER"); }
"++" { acceptAction("INC"); }
"--" { acceptAction("DEC"); }
"&" { acceptAction("BITWISE_AND"); }
"|" { acceptAction("BITWISE_OR"); }
"~" { acceptAction("BITWISE_NOT"); }
"^" { acceptAction("BITWISE_XOR"); }
"!" { acceptAction("NOT"); }
"&&" { acceptAction("LOGICAL_AND"); }
"||" { acceptAction("LOGICAL_OR"); }
"==" { acceptAction("EQUAL"); }
"!=" { acceptAction("NOT_EQUAL"); }
"<" { acceptAction("LESS_THAN"); }
">" { acceptAction("GREATER_THAN"); }
"<=" { acceptAction("LESS_EQUAL"); }
">=" { acceptAction("GREATER_EQUAL"); }
">>" { acceptAction("R_SHIFT"); }
"<<" { acceptAction("L_SHIFT"); }
"=" { acceptAction("ASSIGN"); }
"+=" { acceptAction("ADD_ASSIGN"); }
"-=" { acceptAction("MINUS_ASSIGN"); }
";" { acceptAction("SEMICOLON"); }
"," { acceptAction("COMMA"); }
":" { acceptAction("COLON"); }
"(" { acceptAction("L_PAREN"); }
")" { acceptAction("R_PAREN"); }
"{" { acceptAction("L_CURLY_BRACKET"); }
"}" { acceptAction("R_CURLY_BRACKET"); }
"[" { acceptAction("L_SQUARE_BRACKET"); }
"]" { acceptAction("R_SQUARE_BRACKET"); }
"?" { acceptAction("TERNARY_CONDITIONAL"); }
"#" { acceptAction("NUMBER_SIGN"); }
"->" { acceptAction("POINTER"); }
"printf" { acceptAction("PRINTF"); }
"scanf" { acceptAction("SCANF"); }
"define" { acceptAction("DEFINE"); }
"exit" { acceptAction("EXIT"); }
"//".*\n { }
\"([^\\\"]|\\.)*\" {
    if (end) printf("\n");
    printf("STRING(%.*s)", (int)(strlen(yytext) - 2), yytext + 1); 
    updateColumn();
}
" " { yycolumnno++; }
\n { yycolumnno = 1; }
(_*[a-zA-Z][a-zA-Z0-9_]*) {
    if (end) printf("\n");
    if (strlen(yytext) > 255) {
        printf("error:lexical:%d:%d: identifier too long", yylineno, yycolumnno);
    } else {
        printf("IDENTIFIER(%s)", yytext);  
    }
    updateColumn();
}
"'"(\\.|[^\\']){1}"'" {
    if (end) printf("\n");
    printf("CHARACTER(%.*s)", (int)(strlen(yytext) - 2), yytext + 1); 
    updateColumn();
}
(0x[0-9a-f]+)|(0X[0-9A-F]+) {
    if (end) printf("\n");
    printf("NUM_HEXA(%s)", yytext);
    updateColumn();
}
0[1-7][0-7]* {
    if (end) printf("\n");
    printf("NUM_OCTAL(%s)", yytext);
    updateColumn();
}
[0-9]+ {
    if (end) printf("\n");
    printf("NUM_INTEGER(%s)", yytext);
    updateColumn();
}
. { 
    if (end) printf("\n");
    printf("error:lexical:%d:%d: %s", yylineno, yycolumnno, yytext);
    updateColumn();
}
"/*" { 
    BEGIN(com); 
    lin = yylineno;
    col = yycolumnno; 
    yycolumnno += strlen(yytext); 
}
<com>"*/" {
    BEGIN(INITIAL); 
    yycolumnno += strlen(yytext); 
} 
<com>"/*" {
    char prox = input();
    if (prox == '\n') yylineno--;
    if (prox == '/') { 
        BEGIN(INITIAL); 
        yycolumnno += strlen(yytext) + 1; 
    } else {
        if (end) printf("\n");
        printf("warning:%d:%d: '%s' within block comment", yylineno, yycolumnno, yytext); 
        yycolumnno += strlen(yytext);
        if (prox == '\n') yylineno++;
        unput(prox);
    }
    end = 1;
}
<com>. { yycolumnno += strlen(yytext); }
<com>\n { yycolumnno = 1; }
<com><<EOF>> { 
    if (end) printf("\n");
    printf("error:lexical:%d:%d: unterminated comment", lin, col); 
    exit(1); 
}
%%

int main(int argc, char *argv[]) {
    yylex();
    return 0;
}