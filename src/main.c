#include "../include/hashmap.h"
#include "../include/errors.h"
#include <stdio.h>

int main() {
    hashmap* map = NULL;
    int res = create_map(&map);
    if (res < 0) {
        printf(CREATE_MAP_ERROR);
        free_map(map);
        return 0;
    }

    res = insert("hi", "hi", map);
    if (res < 0) {
        printf(INSERT_ERROR);
        free_map(map);
        return 0;
    }

    res = insert("hello", "hello", map);
    if (res <0) {
        printf(INSERT_ERROR);
        free_map(map);
    }

    print_map(map);

    free_map(map);
    return 0;
}