#include "../include/hashmap.h"
#include <stdlib.h>

hashmap* create_map() {
    hashmap* map = malloc(sizeof(hashmap));
    map->entries = malloc(sizeof(key_value*) * TABLE_SIZE);
    return map;
}

void free_map(hashmap* map) {
    free(map->entries);
    free(map);
}