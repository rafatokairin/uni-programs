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

void insertNode(List *, int, int, int, char *);

void removeNode(List *);

int getNode(List *);

int getLine(List *);

int getColumn(List *);

char *getTokenContent(List *);

void printList(List *);

void freeList(List *);

#endif