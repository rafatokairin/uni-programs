#ifndef QUEUE_H
#define QUEUE_H
#include "state.h"
#include "queue.h"
#include "automata.h"

typedef void* Data;

typedef void (*freeData)(Data); 

typedef char* (*dataToString)(Data); 

typedef void* Queue;

Queue newQueue(void);

int queueSize(Queue queue);

int isQueueEmpty(Queue queue);

int queuePush(Queue queue, Data data);

Data queuePop(Queue queue);

Data queueTop(Queue queue);

void printQueue(Queue queue, dataToString function);

void freeQueue(Queue queue, freeData function);

#endif