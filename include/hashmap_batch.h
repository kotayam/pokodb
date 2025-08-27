#ifndef BATCH_H
#define BATCH_H

#include "errors.h"
#include "hashmap.h"
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

#define BATCH "batch"

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

short run_batch(int num_operations, int num_threads, hashmap *map);

#endif
