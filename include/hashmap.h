#ifndef HASHMAP_H
#define HASHMAP_H

#define TABLE_SIZE 100

typedef struct key_value_t {
    char* key;
    char* value;
    struct key_value_t* next;
} key_value;

typedef struct hashmap_t {
    key_value** entries;
    int size;
} hashmap;

void constructor();

void hash();

void insert();

void get();

void update();

#endif