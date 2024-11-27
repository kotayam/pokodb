#include "hashmap_test.h"

int main() {
    hash_test();
    insert_test();
    get_test();
    insert_same_key_test();
    delete_test();
    delete_same_key_test();
    delete_and_insert_test();
    return 0;
}