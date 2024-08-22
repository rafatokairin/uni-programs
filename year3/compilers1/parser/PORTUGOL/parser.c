#include "parser.h"
#include "utils.h"

void AL(void *cadeia, int *tk, bool *textBefore, char *input) {
    switch (*tk) {
        case ALGORITMO:
            getToken(cadeia, ALGORITMO, tk, textBefore, input);
            getToken(cadeia, ID, tk, textBefore, input);
            getToken(cadeia, PONTO_VIRGULA, tk, textBefore, input);
            BV(cadeia, tk, textBefore, input);
            PF(cadeia, tk, textBefore, input);
            BC(cadeia, tk, textBefore, input);
            getToken(cadeia, PONTO, tk, textBefore, input);
            break;
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

void PF(void *cadeia, int *tk, bool *textBefore, char *input) {
    switch (*tk) {
        case PROCEDIMENTO:
            DProc(cadeia, tk, textBefore, input);
            PF(cadeia, tk, textBefore, input);
            break;
        case FUNCAO:
            DF(cadeia, tk, textBefore, input);
            PF(cadeia, tk, textBefore, input);
            break;
        case INICIO:
            break;
        default:
            printError(cadeia);
            freeList(cadeia);
            free(input);
            exit(-2);
            break;
    }
}

void DProc(void *cadeia, int *tk, bool *textBefore, char *input) {
    switch (*tk) {
        case PROCEDIMENTO:
            getToken(cadeia, PROCEDIMENTO, tk, textBefore, input);
            getToken(cadeia, ID, tk, textBefore, input);
            Param(cadeia, tk, textBefore, input);
            getToken(cadeia, PONTO_VIRGULA, tk, textBefore, input);
            DParam(cadeia, tk, textBefore, input);
            BV(cadeia, tk, textBefore, input);
            BC(cadeia, tk, textBefore, input);
            getToken(cadeia, PONTO_VIRGULA, tk, textBefore, input);
            break;
        default:
            printError(cadeia);
            freeList(cadeia);
            free(input);
            exit(-2);
            break;
    }
}

void DF(void *cadeia, int *tk, bool *textBefore, char *input) {
    switch (*tk) {
        case FUNCAO:
            getToken(cadeia, FUNCAO, tk, textBefore, input);
            getToken(cadeia, ID, tk, textBefore, input);
            Param(cadeia, tk, textBefore, input);
            getToken(cadeia, DOIS_PONTOS, tk, textBefore, input);
            TB(cadeia, tk, textBefore, input);
            getToken(cadeia, PONTO_VIRGULA, tk, textBefore, input);
            DParam(cadeia, tk, textBefore, input);
            BV(cadeia, tk, textBefore, input);
            BC(cadeia, tk, textBefore, input);
            getToken(cadeia, PONTO_VIRGULA, tk, textBefore, input);
            break;
        default:
            printError(cadeia);
            freeList(cadeia);
            free(input);
            exit(-2);
            break;
    }
}

void Param(void *cadeia, int *tk, bool *textBefore, char *input) {
    switch (*tk) {
        case PONTO_VIRGULA:
        case DOIS_PONTOS:
            break;
        case ABRE_PARENTESES:
            getToken(cadeia, ABRE_PARENTESES, tk, textBefore, input);
            DI(cadeia, tk, textBefore, input);
            getToken(cadeia, FECHA_PARENTESES, tk, textBefore, input);
            break;
        default:
            printError(cadeia);
            freeList(cadeia);
            free(input);
            exit(-2);
            break;
    }
}

void DParam(void *cadeia, int *tk, bool *textBefore, char *input) {
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
            break;
        default:
            printError(cadeia);
            freeList(cadeia);
            free(input);
            exit(-2);
            break;
    }
}

void BV(void *cadeia, int *tk, bool *textBefore, char *input) {
    switch (*tk) {
        case PROCEDIMENTO:
        case FUNCAO:
        case INICIO:
        case EOF_TOKEN:
            break;
        case VARIAVEIS:
            getToken(cadeia, VARIAVEIS, tk, textBefore, input);
            DS(cadeia, tk, textBefore, input);
            break;
        default:
            printError(cadeia);
            freeList(cadeia);
            free(input);
            exit(-2);
            break;
    }
}

void DS(void *cadeia, int *tk, bool *textBefore, char *input) {
    switch (*tk) {
        case ID:
        case INTEIRO:
        case REAL:
        case CARACTERE:
        case LOGICO:
            DV(cadeia, tk, textBefore, input);
            DSrec(cadeia, tk, textBefore, input);
            break;
        case TIPO:
            DT(cadeia, tk, textBefore, input);
            DSrec(cadeia, tk, textBefore, input);
            break;
        default:
            printError(cadeia);
            freeList(cadeia);
            free(input);
            exit(-2);
            break;
    }
}

void DT(void *cadeia, int *tk, bool *textBefore, char *input) {
    switch (*tk) {
        case TIPO:
            getToken(cadeia, TIPO, tk, textBefore, input);
            getToken(cadeia, ID, tk, textBefore, input);
            getToken(cadeia, IGUAL, tk, textBefore, input);
            VM(cadeia, tk, textBefore, input);
            getToken(cadeia, ABRE_COLCHETE, tk, textBefore, input);
            DM(cadeia, tk, textBefore, input);
            getToken(cadeia, FECHA_COLCHETE, tk, textBefore, input);
            TB(cadeia, tk, textBefore, input);
            getToken(cadeia, PONTO_VIRGULA, tk, textBefore, input);
            break;
        default:
            printError(cadeia);
            freeList(cadeia);
            free(input);
            exit(-2);
            break;
    }
}

void DV(void *cadeia, int *tk, bool *textBefore, char *input) {
    switch (*tk) {
        case ID:
        case INTEIRO:
        case REAL:
        case CARACTERE:
        case LOGICO:
            TB(cadeia, tk, textBefore, input);
            getToken(cadeia, DOIS_PONTOS, tk, textBefore, input);
            DI(cadeia, tk, textBefore, input);
            getToken(cadeia, PONTO_VIRGULA, tk, textBefore, input);
            break;
        default:
            printError(cadeia);
            freeList(cadeia);
            free(input);
            exit(-2);
            break;
    }
}

void DI(void *cadeia, int *tk, bool *textBefore, char *input) {
    switch (*tk) {
        case ID:
            getToken(cadeia, ID, tk, textBefore, input);
            DIrec(cadeia, tk, textBefore, input);
            break;
        default:
            printError(cadeia);
            freeList(cadeia);
            free(input);
            exit(-2);
            break;
    }
}

void VM(void *cadeia, int *tk, bool *textBefore, char *input) {
    switch (*tk) {
        case VETOR:
            getToken(cadeia, VETOR, tk, textBefore, input);
            break;
        case MATRIZ:
            getToken(cadeia, MATRIZ, tk, textBefore, input);
            break;
        default:
            printError(cadeia);
            freeList(cadeia);
            free(input);
            exit(-2);
            break;
    }
}

void DM(void *cadeia, int *tk, bool *textBefore, char *input) {
    switch (*tk) {
        case NUM_INT:
            getToken(cadeia, NUM_INT, tk, textBefore, input);
            getToken(cadeia, DOIS_PONTOS, tk, textBefore, input);
            getToken(cadeia, NUM_INT, tk, textBefore, input);
            DMrec(cadeia, tk, textBefore, input);
            break;
        default:
            printError(cadeia);
            freeList(cadeia);
            free(input);
            exit(-2);
            break;
    }
}

void TB(void *cadeia, int *tk, bool *textBefore, char *input) {
    switch (*tk) {
        case ID:
            getToken(cadeia, ID, tk, textBefore, input);
            break;
        case INTEIRO:
            getToken(cadeia, INTEIRO, tk, textBefore, input);
            break;
        case REAL:
            getToken(cadeia, REAL, tk, textBefore, input);
            break;
        case CARACTERE:
            getToken(cadeia, CARACTERE, tk, textBefore, input);
            break;
        case LOGICO:
            getToken(cadeia, LOGICO, tk, textBefore, input);
            break;
        default:
            printError(cadeia);
            freeList(cadeia);
            free(input);
            exit(-2);
            break;
    }
}

void BC(void *cadeia, int *tk, bool *textBefore, char *input) {
    switch (*tk) {
        case INICIO:
            getToken(cadeia, INICIO, tk, textBefore, input);
            LC(cadeia, tk, textBefore, input);
            getToken(cadeia, FIM, tk, textBefore, input);
            break;
        default:
            printError(cadeia);
            freeList(cadeia);
            free(input);
            exit(-2);
            break;
    }
}

void LC(void *cadeia, int *tk, bool *textBefore, char *input) {
    switch (*tk) {
        case ID:
        case SE:
        case ENQUANTO:
        case PARA:
        case REPITA:
        case LEIA:
        case IMPRIMA:
            C(cadeia, tk, textBefore, input);
            getToken(cadeia, PONTO_VIRGULA, tk, textBefore, input);
            LCrec(cadeia, tk, textBefore, input);
            break;
        default:
            printError(cadeia);
            freeList(cadeia);
            free(input);
            exit(-2);
            break;
    }
}

void C(void *cadeia, int *tk, bool *textBefore, char *input) {
    switch (*tk) {
        case ID:
            getToken(cadeia, ID, tk, textBefore, input);
            Crec1(cadeia, tk, textBefore, input);
            break;
        case SE:
            getToken(cadeia, SE, tk, textBefore, input);
            E(cadeia, tk, textBefore, input);
            getToken(cadeia, ENTAO, tk, textBefore, input);
            LC(cadeia, tk, textBefore, input);
            Crec2(cadeia, tk, textBefore, input);
            break;
        case ENQUANTO:
            getToken(cadeia, ENQUANTO, tk, textBefore, input);
            E(cadeia, tk, textBefore, input);
            getToken(cadeia, FACA, tk, textBefore, input);
            LC(cadeia, tk, textBefore, input);
            getToken(cadeia, FIM, tk, textBefore, input);
            getToken(cadeia, ENQUANTO, tk, textBefore, input);
            break;
        case PARA:
            getToken(cadeia, PARA, tk, textBefore, input);
            getToken(cadeia, ID, tk, textBefore, input);
            getToken(cadeia, DE, tk, textBefore, input);
            E(cadeia, tk, textBefore, input);
            getToken(cadeia, ATE, tk, textBefore, input);
            E(cadeia, tk, textBefore, input);
            Crec3(cadeia, tk, textBefore, input);
            break;
        case REPITA:
            getToken(cadeia, REPITA, tk, textBefore, input);
            LC(cadeia, tk, textBefore, input);
            getToken(cadeia, ATE, tk, textBefore, input);
            E(cadeia, tk, textBefore, input);
            break;
        case LEIA:
            getToken(cadeia, LEIA, tk, textBefore, input);
            getToken(cadeia, ABRE_PARENTESES, tk, textBefore, input);
            V(cadeia, tk, textBefore, input);
            getToken(cadeia, FECHA_PARENTESES, tk, textBefore, input);
            break;
        case IMPRIMA:
            getToken(cadeia, IMPRIMA, tk, textBefore, input);
            getToken(cadeia, ABRE_PARENTESES, tk, textBefore, input);
            EI(cadeia, tk, textBefore, input);
            getToken(cadeia, FECHA_PARENTESES, tk, textBefore, input);
            break;
        default:
            printError(cadeia);
            freeList(cadeia);
            free(input);
            exit(-2);
            break;
    }
}

void E(void *cadeia, int *tk, bool *textBefore, char *input) {
    switch (*tk) {
        case ID:
        case NUM_INT:
        case NUM_REAL:
        case NAO:
        case VERDADEIRO:
        case FALSO:
        case STRING:
        case ABRE_PARENTESES:
        case MAIS:
        case MENOS:
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

void ES(void *cadeia, int *tk, bool *textBefore, char *input) {
    switch (*tk) {
        case ID:
        case NUM_INT:
        case NUM_REAL:
        case NAO:
        case VERDADEIRO:
        case FALSO:
        case STRING:
        case ABRE_PARENTESES:
            T(cadeia, tk, textBefore, input);
            ESrec(cadeia, tk, textBefore, input);
            break;
        case MAIS:
        case MENOS:
            OPB(cadeia, tk, textBefore, input);
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

void OPR(void *cadeia, int *tk, bool *textBefore, char *input) {
    switch (*tk) {
        case IGUAL:
            getToken(cadeia, IGUAL, tk, textBefore, input);
            break;
        case DIFERENTE:
            getToken(cadeia, DIFERENTE, tk, textBefore, input);
            break;
        case MAIOR:
            getToken(cadeia, MAIOR, tk, textBefore, input);
            break;
        case MAIOR_IGUAL:
            getToken(cadeia, MAIOR_IGUAL, tk, textBefore, input);
            break;
        case MENOR:
            getToken(cadeia, MENOR, tk, textBefore, input);
            break;
        case MENOR_IGUAL:
            getToken(cadeia, MENOR_IGUAL, tk, textBefore, input);
            break;
        default:
            printError(cadeia);
            freeList(cadeia);
            free(input);
            exit(-2);
            break;
    }
}

void OPB(void *cadeia, int *tk, bool *textBefore, char *input) {
    switch (*tk) {
        case MAIS:
            getToken(cadeia, MAIS, tk, textBefore, input);
            break;
        case MENOS:
            getToken(cadeia, MENOS, tk, textBefore, input);
            break;
        default:
            printError(cadeia);
            freeList(cadeia);
            free(input);
            exit(-2);
            break;
    }
}

void T(void *cadeia, int *tk, bool *textBefore, char *input) {
    switch (*tk) {
        case ID:
        case NUM_INT:
        case NUM_REAL:
        case NAO:
        case VERDADEIRO:
        case FALSO:
        case STRING:
        case ABRE_PARENTESES:
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

void F(void *cadeia, int *tk, bool *textBefore, char *input) {
    switch (*tk) {
        case ID:
            getToken(cadeia, ID, tk, textBefore, input);
            Frec(cadeia, tk, textBefore, input);
            break;
        case NUM_INT:
            getToken(cadeia, NUM_INT, tk, textBefore, input);
            break;
        case NUM_REAL:
            getToken(cadeia, NUM_REAL, tk, textBefore, input);
            break;
        case VERDADEIRO:
            getToken(cadeia, VERDADEIRO, tk, textBefore, input);
            break;
        case FALSO:
            getToken(cadeia, FALSO, tk, textBefore, input);
            break;
        case STRING:
            getToken(cadeia, STRING, tk, textBefore, input);
            break;
        case NAO:
            getToken(cadeia, NAO, tk, textBefore, input);
            F(cadeia, tk, textBefore, input);
            break;
        case ABRE_PARENTESES:
            getToken(cadeia, ABRE_PARENTESES, tk, textBefore, input);
            E(cadeia, tk, textBefore, input);
            getToken(cadeia, FECHA_PARENTESES, tk, textBefore, input);
            break;
        default:
            printError(cadeia);
            freeList(cadeia);
            free(input);
            exit(-2);
            break;
    }
}

void V(void *cadeia, int *tk, bool *textBefore, char *input) {
    switch (*tk) {
        case ID:
            getToken(cadeia, ID, tk, textBefore, input);
            Vrec(cadeia, tk, textBefore, input);
            break;
        default:
            printError(cadeia);
            freeList(cadeia);
            free(input);
            exit(-2);
            break;
    }
}

void EI(void *cadeia, int *tk, bool *textBefore, char *input) {
    switch (*tk) {
        case ID:
        case NUM_INT:
        case NUM_REAL:
        case NAO:
        case VERDADEIRO:
        case FALSO:
        case STRING:
        case MAIS:
        case MENOS:
        case ABRE_PARENTESES:
            E(cadeia, tk, textBefore, input);
            EIrec(cadeia, tk, textBefore, input);
            break;
        default:
            printError(cadeia);
            freeList(cadeia);
            free(input);
            exit(-2);
            break;
    }
}

void defineID(int *tk) {
    if (*tk != -1 && *tk != 1 && *tk != EOF_TOKEN) {
        if (*tk >= NUM_INT && *tk <= DIVISAO) return;            
        if (*tk >= DIFERENTE && *tk <= ATRIBUICAO) return;       
        if (*tk >= PROCEDIMENTO && *tk <= COMENT_BLOCO) return;  
        if (*tk == ALGORITMO || *tk == ATE || *tk == INICIO || *tk == IMPRIMA || *tk == FIM || *tk == FUNCAO || *tk == FACA || *tk == FALSO || *tk == VARIAVEIS || *tk == VETOR) return;
        if (*tk == VERDADEIRO || *tk == INTEIRO || *tk == REAL || *tk == REPITA || *tk == SE || *tk == SENAO || *tk == AND || *tk == ENTAO || *tk == ENQUANTO || *tk == DE || *tk == DIV) return;
        if (*tk == OU || *tk == NAO || *tk == TIPO || *tk == LEIA || *tk == LOGICO || *tk == MATRIZ || *tk == CARACTERE || *tk == PARA || *tk == PASSO || *tk == PROCEDIMENTO) return;
        *tk = ID;
    }
}