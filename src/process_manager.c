#include "../include/process_manager.h"
#include <stdio.h>
#include <stdbool.h>

void initialize_process_manager(PROCESS_MANAGER *pm){
    pm->front = 0;
    pm->rear = -1;
    pm -> size = 0;
}

bool pm_isFull(PROCESS_MANAGER *pm){
    return pm->size == MAX_PROCESS;
}

bool pm_isEmpty(PROCESS_MANAGER *pm){
    return pm->size == 0;
}

// commit comments

void insert_front(PROCESS_MANAGER *pm, PROCESS_QUEUE pq){
    if (pm_isFull(pm)) {
        printf("Error: Process manager is full. Cannot insert at front.");
        return;
    }
    if(pm->front == -1){
        pm->front = 0;
    }else{
        pm->front = (pm->front - 1 + MAX_PROCESS) % MAX_PROCESS;
    }
    pm->deque[pm->front] = pq;
    pm->size++;
}

void insert_rear(PROCESS_MANAGER *pm, PROCESS_QUEUE pq){
    if (pm_isFull(pm)) {
        printf("Error: Process manager is full. Cannot insert at front.");
        return;
    }
    pm->rear = (pm->rear + 1) % MAX_PROCESS;
    pm->deque[pm->rear] = pq;
    pm->size++;
}

PROCESS_QUEUE delete_front(PROCESS_MANAGER *pm){
    if (pm_isEmpty(pm)) {
        printf("Error: Cannot delete from an empty process manager.");
        PROCESS_QUEUE empty_queue;
        initialize_process_queue(&empty_queue);
        return empty_queue;
    }
    PROCESS_QUEUE deleted = pm->deque[pm->front];
    pm->front = (pm->front + 1) % MAX_PROCESS;
    pm->size--;
    return deleted;
}

PROCESS_QUEUE delete_rear(PROCESS_MANAGER *pm){
    if (pm_isEmpty(pm)) {
        printf("Error: Cannot delete from an empty process manager.");
        PROCESS_QUEUE empty_queue;
        initialize_process_queue(&empty_queue);
        return empty_queue;
    }
    PROCESS_QUEUE deleted = pm->deque[pm->rear];
    pm -> rear = (pm->rear - 1 + MAX_PROCESS) % MAX_PROCESS;
    pm->size--;
    return deleted;
}
