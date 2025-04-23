#ifndef PROCESS_QUEUE_H
#define PROCESS_QUEUE_H
#define QUEUE_SIZE 5

#include "type_process.h"

typedef struct {
    PROCESS queue[QUEUE_SIZE];
    int front;
    int rear;
    int size;
    int priority;
    int iteration;
} PROCESS_QUEUE;

void initialize_process_queue(PROCESS_QUEUE *pq);

bool pq_isFull(PROCESS_QUEUE *pq);

bool pq_isEmpty(PROCESS_QUEUE *pq);

PROCESS pq_peek(PROCESS_QUEUE *pq);

void pq_enqueue(PROCESS_QUEUE *pq, PROCESS data);

PROCESS pq_dequeue(PROCESS_QUEUE *pq);

void clear_queue(PROCESS_QUEUE *queue);

#endif