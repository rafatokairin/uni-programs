#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "state.h"
#include "queue.h"
#include "automata.h"
#include "parser.h"

typedef void (*Top)(void); 
Queue queue;
int token;
int isFirstPrinting = 1;

typedef enum parsingStatus {
   ACCEPTED,
   REJECTED
} parsingStatus;

parsingStatus status;

void cleanQueue(){
    while(queueTop(queue) != NULL){
        Data top = queuePop(queue);
        if(top != E && top != Ef && top != T && top != Tf && top != F && top != S)
            free(top);
    }
}

char* getToken(int tokenType){
    switch (tokenType){
        case DOLLAR:
            return " $ ";
        case PLUS:
            return " + ";
        case TIMES:
            return " * ";
        case L_PAREN:
            return " ( ";
        case R_PAREN:
            return " ) ";
        case ID:
            return " id ";
        default:
            return " ";
    }
}

void printNewLine(){
    if(!isFirstPrinting) printf("\n");
    else isFirstPrinting = 0;
}

void printLexicalError(char character){
    printNewLine();
    printf("ERRO LEXICO: %c", character);
    status = REJECTED;
}

void printSyntaxError(int readToken, char* expectedToken){
    printNewLine();
    printf("ERRO SINTATICO EM:%sESPERADO: %s", getToken(readToken), expectedToken);
    status = REJECTED;
}

void ignoreString(){
    while(token != NEW_LINE && token != EOF_TOKEN)
        token = getNextToken();
}

void advance() {
    token=getNextToken();
}

int getProduction(char nonT, int T){
    switch(nonT){
        case 'S':
        case 'E':
        case 'T':
            if (T == ID || T == L_PAREN) return 0;
            return -1;
        case 'e':
            if (T == PLUS) return 0;
            if (T == R_PAREN || T == DOLLAR) return 1;
            return -1;
        case 't':
            if (T == TIMES) return 0;
            if (T == PLUS || T == R_PAREN || T == DOLLAR) return 1;
            return -1;
        case 'F':
            if(T == ID) return 0; 
            if(T == L_PAREN) return 1;
            return -1;
    }
}

int match(){
    int* top = (int*) queueTop(queue);
    while(*top == token){
        queuePop(queue);
        free(top);
        advance();
        top = (int*) queueTop(queue);
        if(top == NULL) return 1;
    }
    if (*top >= DOLLAR && *top <= ID)
        return 0;
    return 1;
}

void derive(int matchWasSuccessful){
    if(matchWasSuccessful){
        Top top = queueTop(queue);
        if(top != NULL)
            (*top)();

    }else{ 
        int* top = (int*) queueTop(queue);
        char* tokenName = getToken(*top);
        int tokenNameLen = strlen(tokenName);
        char tName[10];
        sprintf(tName, "%s", &tokenName[1]);
        tName[tokenNameLen-2] = '\0';
        printSyntaxError(token, tName);
        ignoreString();
    }
}

void queuePushToken(int token) {
    int* t = (int*) malloc(sizeof(int));
    *t = token;
    queuePush(queue, t);
}

void S(){
    if (token > EOF_TOKEN){ 
        printLexicalError(token);
        ignoreString();
        return;
    } 
    if (token == NEW_LINE || token == EOF_TOKEN){ 
        printSyntaxError(-1, "id, (");
        return;
    }
    int action = getProduction('S', token);
    switch(action) {
        case 0:
            queuePop(queue);
            queuePushToken(DOLLAR);            
            queuePush(queue, E);
            break;
        default:
            printSyntaxError(token, "id, (");
            ignoreString();
            return;
    }
    int matchWasSuccessful = match();
    derive(matchWasSuccessful);
}

void E(){
    if (token > EOF_TOKEN){ 
        printLexicalError(token);
        ignoreString();
        return;
    }
    if (token == NEW_LINE || token == EOF_TOKEN){
        printSyntaxError(-1, "id, (");
        return;
    }
    int action = getProduction('E', token);
    switch(action) {
        case 0:
            queuePop(queue);
            queuePush(queue, Ef);
            queuePush(queue, T);
            break;
        default:
            printSyntaxError(token, "id, (");
            ignoreString();
            return;
    }
    int matchWasSuccessful = match();
    derive(matchWasSuccessful);
}

void Ef(){
    if (token > EOF_TOKEN){ 
        printLexicalError(token);
        ignoreString();
        return;
    }
    if (token == NEW_LINE || token == EOF_TOKEN){
        printSyntaxError(-1, "+, ), $");
        return;
    }
    int action = getProduction('e', token);
    switch(action) {
        case 0:
            queuePop(queue);
            queuePush(queue, Ef);
            queuePush(queue, T);
            queuePushToken(PLUS);
            break;
        case 1:
            queuePop(queue);
            break;
        default:
            printSyntaxError(token, "+, ), $");
            ignoreString();
            return;
    }
    int matchWasSuccessful = match();
    derive(matchWasSuccessful);
}

void T(){
    if (token > EOF_TOKEN){ 
        printLexicalError(token);
        ignoreString();
        return;
    }
    if (token == NEW_LINE || token == EOF_TOKEN){
        printSyntaxError(-1, "id, (");
        return;
    }
    int action = getProduction('T', token);
    switch(action) {
        case 0:
            queuePop(queue);
            queuePush(queue, Tf);
            queuePush(queue, F);
            break;
        default:
            printSyntaxError(token, "id, (");
            ignoreString();
            return;
    }
    int matchWasSuccessful = match();
    derive(matchWasSuccessful);
}

void Tf(){
    if (token > EOF_TOKEN){ 
        printLexicalError(token);
        ignoreString();
        return;
    }
    if (token == NEW_LINE || token == EOF_TOKEN){
        printSyntaxError(-1, "+, *, ), $");
        return;
    }
    int action = getProduction('t', token);
    switch(action) {
        case 0:
            queuePop(queue);
            queuePush(queue, Tf);
            queuePush(queue, F);
            queuePushToken(TIMES);
            break;
        case 1:
            queuePop(queue);
            break;
        default:
            printSyntaxError(token, "+, *, ), $");
            ignoreString();
            return;
    }
    int matchWasSuccessful = match();
    derive(matchWasSuccessful);
}

void F(){
    if (token > EOF_TOKEN){ 
        printLexicalError(token);
        ignoreString();
        return;
    }
    if (token == NEW_LINE || token == EOF_TOKEN){
        printSyntaxError(-1, "id, (");
        return;
    }
    int action = getProduction('F', token);
    switch(action) {
        case 0:
            queuePop(queue);
            queuePushToken(ID);
            break;
        case 1:
            queuePop(queue);
            queuePushToken(R_PAREN);
            queuePush(queue, E);
            queuePushToken(L_PAREN);
            break;
        default:
            printSyntaxError(token, "id, (");
            ignoreString();
            return;
    }
    int matchWasSuccessful = match();
    derive(matchWasSuccessful);
}

int parse(){
    queue = newQueue();
    token = getNextToken();
    
    while(token != EOF_TOKEN){ 
        status = ACCEPTED;
        queuePush(queue, S);
        S();

        if(token == NEW_LINE || token == EOF_TOKEN)
            token = getNextToken(); 
        else{ 
            while(token != NEW_LINE && token != EOF_TOKEN){
                if(token > EOF_TOKEN){
                    printLexicalError(token);
                    ignoreString();
                    token = getNextToken(); 
                    break;
                }
                token = getNextToken();
            }
        }

        if(status == ACCEPTED){
            printNewLine();
            printf("CADEIA ACEITA");
        }
        cleanQueue();
    }
    freeQueue(queue, NULL);
}