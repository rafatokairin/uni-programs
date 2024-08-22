#include "queue.h"
#include "parser.h"

void *createList() {
    List *l = calloc(1, sizeof(List));
    return l;
}

void insertNode(List *list, int value, int line, int column, char *token) {
    No *node = calloc(1, sizeof(No));
    node->value = value;
    node->line = line;
    node->column = column;
    if (value != 19 && token[0] == '/') token++;
    node->token = calloc(strlen(token) + 1, sizeof(char));
    strcpy(node->token, token);
    if (!list->head) {
        list->head = node;
    } else {
        No *aux = list->head;
        while (aux->next) {
            aux = aux->next;
        }
        aux->next = node;
    }
}

void removeNode(List *list) {
    if (!list->head) {
        return;
    } else {
        No *aux = list->head;
        list->head = aux->next;
        if (aux->token) free(aux->token);
        free(aux);
    }
}

int getNode(List *list) {
    if (!list->head) return -1;
    return list->head->value;
}

int getLine(List *list) {
    if (!list->head) return -1;
    return list->head->line;
}

int getColumn(List *list) {
    if (!list->head) return -1;
    return list->head->column;
}

char *getTokenContent(List *list) {
    if (!list->head) return NULL;
    return list->head->token;
}

void printList(List *list) {
    No *aux = list->head;
    while (aux != NULL) {
        printf("%d ", aux->value);
        aux = aux->next;
    }
    printf("\n");
}

void freeList(List *list) {
    No *aux = list->head;
    while (aux != NULL) {
        No *aux2 = aux->next;
        if (aux) {
            if (aux->token) free(aux->token);
            free(aux);
        }
        aux = aux2;
    }
    if (list) free(list);
}