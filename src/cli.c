#include "../include/cli.h"

void cli_loop() {
    hashmap* map = NULL;
    short res = create_map(&map);
    if (res < 0) {
        print_error(res, CREATE_MAP_ERROR);
        return;
    }
    printf(WELCOME);
    
    free_map(map);
}