#include "parser.h"
#include "automata.h"
#include "utils.h"
#include "state.h"
#include <stdio.h>
#include <stdlib.h>

void eat(void *cadeia, bool *textBefore, char *input) {
    int tk = getNode(cadeia);
    if (tk == -1) {
        printResult("ERRO LISTA VAZIA", textBefore); 
        exit(0);
    }
    defineID(&tk);
    Start(cadeia, &tk, textBefore, input);  
}

void getToken(void *cadeia, int tokenAnalisado, int *tk, bool *textBefore, char *input) {
    if (tokenAnalisado == *tk) { 
        removeNode(cadeia);
        *tk = getNode(cadeia);
        defineID(tk);
    } else {
        int column = getColumn(cadeia) - strlen(getTokenContent(cadeia)) + 1;
        printf("ERRO DE SINTAXE. Linha: %d Coluna: %d -> '%s'", getLine(cadeia), column, getTokenContent(cadeia));
        freeList(cadeia);
        free(input);
        exit(-2);
    }
}

void printError(void *cadeia) {
    int column = getColumn(cadeia) - strlen(getTokenContent(cadeia)) + 1;
    printf("ERRO DE SINTAXE. Linha: %d Coluna: %d -> '%s'", getLine(cadeia), column, getTokenContent(cadeia));
}

void printResult(char *result, bool *textBefore) {
    if (!result) return;
    if (*textBefore) printf("\n");
    printf("%s", result);
    *textBefore = true;
}

void Start(void *cadeia, int *tk, bool *textBefore, char *input) {
    switch (*tk) {
        case ALGORITMO:
            AL(cadeia, tk, textBefore, input);
            getToken(cadeia, EOF_TOKEN, tk, textBefore, input);
            break;
        default:
            printError(cadeia);
            freeList(cadeia);
            free(input);
            exit(-2);
            break;
    }
}

void DSrec(void *cadeia, int *tk, bool *textBefore, char *input) {
    switch (*tk) {
        case ID:
        case TIPO:
        case INTEIRO:
        case REAL:
        case CARACTERE:
        case LOGICO:
            DS(cadeia, tk, textBefore, input);
            break;
        case PROCEDIMENTO:
        case FUNCAO:
        case VARIAVEIS:
        case INICIO:
        case EOF_TOKEN:
            break;
        default:
            printError(cadeia);
            freeList(cadeia);
            free(input);
            exit(-2);
            break;
    }
}

void DIrec(void *cadeia, int *tk, bool *textBefore, char *input) {
    switch (*tk) {
        case PONTO_VIRGULA:
        case FECHA_PARENTESES:
            break;
        case VIRGULA:
            getToken(cadeia, VIRGULA, tk, textBefore, input);
            DI(cadeia, tk, textBefore, input);
            break;
        default:
            printError(cadeia);
            freeList(cadeia);
            free(input);
            exit(-2);
            break;
    }
}

void DMrec(void *cadeia, int *tk, bool *textBefore, char *input) {
    switch (*tk) {
        case FECHA_COLCHETE:
            break;
        case VIRGULA:
            getToken(cadeia, VIRGULA, tk, textBefore, input);
            DM(cadeia, tk, textBefore, input);
            break;
        default:
            printError(cadeia);
            freeList(cadeia);
            free(input);
            exit(-2);
            break;
    }
}

void LCrec(void *cadeia, int *tk, bool *textBefore, char *input) {
    switch (*tk) {
        case ID:
        case SE:
        case ENQUANTO:
        case PARA:
        case REPITA:
        case LEIA:
        case IMPRIMA:
            LC(cadeia, tk, textBefore, input);
            break;
        case FIM:
        case SENAO:
        case ATE:
            break;
        default:
            printError(cadeia);
            freeList(cadeia);
            free(input);
            exit(-2);
            break;
    }
}

void Crec1(void *cadeia, int *tk, bool *textBefore, char *input) {
    switch (*tk) {
        case PONTO_VIRGULA:
            break;
        case ABRE_PARENTESES:
            getToken(cadeia, ABRE_PARENTESES, tk, textBefore, input);
            EI(cadeia, tk, textBefore, input);
            getToken(cadeia, FECHA_PARENTESES, tk, textBefore, input);
            break;
        case ABRE_COLCHETE:
            getToken(cadeia, ABRE_COLCHETE, tk, textBefore, input);
            EI(cadeia, tk, textBefore, input);
            getToken(cadeia, FECHA_COLCHETE, tk, textBefore, input);
            getToken(cadeia, ATRIBUICAO, tk, textBefore, input);
            E(cadeia, tk, textBefore, input);
            break;
        case ATRIBUICAO:
            getToken(cadeia, ATRIBUICAO, tk, textBefore, input);
            E(cadeia, tk, textBefore, input);
            break;
        default:
            printError(cadeia);
            freeList(cadeia);
            free(input);
            exit(-2);
            break;
    }
}

void Crec2(void *cadeia, int *tk, bool *textBefore, char *input) {
    switch (*tk) {
        case FIM:
            getToken(cadeia, FIM, tk, textBefore, input);
            getToken(cadeia, SE, tk, textBefore, input);
            break;
        case SENAO:
            getToken(cadeia, SENAO, tk, textBefore, input);
            LC(cadeia, tk, textBefore, input);
            getToken(cadeia, FIM, tk, textBefore, input);
            getToken(cadeia, SE, tk, textBefore, input);
            break;
        default:
            printError(cadeia);
            freeList(cadeia);
            free(input);
            exit(-2);
            break;
    }
}

void Crec3(void *cadeia, int *tk, bool *textBefore, char *input) {
    switch (*tk) {
        case FACA:
            getToken(cadeia, FACA, tk, textBefore, input);
            LC(cadeia, tk, textBefore, input);
            getToken(cadeia, FIM, tk, textBefore, input);
            getToken(cadeia, PARA, tk, textBefore, input);
            break;
        case PASSO:
            getToken(cadeia, PASSO, tk, textBefore, input);
            E(cadeia, tk, textBefore, input);
            getToken(cadeia, FACA, tk, textBefore, input);
            LC(cadeia, tk, textBefore, input);
            getToken(cadeia, FIM, tk, textBefore, input);
            getToken(cadeia, PARA, tk, textBefore, input);
            break;
        default:
            printError(cadeia);
            freeList(cadeia);
            free(input);
            exit(-2);
            break;
    }
}

void Erec(void *cadeia, int *tk, bool *textBefore, char *input) {
    switch (*tk) {
        case PONTO_VIRGULA:
        case FECHA_PARENTESES:
        case FECHA_COLCHETE:
        case VIRGULA:
        case ENTAO:
        case FACA:
        case ATE:
        case PASSO:
            break;
        case IGUAL:
        case DIFERENTE:
        case MENOR:
        case MENOR_IGUAL:
        case MAIOR:
        case MAIOR_IGUAL:
            OPR(cadeia, tk, textBefore, input);
            ES(cadeia, tk, textBefore, input);
            Erec(cadeia, tk, textBefore, input);
            break;
        default:
            printError(cadeia);
            freeList(cadeia);
            free(input);
            exit(-2);
            break;
    }
}

void ESrec(void *cadeia, int *tk, bool *textBefore, char *input) {
    switch (*tk) {
        case PONTO_VIRGULA:
        case FECHA_PARENTESES:
        case FECHA_COLCHETE:
        case VIRGULA:
        case IGUAL:
        case DIFERENTE:
        case MENOR:
        case MENOR_IGUAL:
        case MAIOR:
        case MAIOR_IGUAL:
        case ENTAO:
        case FACA:
        case ATE:
        case PASSO:
            break;
        case MAIS:
        case MENOS:
            OPB(cadeia, tk, textBefore, input);
            T(cadeia, tk, textBefore, input);
            ESrec(cadeia, tk, textBefore, input);
            break;
        case OU:
            getToken(cadeia, OU, tk, textBefore, input);
            T(cadeia, tk, textBefore, input);
            ESrec(cadeia, tk, textBefore, input);
            break;
        default:
            printError(cadeia);
            freeList(cadeia);
            free(input);
            exit(-2);
            break;
    }
}

void Trec(void *cadeia, int *tk, bool *textBefore, char *input) {
    switch (*tk) {
        case PONTO_VIRGULA:
        case FECHA_PARENTESES:
        case FECHA_COLCHETE:
        case VIRGULA:
        case IGUAL:
        case DIFERENTE:
        case MAIOR:
        case MAIOR_IGUAL:
        case MENOR:
        case MENOR_IGUAL:
        case MAIS:
        case MENOS:
        case OU:
        case ENTAO:
        case FACA:
        case ATE:
        case PASSO:
            break;
        case VEZES:
            getToken(cadeia, VEZES, tk, textBefore, input);
            F(cadeia, tk, textBefore, input);
            Trec(cadeia, tk, textBefore, input);
            break;
        case DIVISAO:
            getToken(cadeia, DIVISAO, tk, textBefore, input);
            F(cadeia, tk, textBefore, input);
            Trec(cadeia, tk, textBefore, input);
            break;
        case DIV:
            getToken(cadeia, DIV, tk, textBefore, input);
            F(cadeia, tk, textBefore, input);
            Trec(cadeia, tk, textBefore, input);
            break;
        case AND:
            getToken(cadeia, AND, tk, textBefore, input);
            F(cadeia, tk, textBefore, input);
            Trec(cadeia, tk, textBefore, input);
            break;
        default:
            printError(cadeia);
            freeList(cadeia);
            free(input);
            exit(-2);
            break;
    }
}

void Frec(void *cadeia, int *tk, bool *textBefore, char *input) {
    switch (*tk) {
        case PONTO_VIRGULA:
        case FECHA_PARENTESES:
        case FECHA_COLCHETE:
        case VIRGULA:
        case IGUAL:
        case DIFERENTE:
        case MAIOR:
        case MAIOR_IGUAL:
        case MENOR:
        case MENOR_IGUAL:
        case MAIS:
        case MENOS:
        case OU:
        case VEZES:
        case DIVISAO:
        case DIV:
        case AND:
        case ENTAO:
        case FACA:
        case ATE:
        case PASSO:
            break;
        case ABRE_PARENTESES:
            getToken(cadeia, ABRE_PARENTESES, tk, textBefore, input);
            EI(cadeia, tk, textBefore, input);
            getToken(cadeia, FECHA_PARENTESES, tk, textBefore, input);
            break;
        case ABRE_COLCHETE:
            getToken(cadeia, ABRE_COLCHETE, tk, textBefore, input);
            EI(cadeia, tk, textBefore, input);
            getToken(cadeia, FECHA_COLCHETE, tk, textBefore, input);
            break;
        default:
            printError(cadeia);
            freeList(cadeia);
            free(input);
            exit(-2);
            break;
    }
}

void Vrec(void *cadeia, int *tk, bool *textBefore, char *input) {
    switch (*tk) {
        case FECHA_PARENTESES:
            break;
        case ABRE_COLCHETE:
            getToken(cadeia, ABRE_COLCHETE, tk, textBefore, input);
            EI(cadeia, tk, textBefore, input);
            getToken(cadeia, FECHA_COLCHETE, tk, textBefore, input);
            break;
        default:
            printError(cadeia);
            freeList(cadeia);
            free(input);
            exit(-2);
            break;
    }
}

void EIrec(void *cadeia, int *tk, bool *textBefore, char *input) {
    switch (*tk) {
        case FECHA_PARENTESES:
        case FECHA_COLCHETE:
            break;
        case VIRGULA:
            getToken(cadeia, VIRGULA, tk, textBefore, input);
            EI(cadeia, tk, textBefore, input);
            break;
        default:
            printError(cadeia);
            freeList(cadeia);
            free(input);
            exit(-2);
            break;
    }
}

void parse() {
    bool textBefore = false;
    char *input = calloc(131072, sizeof(char));
    bool firstLine = true;
    bool flagLexico = false;
    bool inMultiLineComment = false;
    int lineno = 0;
    int index;
    void *cadeia = createList();
    char *tokenContents = calloc(200, sizeof(char));
    int column = 0;

    while (fgets(input, 131072, stdin) != NULL) {
        int currentState;
        index = 0;
        int backupIndex;
        int end;
        bool acceptedAsFinal;
        lineno++;

        if (!inMultiLineComment) {
            currentState = 1;       
            backupIndex = 0;         
            acceptedAsFinal = true;  
            end = -1;                
            if (firstLine) {
                flagLexico = false;
            }
            char *isThereComment = strchr(input, '{');
            if (isThereComment) inMultiLineComment = true;
        }
        if (input[strlen(input) - 1] == 10 && inMultiLineComment) {
            input[strlen(input) - 1] = '\0';
        }
        if (inMultiLineComment) {
            char *isThereComment = strchr(input, '}');
            if (isThereComment) {
                inMultiLineComment = false;
            }
        }

        while (input[index] != '\0') {
            int currentCharIndex = charmapColumn(input[index]);
            if (currentCharIndex == -1) {
                if (end == -1) {
                    if (index == 0) {
                        printErroLexico(cadeia, input, lineno, index, &textBefore, &flagLexico, tokenContents);
                        resetVariables(&index, (index + 1), &backupIndex, &end, &currentState);
                        continue;
                    }

                    resetVariables(&index, (backupIndex + 1), &backupIndex, &end, &currentState);
                    printErroLexico(cadeia, input, lineno, index - 1, &textBefore, &flagLexico, tokenContents);
                    continue;
                }
                if (end != currentState) { 
                    index = backupIndex;
                    backupIndex = index;
                }
                if (end != -1) {                                      
                    if (end != COMENT_LINHA && end != COMENT_BLOCO) {  
                        insertNode(cadeia, end, lineno, index, tokenContents);
                        free(tokenContents);
                        column = 0;
                        tokenContents = calloc(200, sizeof(char));
                    }
                    inMultiLineComment = false;
                }
                resetVariables(&index, (index + 1), &backupIndex, &end, &currentState);
                printErroLexico(cadeia, input, lineno, index - 1, &textBefore, &flagLexico, tokenContents);
                continue;
            }
            int nextState = edges[currentState - 1][currentCharIndex];
            if (nextState == 0) {
                if (end == -1) {                                                                             
                    printErroLexico(cadeia, input, lineno, index, &textBefore, &flagLexico, tokenContents);  
                    resetVariables(&index, (backupIndex + 1), &backupIndex, &end, &currentState);
                    continue;
                }
                if (end != -1) { 
                    if (end != COMENT_LINHA && end != COMENT_BLOCO) {
                        insertNode(cadeia, end, lineno, index, tokenContents);
                        free(tokenContents);
                        column = 0;
                        tokenContents = calloc(200, sizeof(char));
                    }
                    backupIndex = index;
                    inMultiLineComment = false;
                }
                if (currentState != end) { 
                    index = backupIndex - 1;
                    backupIndex = index;
                }
                end = -1;
                currentState = 1;
                continue;
            }
            currentState = nextState;                             
            acceptedAsFinal = isFinal(currentState); 
            if (acceptedAsFinal) {
                if (currentState != 166 && currentState != 169 && currentState != 170) {
                    tokenContents[column] = input[index];
                    column++;
                }
                end = currentState;
            }
            if (currentState == 167) { 
                tokenContents[column] = input[index];
                column++;
            }
            index++;
            if (acceptedAsFinal) {
                backupIndex = index;
            }
        }
        if (input[index] == 0) continue;
        if (end == currentState) {
            backupIndex = index;
            if (end != COMENT_LINHA && end != COMENT_BLOCO) {
                insertNode(cadeia, end, lineno, index, tokenContents);
                free(tokenContents);
                column = 0;
                tokenContents = calloc(200, sizeof(char));
            }
            inMultiLineComment = false;

        } else {  
            if (input[backupIndex] == 0) continue;
            printErroLexico(cadeia, input, lineno, backupIndex, &textBefore, &flagLexico, tokenContents);
            resetVariables(&index, (backupIndex + 1), &backupIndex, &end, &currentState);
        }
        if (!inMultiLineComment) {
            flagLexico = false;
        }
    }
    free(tokenContents);
    if (!inMultiLineComment) {
        if (!flagLexico) {
            if (getNode(cadeia) != -1) {
                insertNode(cadeia, EOF_TOKEN, lineno, index, "$"); 
                eat(cadeia, &textBefore, input);
            }
        }
        flagLexico = false;
        freeList(cadeia);
    }
    free(input);
    printf("PROGRAMA CORRETO."); 
}