#include "../include/hashmap.h"
#include <stdio.h>

int main() {
    printf("hello world!");
    hashmap* map = create_map();
    free_map(map);
    return 0;
}