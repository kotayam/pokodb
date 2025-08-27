#include "../include/hashmap_batch.h"

short create_operation(operation *ops, char *op, char *key, char *value) {
    ops = malloc(sizeof(operation));
    if (ops == NULL) {
        return NOT_ENOUGH_MEMORY;
    }
    ops->ops = op;
    ops->key = key;
    ops->value = value;
    return 0;
}

short create_batch(batch *batch, operation **ops, int size) {}

short handle_operation(operation *ops) {}

short handle_batch(operation **ops, int num_threads) {}
