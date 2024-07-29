%option noyywrap
%option yylineno
%x COMMENT
%{
int newline = 0;
int yycolumn = 1;
int lin;
int col;

void printfToken(char *token, int *newline) {
    if (*newline) printf("\n");
    printf("%s", token);
    *newline = 1;
}

%}

%%

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
        if (newline) printf("\n");
        printf("warning:%d:%d: '%s' within block comment", yylineno, yycolumn, yytext); 
        yycolumn += strlen(yytext);
        if (next == '\n') yylineno++;
        unput(next);
    }
    newline = 1;
}
<COMMENT>. { yycolumn += strlen(yytext); }
<COMMENT>\n { yycolumn = 1; }
<COMMENT><<EOF>> { 
    if (newline) printf("\n");
    printf("error:lexical:%d:%d: unterminated comment", lin, col); 
    exit(1); 
}

"//".*\n { printf("comentario de linha\n"); }
"void" { printfToken("VOID", &newline); yycolumn += strlen(yytext); }
"int" {  printfToken("INT", &newline); yycolumn += strlen(yytext); }
"char" { printfToken("CHAR", &newline); yycolumn += strlen(yytext); }
"return" { printfToken("RETURN", &newline); yycolumn += strlen(yytext); }
"break" { printfToken("BREAK", &newline); yycolumn += strlen(yytext);  }
"switch" { printfToken("SWITCH", &newline); yycolumn += strlen(yytext); }
"case" { printfToken("CASE", &newline); yycolumn += strlen(yytext); }
"default" { printfToken("DEFAULT", &newline); yycolumn += strlen(yytext); }
"do" { printfToken("DO", &newline); yycolumn += strlen(yytext); }
"while" { printfToken("WHILE", &newline); yycolumn += strlen(yytext); }
"for" { printfToken("FOR", &newline); yycolumn += strlen(yytext); }
"if" { printfToken("IF", &newline); yycolumn += strlen(yytext); }
"else" { printfToken("ELSE", &newline); yycolumn += strlen(yytext); }
"typedef" { printfToken("TYPEDEF", &newline); yycolumn += strlen(yytext); }
"struct" { printfToken("STRUCT", &newline); yycolumn += strlen(yytext); }
"+" { printfToken("PLUS", &newline); yycolumn += strlen(yytext); }
"-" { printfToken("MINUS", &newline); yycolumn += strlen(yytext); }
"*" { printfToken("MULTIPLY", &newline); yycolumn += strlen(yytext); }
"/" { printfToken("DIV", &newline); yycolumn += strlen(yytext); }
"%" { printfToken("REMAINDER", &newline); yycolumn += strlen(yytext); }
"++" { printfToken("INC", &newline); yycolumn += strlen(yytext); }
"--" { printfToken("DEC", &newline); yycolumn += strlen(yytext); }
"&" { printfToken("BITWISE_AND", &newline); yycolumn += strlen(yytext); }
"|" { printfToken("BITWISE_OR", &newline); yycolumn += strlen(yytext); }
"~" { printfToken("BITWISE_NOT", &newline); yycolumn += strlen(yytext); }
"^" { printfToken("BITWISE_XOR", &newline); yycolumn += strlen(yytext); }
"!" { printfToken("NOT", &newline); yycolumn += strlen(yytext); }
"&&" { printfToken("LOGICAL_AND", &newline); yycolumn += strlen(yytext); }
"||" { printfToken("LOGICAL_OR", &newline); yycolumn += strlen(yytext); }
"==" { printfToken("EQUAL", &newline); yycolumn += strlen(yytext); }
"!=" { printfToken("NOT_EQUAL", &newline); yycolumn += strlen(yytext); }
"<" { printfToken("LESS_THAN", &newline); yycolumn += strlen(yytext); }
">" { printfToken("GREATER_THAN", &newline); yycolumn += strlen(yytext); }
"<=" { printfToken("LESS_EQUAL", &newline); yycolumn += strlen(yytext); }
">=" { printfToken("GREATER_EQUAL", &newline); yycolumn += strlen(yytext); }
">>" { printfToken("R_SHIFT", &newline); yycolumn += strlen(yytext); }
"<<" { printfToken("L_SHIFT", &newline); yycolumn += strlen(yytext); }
"=" { printfToken("ASSIGN", &newline); yycolumn += strlen(yytext);}
"+=" { printfToken("ADD_ASSIGN", &newline); yycolumn += strlen(yytext); }
"-=" { printfToken("MINUS_ASSIGN", &newline); yycolumn += strlen(yytext); }
";" { printfToken("SEMICOLON", &newline); yycolumn += strlen(yytext); }
"," { printfToken("COMMA", &newline); yycolumn += strlen(yytext); }
":" { printfToken("COLON", &newline); yycolumn += strlen(yytext); }
"(" { printfToken("L_PAREN", &newline); yycolumn += strlen(yytext); }
")" { printfToken("R_PAREN", &newline); yycolumn += strlen(yytext); }
"{" { printfToken("L_CURLY_BRACKET", &newline); yycolumn += strlen(yytext); }
"}" { printfToken("R_CURLY_BRACKET", &newline); yycolumn += strlen(yytext); }
"[" { printfToken("L_SQUARE_BRACKET", &newline); yycolumn += strlen(yytext); }
"]" { printfToken("R_SQUARE_BRACKET", &newline); yycolumn += strlen(yytext); }
"?" { printfToken("TERNARY_CONDITIONAL", &newline); yycolumn += strlen(yytext); }
"#" { printfToken("NUMBER_SIGN", &newline); yycolumn += strlen(yytext); }
"->" { printfToken("POINTER", &newline); yycolumn += strlen(yytext); }
"printf" { printfToken("PRINTF", &newline); yycolumn += strlen(yytext); }
"scanf" { printfToken("SCANF", &newline); yycolumn += strlen(yytext); }
"define" { printfToken("DEFINE", &newline); yycolumn += strlen(yytext); }
"exit" { printfToken("EXIT", &newline); yycolumn += strlen(yytext); }

\"([^\\\"]|\\.)*\" {
    if (newline) printf("\n");
    printf("STRING(%.*s)", (int)(strlen(yytext) - 2), yytext + 1); 
    newline = 1;
    yycolumn += strlen(yytext);
}
" " { yycolumn++; }
\n { yycolumn = 1; }
(_*[a-zA-Z][a-zA-Z0-9_]*) {
    if (newline) printf("\n");
    if (strlen(yytext) > 255) {
        printf("error:lexical:%d:%d: identifier too long", yylineno, yycolumn);
    } else {
        printf("IDENTIFIER(%s)", yytext);  
    }
    newline = 1;
    yycolumn += strlen(yytext);
}
"'"(\\.|[^\\']){1}"'" {
    if (newline) printf("\n");
    printf("CHARACTER(%.*s)", (int)(strlen(yytext) - 2), yytext + 1); 
    newline = 1;
    yycolumn += strlen(yytext);
}
(0x[0-9a-f]+)|(0X[0-9A-F]+) {
    if (newline) printf("\n");
    printf("NUM_HEXA(%s)", yytext);
    newline = 1;
    yycolumn += strlen(yytext);
}
0[1-7][0-7]* {
    if (newline) printf("\n");
    printf("NUM_OCTAL(%s)", yytext);
    newline = 1;
    yycolumn += strlen(yytext);
}
[0-9]+ {
    if (newline) printf("\n");
    printf("NUM_INTEGER(%s)", yytext);
    newline = 1;
    yycolumn += strlen(yytext);
}
. { 
    if (newline) printf("\n");
    printf("error:lexical:%d:%d: %s", yylineno, yycolumn, yytext);
    newline = 1;
    yycolumn += strlen(yytext);
}

%%

int main(int argc, char *argv[]) {
    yylex();
    return 0;
}