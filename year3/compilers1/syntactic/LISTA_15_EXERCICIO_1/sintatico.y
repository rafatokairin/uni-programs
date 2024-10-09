%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define HASH_SIZE 211
extern int yylex();
void yyerror(void *s);
extern int yychar;
extern int textAnt;
extern int eof;
int errorAux = 0;
int errorSemant = 0;
int atual;

typedef struct node {
    int key;
    char *value;
    struct node *next;
} HashNode;

int hash();
void insereHash();
int searchHash();
void freeHash();
void **hashTab = NULL;

%}
%union {
    struct {
        char *valor;
        int column;
        int line;
    } token;
}
%token EOL
%token COMMA
%token INT
%token CHAR
%token FLOAT
%token ID
%start S

%%
S: D D_Prime EOL { errorAux = 0; return 0; }
    | error { errorAux = 1; return 0; } ;

D_Prime: D D_Prime { }
    | { } ;

D: T I { } ;

T: INT { atual = INT; }
    | CHAR { atual = CHAR; }
    | FLOAT { atual = FLOAT; } ;

I: ID { 
    // printf(">> %d %s\n\n", atual, yylval.token.valor);
    if (!searchHash())
        insereHash(); 
}
    | I COMMA ID { 
        // printf("-> %d %s\n\n", atual, yylval.token.valor);
        if (!searchHash())
            insereHash(); 
} ;

%%
void yyerror(void *s) {}

int hash() {
    int hash = 0;
    for (int i = 0; i < strlen(yylval.token.valor); i++)
        hash += yylval.token.valor[i];
    return hash % HASH_SIZE;
}

void insereHash() {
    int index = hash(yylval.token.valor);
    HashNode *aux = calloc(1, sizeof(HashNode));
    aux->key = atual;
    aux->value = calloc(strlen(yylval.token.valor) + 1, sizeof(char));
    strcpy(aux->value, yylval.token.valor);
    HashNode *head = (HashNode *) hashTab[index];
    if (!head) {
        hashTab[index] = aux;
    } else {
        while (head->next) 
            head = head->next;
        head->next = aux;
    }
}

int searchHash() {
    if (!hashTab) return 0;
    int index = hash(yylval.token.valor);
    int ocorrencias = 0;
    HashNode *head = (HashNode *) hashTab[index];
    while (head) {
        if (!strcmp(yylval.token.valor, head->value)) { // existe outro daquele identificador na hash
            ocorrencias++;
            if (ocorrencias == 1) continue;  // se for o primeiro, continua 
            if (atual == head->key) {  // se for do mesmo tipo
                if (textAnt) printf("\n");
                printf("%d: identifier '%s' already declared", yylval.token.line, yylval.token.valor);
                errorSemant = 1;
                textAnt = 1;
                return 1;
            } else {  // se for de tipo diferente
                if (textAnt) printf("\n");
                printf("%d: redefinition of identifier '%s'", yylval.token.line, yylval.token.valor);
                errorSemant = 1;
                textAnt = 1;
                return 1;
            }
        }
        head = head->next;
    }
    return 0;
}

void freeHash() {
    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode *head = hashTab[i];
        while (head) {
            HashNode *aux = head->next;
            if (head->value) 
                free(head->value);
            free(head);
            head = aux;
        }
        hashTab[i] = NULL; 
    }
}

int main(int argc, char *argv[]) {
    hashTab = calloc(HASH_SIZE, sizeof(HashNode));
    while (!eof) {
        yyparse();
        if (yychar == 0) break;
        if (errorSemant == 0) {
            if (textAnt) printf("\n");
            printf("%d: All Identifiers on Hash.", yylval.token.line);
            textAnt = 1;
            freeHash();
        } else {
            errorSemant = 0;
            freeHash();
        }        
    }
    if (hashTab) {
        freeHash(hashTab);
        free(hashTab);
    }
    return 0;
}