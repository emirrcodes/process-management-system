#include "../include/type_process.h"
#include <stdio.h>

void initialize_process(PROCESS *p, int pid, int priority){
    if (p == NULL){
        printf("Error : NULL pointer passed to initialize_process.\n");
        return;
    }
    p->pid = pid;
    p->priority = priority;
}

