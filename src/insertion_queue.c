#include "../include/insertion_queue.h"
#include <stdio.h>
#include <stdbool.h>

void initialize_execution_queue(INSERTION_QUEUE *iq) {
    iq->size = 0;
    iq->front = 0;
    iq->rear = -1;
}

bool iq_isFull(INSERTION_QUEUE *iq){
    return iq->size == MAX_OPERATION;
}

bool iq_isEmpty(INSERTION_QUEUE *iq){
    return iq->size == 0;
}

PROCESS_QUEUE iq_peek(INSERTION_QUEUE *iq){
    if (iq_isEmpty(iq)) {
        printf("Error: Attempted to peek from an empty queue." );
        PROCESS_QUEUE empty_queue;
        initialize_process_queue(&empty_queue);
        return empty_queue;
    }
    return iq->queue[iq->front];
}

void iq_enqueue(INSERTION_QUEUE *iq, PROCESS_QUEUE data){
    if (iq_isFull(iq)){
        printf("Error: Attempted to enqueue to a full queue.");
        return;
    }
    iq->rear = (iq->rear + 1) % MAX_OPERATION;
    iq->queue[iq->rear] = data;
    iq->size++;
}

PROCESS_QUEUE iq_dequeue(INSERTION_QUEUE *iq){
    if (iq_isEmpty(iq)) {
        printf("Error: Attempted to peek from an empty queue.");
        PROCESS_QUEUE empty_queue;
        initialize_process_queue(&empty_queue);
        return empty_queue;
    }
    PROCESS_QUEUE deleted = iq->queue[iq->front];
    iq->front = (iq->front + 1) % MAX_OPERATION;
    iq->size--;
    return deleted;
}