#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

typedef struct No {
    Data data;
    struct No* next;
} No;

typedef struct {
    int size;
    No* top;
} List;

Queue newQueue(void){
    List* list = (List*) malloc(sizeof(List));
    if(list == NULL) return NULL;
    (*list).size = 0;
    (*list).top = NULL;
    return list;
}

int queueSize(Queue St){
    if(St == NULL) return -1;
    List* list = (List*) St;
    return (*list).size;
}

int isQueueEmpty(Queue St){
    if(St == NULL) return -1;
    List* list = (List*) St;
    if((*list).top == NULL) return 1;
    else return 0;
}

int queuePush(Queue St, Data data){
    if(St == NULL || data == NULL) return 0;
    List* list = (List*) St;
    No* new = (No*) malloc(sizeof(No));
    if(new == NULL) return 0;
    (*new).data = data;
    (*new).next = (*list).top;
    (*list).top = new;
    (*list).size++;
    return 1;
}

Data queuePop(Queue St){
    if(St == NULL) return NULL;
    List* list = (List*) St;
    if((*list).top == NULL) return NULL;

    No* top = (*list).top;
    (*list).top = (*top).next;

    Data popedElement = (*top).data;
    free(top);
    (*list).size--;
    return popedElement;
}

Data queueTop(Queue St){
    if(St == NULL) return NULL;
    List* list = (List*) St;
    if((*list).top == NULL) return NULL;

    return (*((*list).top)).data;
}

void printQueue(Queue St, dataToString function){
    if(St == NULL || function == NULL) return;
    List* list = (List*) St;
    char* dataString;
    printf("top-> ");
    No* current = (*list).top;
    while(current != NULL){
        if(current == (*list).top) 
            printf("%s\n", dataString = (*function)((*current).data));
        else
            printf("      %s\n", dataString = (*function)((*current).data));
        free(dataString);
        current = (*current).next;
    }
    printf("\n");
}

void freeQueue(Queue St, freeData function){
    if(St == NULL) return;
    List* list = (List*) St;
    No* current = (*list).top;
    while(current != NULL){
        if(function != NULL)
            (*function)((*current).data);
        current = (*current).next;
        free((*list).top);
        (*list).top = current;
    }
    free(list);
}