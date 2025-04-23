#include "../include/process_queue.h"
#include <stdio.h>
#include <stdbool.h>

void initialize_process_queue(PROCESS_QUEUE *pq) {
    if(pq == NULL){
        printf("Error: NULL pointer passed to initialize_process_queue.\n");
        return;
    }
    pq->front = 0;
    pq->rear = -1;
    pq->size = 0;
    pq->priority = 0;
    pq->iteration = 0;
    for (int i = 0; i < QUEUE_SIZE; i++) {
        pq->queue[i].pid = 0;
        pq->queue[i].priority = 0;
    }
}

bool pq_isFull(PROCESS_QUEUE *pq){
    return pq->size == QUEUE_SIZE;
}

bool pq_isEmpty(PROCESS_QUEUE *pq){
    return pq->size == 0;
}

PROCESS pq_peek(PROCESS_QUEUE *pq){
    if(pq_isEmpty(pq)){
        printf("Error: Attempted to peek from an empty queue.\n");
        PROCESS empty = {0,-1};
        return empty;
    }
    return pq->queue[pq->front];
}

void pq_enqueue(PROCESS_QUEUE *pq, PROCESS data){
    if(pq_isFull(pq)){
        printf("Error: Attempted to enqueue to a full queue.\n");
        return;
    }
    pq->rear = (pq->rear + 1)%QUEUE_SIZE;
    pq->queue[pq->rear] = data;
    pq->size++;
}

PROCESS pq_dequeue(PROCESS_QUEUE *pq){
    if(pq_isEmpty(pq)){
        printf("Error: Attempted to dequeue from an empty queue.\n");
        PROCESS empty = {0, -1};
        return empty;
    }
    PROCESS data = pq->queue[pq->front];
    pq->front = (pq->front + 1) % QUEUE_SIZE;
    pq->size--;
    return data;
}

void clear_queue(PROCESS_QUEUE *queue) {
    while (!pq_isEmpty(queue)) {
        pq_dequeue(queue);
    }
}