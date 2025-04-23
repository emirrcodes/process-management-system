#include "../include/execution_functions.h"
#include <stdio.h>
#include <stdbool.h>

void read_process_file(const char *filename, PROCESS_MANAGER *pm) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open process file: %s\n", filename);
        return;
    }

    PROCESS_QUEUE temp_queue;
    initialize_process_queue(&temp_queue);

    char line[256];
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        PROCESS process = {0};
        int isHead;

        if (sscanf(line, "%d,%d,%d", &process.pid, &process.priority, &isHead) != 3) {
            continue;
        }

        if (isHead == 1 && !pq_isEmpty(&temp_queue)) {
            insert_rear(pm, temp_queue);
            initialize_process_queue(&temp_queue);
        }
        pq_enqueue(&temp_queue, process);
    }

    if (!pq_isEmpty(&temp_queue)) {
        insert_rear(pm, temp_queue);
    }

    fclose(file);
}

void read_insertion_file(const char *filename, INSERTION_QUEUE *eq) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open insertion file: %s\n", filename);
        return;
    }

    char line[256];
    PROCESS_QUEUE temp_queue;
    initialize_process_queue(&temp_queue);

    int current_iteration = -1;

    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        PROCESS process = {0};
        int iteration, isHead;

        if (sscanf(line, "%d,%d,%d,%d", &iteration, &process.pid, &process.priority, &isHead) != 4) {
            continue;
        }

        if (iteration != current_iteration) {
            if (current_iteration != -1 && !pq_isEmpty(&temp_queue)) {
                iq_enqueue(eq, temp_queue);
                initialize_process_queue(&temp_queue);
            }
            current_iteration = iteration;
        }

        if (isHead == 1 && !pq_isEmpty(&temp_queue)) {
            iq_enqueue(eq, temp_queue);
            initialize_process_queue(&temp_queue);
        }

        pq_enqueue(&temp_queue, process);
    }

    if (!pq_isEmpty(&temp_queue)) {
        iq_enqueue(eq, temp_queue);
    }

    fclose(file);
}

void execution_loop(PROCESS_MANAGER *pm, INSERTION_QUEUE *eq, FAILURE_STACK *fs) {
    int current_iteration = 0; 
    int max_iterations = 50;  

    while (!pm_isEmpty(pm) || !iq_isEmpty(eq)) {
        if (current_iteration > max_iterations) {
            printf("Error: Maximum iteration limit reached. Exiting loop...\n");
            break;
        }

        if (!iq_isEmpty(eq)) {
            PROCESS_QUEUE curr_iq = iq_peek(eq);
            if (current_iteration == curr_iq.iteration) {
                PROCESS_QUEUE arriving_queue = iq_dequeue(eq);
                if (!pq_isEmpty(&arriving_queue)) {
                    insert_rear(pm, arriving_queue);
                }
            }
        }

        if (!pm_isEmpty(pm)) {
            PROCESS_QUEUE current_queue = delete_front(pm);

            while (!pq_isEmpty(&current_queue)) {
                PROCESS process = pq_dequeue(&current_queue);

                if (process.pid <= 0 || process.priority < 0) {
                    continue;
                }

                if (process.pid % 8 == 0) { 
                    if (!pq_isEmpty(&current_queue)) {
                        push(fs, current_queue);
                    }
                    break;
                }
            }

            if (!pq_isEmpty(&current_queue)) {
                clear_queue(&current_queue);
            }
        }

        if (pm_isEmpty(pm) && iq_isEmpty(eq)) {
            break;
        }

        current_iteration++;
    }
}