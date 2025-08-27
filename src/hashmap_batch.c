#include "../include/hashmap_batch.h"

short create_operation(operation **ops, char *op, char *key, char *value) {
    *ops = malloc(sizeof(operation));
    if (ops == NULL) {
        return NOT_ENOUGH_MEMORY;
    }
    (*ops)->ops = op;
    (*ops)->key = key;
    (*ops)->value = value;
    return 0;
}

short create_batch(batch **batch, operation **ops, int size) {
    *batch = malloc(sizeof(batch));
    if (batch == NULL) {
        return NOT_ENOUGH_MEMORY;
    }
    (*batch)->ops = ops;
    (*batch)->size = size;
    return 0;
}

short handle_operation(operation *ops, hashmap *map) {
    if (strcmp(ops->ops, "insert") == 0) {
        return hm_insert(ops->key, ops->value, map);
    } else if (strcmp(ops->ops, "get") == 0) {
        char *res = NULL;
        if (hm_get(ops->key, &res, map) < 0) {
            return KEY_DOES_NOT_EXIST;
        }
        return 0;
    } else if (strcmp(ops->ops, "delete") == 0) {
        return hm_delete(ops->key, map);
    } else if (strcmp(ops->ops, "update") == 0) {
        return hm_update(ops->key, ops->value, map);
    } else {
        return INVALID_COMMAND;
    }
}

short handle_batch(operation **ops, int num_threads) {}

void free_batch(batch *batch) {
    for (int i = 0; i < batch->size; i++) {
        free(batch->ops[i]);
    }
    free(batch);
}
