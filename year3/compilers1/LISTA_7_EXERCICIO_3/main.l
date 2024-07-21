%option noyywrap

%%
"aba"+ printf("(%s) (action 1)\n", yytext);
"a"[b]*"a" printf("(%s) (action 2)\n", yytext);
"a"|"b" printf("(%s) (action 3)\n", yytext);
[\n]
. printf("ERRO\n");
%%

int main(int argc, char **argv){
	yylex();
	return 0;
}