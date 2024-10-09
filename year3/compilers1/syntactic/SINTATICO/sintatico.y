%{
#include<stdio.h>
#include<string.h>
#include<stdarg.h>
extern char* yytext;
extern int yylex();
void yyerror(char *s);
FILE* input_file = NULL;
extern int col;
extern int lin;

%}
%token VOID
%token INT 
%token CHAR 
%token RETURN 
%token BREAK 
%token SWITCH 
%token CASE 
%token DEFAULT
%token DO 
%token WHILE 
%token FOR 
%token IF 
%token ELSE 
%token TYPEDEF 
%token STRUCT
%token PLUS 
%token MINUS 
%token MULTIPLY
%token DIV
%token REMAINDER
%token INC 
%token DEC 
%token BITWISE_AND
%token BITWISE_OR
%token BITWISE_NOT
%token BITWISE_XOR
%token NOT 
%token LOGICAL_AND 
%token LOGICAL_OR
%token EQUAL
%token NOT_EQUAL 
%token LESS_THAN
%token GREATER_THAN
%token LESS_EQUAL
%token GREATER_EQUAL
%token R_SHIFT
%token L_SHIFT
%token ASSIGN
%token ADD_ASSIGN
%token MINUS_ASSIGN
%token SEMICOLON
%token COMMA
%token COLON
%token L_PAREN
%token R_PAREN
%token L_CURLY_BRACKET
%token R_CURLY_BRACKET
%token L_SQUARE_BRACKET
%token R_SQUARE_BRACKET
%token TERNARY_CONDITIONAL
%token NUMBER_SIGN
%token POINTER
%token PRINTF 
%token SCANF 
%token DEFINE 
%token EXIT
%token NUM_HEXA 
%token NUM_OCTAL
%token NUM_INTEGER
%token IDENTIFIER
%token CHARACTER
%token STRING
%token UNTERMINATED_COMMENT
%token IDENTIFIER_TOO_LONG
%token END_OF_FILE
%token OTHER

%start exec
%%
exec: 
    program exec END_OF_FILE {printf("SUCCESSFUL COMPILATION."); return 0;}
	| program END_OF_FILE {printf("SUCCESSFUL COMPILATION."); return 0;}
;
program: 
    declaracao {}
	| funcao {}
;
declaracao: 
    NUMBER_SIGN DEFINE IDENTIFIER expressao {}
    | declaracaoVar {}
    | declaracaoEnd {}
;
funcao: 
    tipo pointer IDENTIFIER parametros L_CURLY_BRACKET decVarFunc comandos R_CURLY_BRACKET {}
;
decVarFunc: 
    declaracaoVar decVarFunc	{}
	| {}
;
declaracaoVar: 
    tipo decVar SEMICOLON {}
;
decVar: 
    pointer IDENTIFIER array ASSIGN atribuicao decVarAux {}
    | pointer IDENTIFIER array decVarAux {}
;
decVarAux: 
    COMMA decVar {}
    | {}
;
declaracaoEnd: 
    tipo pointer IDENTIFIER parametros SEMICOLON {}
;
parametros: 
    L_PAREN param R_PAREN {}
	| L_PAREN R_PAREN {}
;
param: 
    tipo pointer IDENTIFIER array paramAux	{}
;
paramAux: 
    COMMA param	{}
	| {}
;
array: 
    L_SQUARE_BRACKET expressao R_SQUARE_BRACKET array {}
	 | {}
;
tipo: 
    INT {}
	| CHAR {}
	| VOID {}
;
bloco: 
    L_CURLY_BRACKET comandos R_CURLY_BRACKET {}
;
comandos: 
    listaComandos comandos	{}
	| listaComandos {}
;
listaComandos: 
    DO bloco WHILE L_PAREN expressao R_PAREN SEMICOLON {}
	| IF L_PAREN expressao R_PAREN bloco elseExp	{}
	| WHILE L_PAREN expressao R_PAREN bloco {}
	| FOR L_PAREN opcional SEMICOLON opcional SEMICOLON opcional R_PAREN bloco {}
    | PRINTF L_PAREN STRING printfExp R_PAREN SEMICOLON {}
	| SCANF L_PAREN STRING COMMA BITWISE_AND IDENTIFIER R_PAREN SEMICOLON {}
    | EXIT L_PAREN expressao R_PAREN SEMICOLON {}
	| RETURN opcional SEMICOLON {}
	| expressao SEMICOLON {}
	| SEMICOLON {}
	| bloco	{}
;
printfExp: 
    COMMA expressao	{}
	| {}
;
elseExp: 
    ELSE bloco {}
	| {}
;
opcional: 
    expressao {}
	| {}
;
expressao: 
    atribuicao {}
    | atribuicao COMMA expressao {}
;
atribuicao: 
    cond {}
    | unaria atribuicaoAux atribuicao {}
;
atribuicaoAux: 
    ASSIGN {}
	| ADD_ASSIGN {}
	| MINUS_ASSIGN {}
;
cond: 
    orLogic {}
    | orLogic TERNARY_CONDITIONAL expressao COLON cond {}
;
orLogic: 
    andLogic {}
    | andLogic LOGICAL_OR orLogic {}
;
andLogic: 
    or {}
    | or LOGICAL_AND andLogic {}
;
or: 
    xor {}
    | xor BITWISE_OR or {}
;
xor: 
    and {}
    | and BITWISE_XOR xor {}
;
and: 
    igualdade {}
    | igualdade BITWISE_AND and {}
;
igualdade: 
    relacional {}
    | relacional igualdadeAux igualdade {}
;
igualdadeAux: 
    EQUAL {}
	| NOT_EQUAL {}
;
relacional: 
    shift {}
	| shift relacionalAux relacional {}
;
relacionalAux: 
    LESS_THAN {}
	| LESS_EQUAL {}
	| GREATER_THAN {}
	| GREATER_EQUAL {}
;
shift: 
    add {}
	| add shiftAux shift {}
;
shiftAux: 
    L_SHIFT {}
	| R_SHIFT {}
;
add: 
    mult {}
	| mult addAux add {}
;
addAux: 
    PLUS {}
	| MINUS {}
;
mult: 
    cast {}
	| cast multAux mult {}
;
multAux: 
    MULTIPLY {}
	| DIV {}
	| REMAINDER {}
;
cast: 
    unaria {}
	| L_PAREN tipo pointer R_PAREN cast {}
;
unaria: 
    posfixa	{}
	| INC unaria {}
	| DEC unaria {}
	| unAux cast {}
;
unAux: 
    BITWISE_AND {}
	| PLUS {}
	| MINUS {}
	| BITWISE_NOT {}
	| NOT {}
;
posfixa: 
    prim {}
	| posfixa INC {}
	| posfixa DEC {}
	| posfixa L_SQUARE_BRACKET expressao R_SQUARE_BRACKET {}
	| posfixa L_PAREN R_PAREN	{}
	| posfixa L_PAREN atribuicao pfAux R_PAREN {}
;
pfAux: 
    COMMA atribuicao pfAux	{}
	| {}
;
prim: 
    IDENTIFIER {}
	| num {}
	| CHARACTER {}
	| STRING {}
	| L_PAREN expressao R_PAREN {}
;
num: 
    NUM_INTEGER	{}
    | NUM_HEXA {}
    | NUM_OCTAL {}
;
pointer: 
    MULTIPLY pointer {}
    | {}
;
%%

void printfLin(FILE* input, int n){
	int i = 1;
	char c;
	fseek(input, 0, SEEK_SET);
	while(i < n) {
		c = fgetc(input);
		if (c == EOF)
            break;
		else if(c == '\n')
            i++;
	}
	c = fgetc(input);
	while(c != '\n' && c != EOF){
		printf("%c", c);
		c = fgetc(input);
	}
	printf("\n");
}
void yyerror(char *s){
	int i = 1;
	switch(yychar){
		case IDENTIFIER_TOO_LONG:
			printf("error:lexical:%d:%d: identifier too long", lin, col);
			break;
		case UNTERMINATED_COMMENT:
			printf("error:lexical:%d:%d: unterminated comment", lin, col);
			break;
		case OTHER:
			col -= strlen(yytext);
			printf("error:lexical:%d:%d: %s", lin, col, yytext);
			break;
		case END_OF_FILE:
			printf("error:syntax:%d:%d: expected declaration or statement at end of input\n", lin, col);
			printfLin(input_file, lin);
			for(i; i < col; i++)
                printf(" ");
			printf("^");
			break;
		default:
			col -= strlen(yytext);
			printf("error:syntax:%d:%d: %s\n", lin, col, yytext);
			printfLin(input_file, lin);
			for(i; i < col; i++)
                printf(" ");
			printf("^");
			break;
	}
}
int main(int argc, char **argv){
	input_file = stdin;
	yyparse();
    return 0;
}