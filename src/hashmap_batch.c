#include "../include/hashmap_batch.h"
#include <stdio.h>

typedef struct operation_t {
    char *operation;
    char *key;
    char *value;
} operation;

typedef struct batch_t {
    operation **operations;
    int size;
} batch;

typedef struct job_t {
    batch **batches;
    int num_threads;
} job;

typedef struct thread_args_t {
    batch *batch;
    hashmap *map;
    int idx_thread;
} thread_args;

short generate_operations(int num_operations, operation ***operations);
short create_operation(operation **operation, char *ops, char *key,
                       char *value);

short create_job(job **job, operation **ops, int num_ops, int num_threads);
short create_batch(batch **batch, operation **operations, int size);

short handle_job(job *job, hashmap *map);
void *handle_batch(void *arg);
short handle_operation(operation *ops, hashmap *map);
char *str_operation(operation *ops);

void free_job(job *job);

short run_batch(int num_operations, int num_threads, hashmap *map) {
    printf("Running batch with %d operations using %d threads...\n",
           num_operations, num_threads);
    operation **operations = NULL;
    short res = generate_operations(num_operations, &operations);
    if (res < 0) {
        return res;
    }

    job *job = NULL;
    res = create_job(&job, operations, num_operations, num_threads);
    if (res < 0) {
        return res;
    }

    res = handle_job(job, map);
    if (res < 0) {
        return res;
    }

    free_job(job);
    return 0;
}

short generate_operations(int num_operations, operation ***operations) {
    *operations = malloc(sizeof(operation *) * num_operations);
    srand(time(NULL));
    for (int i = 0; i < num_operations; i++) {
        char *ops;
        int ops_rand = rand() % 4;
        switch (ops_rand) {
        case 0:
            ops = INSERT;
            break;
        case 1:
            ops = GET;
            break;
        case 2:
            ops = UPDATE;
            break;
        case 3:
            ops = DELETE;
            break;
        default:
            ops = INSERT;
        }

        int key_rand = rand() % 10;
        char *key = malloc(12);
        if (key == NULL) {
            free(operations);
            return NOT_ENOUGH_MEMORY;
        }
        sprintf(key, "%d", key_rand);

        int val_rand = rand() % 100;
        char *value = malloc(12);
        if (value == NULL) {
            free(key);
            free(operations);
            return NOT_ENOUGH_MEMORY;
        }
        sprintf(value, "%d", val_rand);

        short res = create_operation(&(*operations)[i], ops, key, value);
        if (res < 0) {
            // TODO: free
            return res;
        }
    }
    return 0;
}

short create_operation(operation **operation, char *ops, char *key,
                       char *value) {
    *operation = malloc(sizeof(struct operation_t));
    if (*operation == NULL) {
        return NOT_ENOUGH_MEMORY;
    }
    (*operation)->operation = ops;
    (*operation)->key = key;
    (*operation)->value = value;
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
            size = size + num_ops % needed_threads;
        }
        operation **batch_ops = malloc(sizeof(operation *) * size);
        for (int j = 0; j < size; j++) {
            batch_ops[j] = operations[curr_ops + j];
        }
        batch *batch = NULL;
        short res = create_batch(&batch, batch_ops, size);
        if (res < 0) {
            return res;
        }
        batches[i] = batch;

        curr_ops = curr_ops + size;
    }

    (*job)->batches = batches;
    (*job)->num_threads = needed_threads;
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

short handle_job(job *job, hashmap *map) {
    int num_threads = job->num_threads;
    pthread_t threads[num_threads];
    thread_args *args = malloc(sizeof(thread_args) * num_threads);
    for (int i = 0; i < job->num_threads; i++) {
        args[i].batch = job->batches[i];
        args[i].map = map;
        args[i].idx_thread = i;
        pthread_create(&threads[i], NULL, handle_batch, (void *)&args[i]);
    }
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
    free(args);
    return 0;
}

void *handle_batch(void *arg) {
    thread_args *args = (thread_args *)arg;
    batch *batch = args->batch;
    hashmap *map = args->map;
    int idx_thread = args->idx_thread;
    printf("**Thread %d started for batch size %d\n", idx_thread, batch->size);
    for (int i = 0; i < batch->size; i++) {
        operation *ops = batch->operations[i];
        short res = handle_operation(ops, map);
        if (res < 0) {
            printf("Thread %d: failed operation %s  with %d \n", idx_thread,
                   str_operation(ops), res);
        } else {
            printf("Thread %d: completed operation %s\n", idx_thread,
                   str_operation(ops));
        }
    }
    return NULL;
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

char *str_operation(operation *ops) {
    int len = 128;
    char *str = malloc(sizeof(char) * len);
    if (strcmp(ops->operation, GET) == 0 ||
        strcmp(ops->operation, DELETE) == 0) {
        snprintf(str, len, "[%s k=%s]", ops->operation, ops->key);
    } else if (strcmp(ops->operation, INSERT) == 0 ||
               strcmp(ops->operation, UPDATE) == 0) {
        snprintf(str, len, "[%s k=%s v=%s]", ops->operation, ops->key,
                 ops->value);
    }
    return str;
}

void free_job(job *job) {
    for (int i = 0; i < job->num_threads; i++) {
        batch *batch = job->batches[i];
        for (int j = 0; j < batch->size; j++) {
            operation *ops = batch->operations[j];
            free(ops->key);
            free(ops->value);
            free(ops);
        }
        free(batch->operations);
        free(batch);
    }
    free(job);
}
