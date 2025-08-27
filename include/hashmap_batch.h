#ifndef BATCH_H
#define BATCH_H

#include "errors.h"
#include <stdlib.h>

typedef struct operation_t {
    char *ops;
    char *key;
    char *value;
} operation;

typedef struct batch_t {
    operation **ops;
    int size;
} batch;

short create_operation(operation *ops, char *op, char *key, char *value);

short create_batch(batch *batch, operation **ops, int size);

short handle_operation(operation *ops);

short handle_batch(operation **ops, int num_threads);

#endif
