#ifndef INSERTION_QUEUE_H
#define INSERTION_QUEUE_H
#define MAX_OPERATION 10

#include "process_queue.h"

typedef struct {
    PROCESS_QUEUE queue[MAX_OPERATION];
    int front;
    int rear;
    int size;
} INSERTION_QUEUE;

void initialize_execution_queue(INSERTION_QUEUE *iq);

bool iq_isFull(INSERTION_QUEUE *iq);

bool iq_isEmpty(INSERTION_QUEUE *iq);

PROCESS_QUEUE iq_peek(INSERTION_QUEUE *iq);

void iq_enqueue(INSERTION_QUEUE *iq, PROCESS_QUEUE data);

PROCESS_QUEUE iq_dequeue(INSERTION_QUEUE *iq);

#endif