%option noyywrap
%option yylineno
%x COMMENT
%{
int end = 0, yycolumn = 1, lin, col;
void updateColumn() {
    end = 1;
    yycolumn += strlen(yytext);
}
void acceptAction(const char* token) {
    if (end) printf("\n");
    printf("%s", token);
    updateColumn();
}
%}

%%
"//".*\n { }
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
\"([^\\\"]|\\.)*\" {
    if (end) printf("\n");
    printf("STRING(%.*s)", (int)(strlen(yytext) - 2), yytext + 1); 
    updateColumn();
}
" " { yycolumn++; }
\n { yycolumn = 1; }
(_*[a-zA-Z][a-zA-Z0-9_]*) {
    if (end) printf("\n");
    if (strlen(yytext) > 255) {
        printf("error:lexical:%d:%d: identifier too long", yylineno, yycolumn);
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
    printf("error:lexical:%d:%d: %s", yylineno, yycolumn, yytext);
    updateColumn();
}
"/*" { 
    BEGIN(COMMENT); 
    lin = yylineno;
    col = yycolumn; 
    yycolumn += strlen(yytext); 
}
<COMMENT>"*/" {
    BEGIN(INITIAL); 
    yycolumn += strlen(yytext); 
} 
<COMMENT>"/*" {
    char next = input();
    if (next == '\n') yylineno--;
    if (next == '/') { 
        BEGIN(INITIAL); 
        yycolumn += strlen(yytext) + 1; 
    } else {
        if (end) printf("\n");
        printf("warning:%d:%d: '%s' within block comment", yylineno, yycolumn, yytext); 
        yycolumn += strlen(yytext);
        if (next == '\n') yylineno++;
        unput(next);
    }
    end = 1;
}
<COMMENT>. { yycolumn += strlen(yytext); }
<COMMENT>\n { yycolumn = 1; }
<COMMENT><<EOF>> { 
    if (end) printf("\n");
    printf("error:lexical:%d:%d: unterminated comment", lin, col); 
    exit(1); 
}
%%

int main(int argc, char *argv[]) {
    yylex();
    return 0;
}