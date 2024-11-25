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

int create_map(hashmap** map);

void hash();

int insert(char* key, char* value, hashmap* map);

void get();

void update();

void print_map(hashmap* map);

void free_map(hashmap* map);

#endif