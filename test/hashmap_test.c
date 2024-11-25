#include "hashmap_test.h"

void insert_test() {
    hashmap* map = NULL;
    int res = create_map(&map);
    if (res < 0) {
        printf(CREATE_MAP_ERROR);
        free_map(map);
        return;
    }

    res = insert("hi", "hi", map);
    if (res < 0) {
        printf(INSERT_ERROR);
        free_map(map);
        return;
    }

    res = insert("hello", "hello", map);
    if (res <0) {
        printf(INSERT_ERROR);
        free_map(map);
    }

    print_map(map);

    free_map(map);
}