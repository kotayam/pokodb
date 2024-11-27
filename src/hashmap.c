#include "../include/hashmap.h"

short create_map(hashmap** map) {
    *map = malloc(sizeof(hashmap)); 
    if (*map == NULL) {
        return NOT_ENOUGH_MEMORY;
    }

    (*map)->size = 0;
    (*map)->entries = malloc(sizeof(key_value*) * TABLE_SIZE);
    if ((*map)->entries == NULL) {
        return NOT_ENOUGH_MEMORY;
    }

    for (int i = 0; i < TABLE_SIZE; i++) {
        (*map)->entries[i] = NULL;
    }


    return 0;
}

tb_size hash(char* key) {
    tb_size hash = 5381;
    int c;

    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash % TABLE_SIZE;
}

short insert(char* key, char* value, hashmap* map) {
    char* val = get(key, map);
    if (val != NULL) {
        return KEY_EXISTS;
    } 

    tb_size index = hash(key);

    // save first node
    key_value* node = map->entries[index];

    // create new node
    key_value* new = malloc(sizeof(key_value));
    if (new == NULL) {
        return NOT_ENOUGH_MEMORY;
    }
    char* key_copy = strdup(key);
    if (key_copy == NULL) {
        return NOT_ENOUGH_MEMORY;
    }
    char* value_copy = strdup(value);
    if (value_copy == NULL) {
        free(key_copy);
        return NOT_ENOUGH_MEMORY;
    }
    new->key = key_copy;
    new->value = value_copy;
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
    tb_size index = hash(key);

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

short delete(char* key, hashmap* map) {
    tb_size index = hash(key);
    
    key_value* curr = map->entries[index];
    if (curr == NULL) {
        return KEY_DOES_NOT_EXIST;
    }
    if (strcmp(curr->key, key) == 0) {
        // first is match
        map->entries[index] = curr->next;
        free(curr->key);
        free(curr->value);
        free(curr);
        map->size--;
        return 0;
    }
    key_value* prev = curr;
    curr = curr->next;
    while (curr != NULL) {
        bool match = strcmp(curr->key, key) == 0;
        if (!match) {
            // check next
            prev = curr;
            curr = curr->next;
        } else {
            // delete curr node
            prev->next = curr->next;
            free(curr->key);
            free(curr->value);
            free(curr);
            curr = NULL;
            map->size--;
            return 0;
        }
    }

    return KEY_DOES_NOT_EXIST;
}

short update(char* key, char* value, hashmap* map) {
    tb_size index = hash(key);

    key_value* node = map->entries[index];
    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            char* value_copy = strdup(value);
            if (value_copy == NULL) {
                return NOT_ENOUGH_MEMORY;
            }
            char* old = node->value;
            node->value = value_copy;
            free(old);
            return 0;
        }
        node = node->next;
    }

    return KEY_DOES_NOT_EXIST;
}

void print_map(hashmap* map) {
    printf("MAP SIZE: %d\n", map->size);
    for (int i = 0; i < TABLE_SIZE; i++) {
        key_value* node = map->entries[i];
        while (node != NULL) {
            printf("KEY: %s, VALUE: %s\n", node->key, node->value);
            node = node->next;
        }
    }
}

void free_map(hashmap* map) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        key_value* node = map->entries[i];
        while (node != NULL) {
            key_value* next = node->next;
            free(node->key);
            free(node->value);
            free(node);
            node = next;
        }
    }
    free(map->entries);
    free(map);
}