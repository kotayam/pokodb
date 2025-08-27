#include "hashmap_test.h"

int main() {
    hash_test();
    insert_test();
    get_test();
    insert_same_key_test();
    delete_test();
    delete_same_key_test();
    delete_and_insert_test();
    update_test();

    if (tests_failed > 0) {
        printf("Failed %d tests.\n", tests_failed);
        return 1;
    }
    printf("All tests passed!\n");
    return 0;
}
