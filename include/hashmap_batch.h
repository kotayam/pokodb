#ifndef BATCH_H
#define BATCH_H

#include "errors.h"
#include "hashmap.h"
#include <stdlib.h>
#include <string.h>

typedef struct operation_t {
    char *ops;
    char *key;
    char *value;
} operation;

typedef struct batch_t {
    operation **ops;
    int size;
} batch;

short create_operation(operation **ops, char *op, char *key, char *value);

short create_batch(batch **batch, operation **ops, int size);

short handle_operation(operation *ops, hashmap *map);

short handle_batch(operation **ops, int num_threads);

void free_batch(batch *batch);

#endif
