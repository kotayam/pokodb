#include "../include/hashmap.h"
#include "../include/errors.h"
#include <stdlib.h>

int create_map(hashmap** map) {
    hashmap* map_p = malloc(sizeof(hashmap)); 
    if (map_p == NULL) {
        return NOT_ENOUGH_MEMORY;
    }
    *map = map_p;

    key_value** entries_p = malloc(sizeof(key_value*) * TABLE_SIZE);
    if (entries_p == NULL) {
        return NOT_ENOUGH_MEMORY;
    }
    (*map)->entries = entries_p;

    return 0;
}

void free_map(hashmap* map) {
    free(map->entries);
    free(map);
}