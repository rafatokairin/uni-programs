%option noyywrap 
%{
	#include <string.h>
	#include <sintatico.tab.h>
	int lin = 1;
	int col = 1;

void warning() {
	int i = 0;
	for (i = 0; i < strlen(yytext); i++) {
		if (yytext[i]=='\n') {
			lin += 1; 
			col = 1;
		} else col += 1;
		if (yytext[i]=='/' && i < (strlen(yytext)-1) && i > 0)
			if(yytext[i+1]=='*' && yytext[i+2] != '/') 
				printf("warning:%d:%d: \'/*\' within block comment\n", lin, col-1);
	}	
}

%}
%% 
"void" {col += 4; return VOID;}
"int" {col += 3; return INT;}
"char" {col += 4; return CHAR;}
"return" {col += 6; return RETURN;}
"break" {col += 5; return BREAK;}
"switch" {col += 6; return SWITCH;}
"case" {col += 4; return CASE;}
"default" {col += 7; return DEFAULT;}
"do" {col += 2; return DO;}
"while" {col += 5; return WHILE;}
"for" {col += 3; return FOR;}
"if" {col += 2; return IF;}
"else" {col += 4; return ELSE;}
"typedef" {col += 7; return TYPEDEF;}
"struct" {col += 6; return STRUCT;}
"printf" {col += 6; return PRINTF;}
"scanf" {col += 5; return SCANF;}
"exit" {col += 4; return EXIT;}
"#" {col += 1; return NUMBER_SIGN;}
"define" {col += 6; return DEFINE;}
"+" {col += 1; return PLUS;}
"-" {col += 1; return MINUS;}
"*" { col += 1; return MULTIPLY;}
"/" {col += 1; return DIV;}
"%" {col += 1; return REMAINDER;}
"++" {col += 2; return INC;}
"--" {col += 2; return DEC;}
"&" {col += 1; return BITWISE_AND;}
"|" {col += 1; return BITWISE_OR;}
"~" {col += 1; return BITWISE_NOT;}
"^" {col += 1; return BITWISE_XOR;}
"&&" {col += 2; return LOGICAL_AND;}
"||" {col += 2; return LOGICAL_OR;}
"!" {col += 1; return NOT;}
"==" {col += 2; return EQUAL;}
"!=" {col += 2; return NOT_EQUAL;}
"<" {col += 1; return LESS_THAN;}
">" {col += 1; return GREATER_THAN;}
"<=" {col += 2; return LESS_EQUAL;}
">=" {col += 2; return GREATER_EQUAL;}
">>" {col += 2; return R_SHIFT;}
"<<" {col += 2; return L_SHIFT;}
"=" {col += 1; return ASSIGN;}
"+=" {col += 2; return ADD_ASSIGN;}
"-=" {col += 2; return MINUS_ASSIGN;}
";" {col += 1; return SEMICOLON;}
"," {col += 1; return COMMA;}
":" {col += 1; return COLON;}
"(" {col += 1; return L_PAREN;}
")" {col += 1; return R_PAREN;}
"{" {col += 1; return L_CURLY_BRACKET;}
"}" {col += 1; return R_CURLY_BRACKET;}
"[" { col += 1; return L_SQUARE_BRACKET;}
"]" { col += 1; return R_SQUARE_BRACKET;}
"?" {col += 1; return TERNARY_CONDITIONAL;}
"->" {col += 2; return POINTER;}
[_a-zA-Z][_a-zA-Z0-9]* {if (strlen(yytext)>255){return IDENTIFIER_TOO_LONG;} else {col += strlen(yytext);return IDENTIFIER;}}
"0"[1-7][0-7]* {col += strlen(yytext);return NUM_OCTAL;}
[0-9]+ { col += strlen(yytext);return NUM_INTEGER;}
0[xX][0-9a-fA-F]+ {col += strlen(yytext);return NUM_HEXA;}
["]([^"\\\n]|\\.|\\\n)*["] {col += strlen(yytext);return STRING;}
"\'""\\"?."\'" {col += strlen(yytext); return CHARACTER;}
[\r\t \f] {col += 1;}
"//".*[\n] {lin += 1; col = 1;}
"//".* {return END_OF_FILE;}
("/*"([^*]|[\n]|("*"+([^*/]|[\n])))*"*/") {warning();}
("/*"([^*]|[\n]|("*"+([^*/]|[\n])))*) {return UNTERMINATED_COMMENT;}
[\n] {lin += 1; col = 1;}
<<EOF>> {return END_OF_FILE;}
. { col += strlen(yytext); return OTHER;}
%%