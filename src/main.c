#include "../include/hashmap.h"
#include <stdio.h>

int main() {
    printf("hello world!\n");

    hashmap* map = NULL;
    int res = create_map(&map);
    if (res < 0) {
        printf("error creating map\n");
        free_map(map);
        return 0;
    }

    res = insert("test", "test", map);
    if (res < 0) {
        printf("error inserting\n");
        free_map(map);
        return 0;
    }

    free_map(map);
    return 0;
}