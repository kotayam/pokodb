#include "../include/hashmap.h"
#include "../include/errors.h"
#include <stdlib.h>
#include <stdio.h>

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

int insert(char* key, char* value, hashmap* map) {
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

    return 0;
}

char* get(char* key, hashmap* map) {
    
}

void print_map(hashmap* map) {
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