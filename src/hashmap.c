#include "../include/hashmap.h"
#include "../include/errors.h"
#include <stdlib.h>

int create_map(hashmap** map) {
    *map = malloc(sizeof(hashmap)); 
    if (*map == NULL) {
        return NOT_ENOUGH_MEMORY;
    }

    (*map)->entries = malloc(sizeof(key_value*) * TABLE_SIZE);
    if ((*map)->entries == NULL) {
        return NOT_ENOUGH_MEMORY;
    }

    for (int i = 0; i < TABLE_SIZE; i++) {
        (*map)->entries[i] = NULL;
    }

    return 0;
}

void free_map(hashmap* map) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        // TODO: loop the next and free until reach last node
        free(map->entries[i]);
    }
    free(map->entries);
    free(map);
}