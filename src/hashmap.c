#include "../include/hashmap.h"

short create_map(hashmap** map) {
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

unsigned int hash(char* key) {
    unsigned int hash = 5381;
    int c;

    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash % TABLE_SIZE;
}

short insert(char* key, char* value, hashmap* map) {
    // TODO: hash key to identify index in entries array
    int index = 0;

    // save first node
    key_value* node = map->entries[index];

    // create new node
    key_value* new = malloc(sizeof(key_value));
    if (new == NULL) {
        return NOT_ENOUGH_MEMORY;
    }
    new->key = key;
    new->value = value;
    new->next = NULL;

    // insert to front
    map->entries[index] = new;
    if (node != NULL) {
        new->next = node;
    }

    map->size++;

    return 0;
}

char* get(char* key, hashmap* map) {
    //TODO: find index by hash
    int index = 0;

    // get first node
    key_value* node = map->entries[index];
    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            return node->value;
        }
        node = node->next;
    }
    return NULL;
}

void print_map(hashmap* map) {
    printf("map size: %d\n", map->size);
    for (int i = 0; i < TABLE_SIZE; i++) {
        key_value* node = map->entries[i];
        while (node != NULL) {
            printf("Key: %s, Value: %s\n", node->key, node->value);
            node = node->next;
        }
    }
}

void free_map(hashmap* map) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        key_value* node = map->entries[i];
        while (node != NULL) {
            key_value* next = node->next;
            free(node);
            node = next;
        }
    }
    free(map->entries);
    free(map);
}