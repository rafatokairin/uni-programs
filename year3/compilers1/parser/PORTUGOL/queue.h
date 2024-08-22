#ifndef QUEUE_H
#define QUEUE_H
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    int line;
    int column;
    char *token;
    struct node *next;
} No;

typedef struct list {
    No *head;
} List;

void *createList();

void insertNode(List *list, int value, int line, int column, char *token);

void removeNode(List *list);

int getNode(List *list);

int getLine(List *list);

int getColumn(List *list);

char *getTokenContent(List *list);

void printList(List *list);

void freeList(List *list);

#endif