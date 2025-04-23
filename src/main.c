#include <stdio.h>
#include "../include/process_manager.h"
#include "../include/insertion_queue.h"
#include "../include/failure_stack.h"
#include "../include/execution_functions.h"

void print_process_results(const char *status, PROCESS process) {
    printf("PID: %d, Priority: %d, Status: %s\n", process.pid, process.priority, status);
}

void print_failure_stack(FAILURE_STACK *fs) {
    if (fs_isEmpty(fs)) {
        printf("Failure stack is empty. No failed processes.\n");
        return;
    }

    printf("Failed processes in stack:\n");
    while (!fs_isEmpty(fs)) {
        PROCESS_QUEUE failed_queue = pop(fs);
        if (pq_isEmpty(&failed_queue)) {
            printf("Warning: Empty queue found in failure stack.\n");
            continue;
        }

        while (!pq_isEmpty(&failed_queue)) {
            PROCESS failed_process = pq_dequeue(&failed_queue);
            printf("PID: %d, Priority: %d\n", failed_process.pid, failed_process.priority);
        }
    }
}

int main() {
    PROCESS_MANAGER pm;
    INSERTION_QUEUE iq;
    FAILURE_STACK fs;

    initialize_process_manager(&pm);
    initialize_execution_queue(&iq);
    initialize_failed_stack(&fs);

    printf("Reading initial processes...\n");
    read_process_file("../initial_processes.txt", &pm);

    printf("Reading arriving processes...\n");
    read_insertion_file("../arriving_processes.txt", &iq);
    
    printf("Starting execution loop...\n");
    execution_loop(&pm, &iq, &fs);

    printf("Execution completed. Final results:\n");
    if (!fs_isEmpty(&fs)) {
        print_failure_stack(&fs);
    } else {
        printf("No failed processes.\n");
    }

    clear_failure_stack(&fs);
    return 0;
}