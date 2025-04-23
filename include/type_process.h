#ifndef TYPE_PROCESS_H
#define TYPE_PROCESS_H
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int pid;
    int priority;
} PROCESS;

void initialize_process(PROCESS *p, int pid, int priority);

#endif