#include "../include/hashmap_batch.h"

typedef struct thread_args_t {
    batch *batch;
    hashmap *map;
} thread_args;

short create_batch(batch **batch, operation **operations, int size);
short handle_operation(operation *ops, hashmap *map);
void *handle_batch(void *arg);
void free_job(job *job);

short run_batch(int num_operations, int num_threads, hashmap *map) {
    printf("Running batch with %d operations using %d threads. mapsize: %d",
           num_operations, num_threads, map->size);
    return 0;
}

short create_operation(operation **operation, char *ops, char *key,
                       char *value) {
    *operation = malloc(sizeof(struct operation_t));
    if (operation == NULL) {
        return NOT_ENOUGH_MEMORY;
    }
    (*operation)->operation = ops;
    (*operation)->key = key;
    (*operation)->value = value;
    return 0;
}

short create_batch(batch **batch, operation **operations, int size) {
    *batch = malloc(sizeof(struct batch_t));
    if (batch == NULL) {
        return NOT_ENOUGH_MEMORY;
    }
    (*batch)->operations = operations;
    (*batch)->size = size;
    return 0;
}

short create_job(job **job, operation **operations, int num_ops,
                 int num_threads) {
    int needed_threads = num_threads;
    if (num_ops < num_threads) {
        needed_threads = num_ops;
    }
    *job = malloc(sizeof(struct job_t));
    if (job == NULL) {
        return NOT_ENOUGH_MEMORY;
    }

    batch **batches = malloc(sizeof(batch *) * needed_threads);
    int curr_ops = 0;
    for (int i = 0; i < needed_threads; i++) {
        int size = num_ops / needed_threads;
        if (i == needed_threads - 1) {
            size = num_ops % needed_threads;
        }
        operation **batch_ops = malloc(sizeof(operation *) * size);
        for (int j = 0; j < size; j++) {
            batch_ops[j] = operations[curr_ops + j];
        }
        batch *batch = NULL;
        create_batch(&batch, batch_ops, size);
        batches[i] = batch;

        curr_ops = curr_ops + size;
    }

    (*job)->batches = batches;
    (*job)->num_threads = needed_threads;
    return 0;
}

short handle_operation(operation *ops, hashmap *map) {
    if (strcmp(ops->operation, INSERT) == 0) {
        return hm_insert(ops->key, ops->value, map);
    } else if (strcmp(ops->operation, GET) == 0) {
        char *res = NULL;
        if (hm_get(ops->key, &res, map) < 0) {
            return KEY_DOES_NOT_EXIST;
        }
        return 0;
    } else if (strcmp(ops->operation, DELETE) == 0) {
        return hm_delete(ops->key, map);
    } else if (strcmp(ops->operation, UPDATE) == 0) {
        return hm_update(ops->key, ops->value, map);
    } else {
        return INVALID_COMMAND;
    }
}

void *handle_batch(void *arg) {
    thread_args *args = (thread_args *)arg;
    batch *batch = args->batch;
    hashmap *map = args->map;
    for (int i = 0; i < batch->size; i++) {
        operation *ops = batch->operations[i];
        short res = handle_operation(ops, map);
        if (res < 0) {
            printf("Operation %s, %s, %s failed with %d\n", ops->operation,
                   ops->key, ops->value, res);
        }
    }
    return NULL;
}

short handle_job(job *job, hashmap *map) {
    int num_threads = job->num_threads;
    pthread_t threads[num_threads];
    thread_args *args = malloc(sizeof(thread_args) * num_threads);
    for (int i = 0; i < job->num_threads; i++) {
        args[i].batch = job->batches[i];
        args[i].map = map;
        pthread_create(&threads[i], NULL, handle_batch, (void *)&args[i]);
    }
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
    free(args);
    free_job(job);
    return 0;
}

void free_job(job *job) {
    for (int i = 0; i < job->num_threads; i++) {
        for (int j = 0; j < job->batches[i]->size; j++) {
            free(job->batches[i]->operations[j]);
        }
        free(job->batches[i]);
    }
    free(job);
}
