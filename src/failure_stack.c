#include "../include/failure_stack.h"
#include <stdio.h>
#include <stdbool.h>

void initialize_failed_stack(FAILURE_STACK *fs){
    fs->top = -1;
}

bool fs_isFull(FAILURE_STACK *fs){
    return fs->top == MAX_FAILED-1;
}

bool fs_isEmpty(FAILURE_STACK *fs){
    return fs->top == -1;
}

void push(FAILURE_STACK *fs, PROCESS_QUEUE data){
    if(fs_isFull(fs)){
        printf("Error: Cannot push to a full stack.\n");
        return;
    }
    fs->stack[++fs->top] = data;
}

PROCESS_QUEUE pop(FAILURE_STACK *fs){
    if(fs_isEmpty(fs)){
        printf("Error: Cannot push to a full stack.\n");
        PROCESS_QUEUE empty_queue;
        initialize_process_queue(&empty_queue);
        return empty_queue;
    }
    PROCESS_QUEUE popped = fs->stack[fs->top];
    fs->top--;
    return popped;
}

void clear_failure_stack(FAILURE_STACK *fs) {
    while (!fs_isEmpty(fs)) {
        PROCESS_QUEUE failed_queue = pop(fs);
        clear_queue(&failed_queue);
    }
}