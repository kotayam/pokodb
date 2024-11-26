#ifndef HASHMAP_H
#define HASHMAP_H

#include "errors.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define TABLE_SIZE 100

typedef unsigned int tb_size;

typedef struct key_value_t {
    char* key;
    char* value;
    struct key_value_t* next;
} key_value;

typedef struct hashmap_t {
    key_value** entries;
    tb_size size;
} hashmap;

short create_map(hashmap** map);

tb_size hash(char* key);

short insert(char* key, char* value, hashmap* map);

char* get(char* key, hashmap* map);

short delete(char* key, hashmap* map);

void print_map(hashmap* map);

void free_map(hashmap* map);

#endif