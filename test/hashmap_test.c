#include "hashmap_test.h"

short before(hashmap** map) {
    short res = create_map(map);
    if (res < 0) {
        print_error(res, CREATE_MAP_ERROR);
        free_map(*map);
        return res;
    }

    res = insert("hi", "hi", *map);
    if (res < 0) {
        print_error(res, INSERT_ERROR);
        free_map(*map);
        return res;
    }

    res = insert("hello", "hello", *map);
    if (res <0) {
        print_error(res, INSERT_ERROR);
        free_map(*map);
        return res;
    }

    return 0;
}

void print_test_name(char* name) {
    printf("****%s****\n", name);
}

void print_test_result(char* expected, char* actual) {
    printf("expected: %s, actual: %s\n", expected, actual);
}

void print_hash_result(char* key, tb_size hash) {
    printf("hash: %s -> %d\n", key, hash);
}

void insert_test() {
    print_test_name("insert test");
    hashmap* map = NULL;
    short res = create_map(&map);
    if (res < 0) {
        print_error(res, CREATE_MAP_ERROR);
        free_map(map);
        return;
    }

    res = insert("hi", "hi", map);
    if (res < 0) {
        print_error(res, INSERT_ERROR);
        free_map(map);
        return;
    }

    res = insert("hello", "hello", map);
    if (res <0) {
        print_error(res, INSERT_ERROR);
        free_map(map);
    }

    print_map(map);

    free_map(map);
}

void get_test() {
    print_test_name("get test");
    hashmap* map = NULL;
    int res = before(&map);
    if (res < 0) {
        print_error(res, BEFORE_ERROR);
        return;
    }

    char* expected_one = "hi";
    char* actual_one = get(expected_one, map);
    if (actual_one == NULL) {
        printf(FAIL_TEST);
    } else {
        print_test_result(expected_one, actual_one);
    }

    char* expected_two = "hello";
    char* actual_two = get(expected_two, map);
    if (actual_two == NULL) {
        printf(FAIL_TEST);
    } else {
        print_test_result(expected_two, actual_two);
    }

    char* no_exist = get("test", map);
    if (no_exist == NULL) {
        printf(PASS_TEST);
    } else {
        print_test_result(NULL, no_exist);
    }

    free_map(map);
}

void hash_test() {
    print_test_name("hash test");
    char* key_one = "test";
    print_hash_result(key_one, hash(key_one));

    char* key_two = "hello";
    print_hash_result(key_two, hash(key_two));
}