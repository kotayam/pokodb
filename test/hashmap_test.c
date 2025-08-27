#include "hashmap_test.h"

int tests_failed = 0;

short before(hashmap **map) {
    short res = create_map(map);
    if (res < 0) {
        print_error(res, CREATE_MAP_ERROR);
        free_map(*map);
        return res;
    }

    res = hm_insert("hi", "hi", *map);
    if (res < 0) {
        print_error(res, INSERT_ERROR);
        free_map(*map);
        return res;
    }

    res = hm_insert("hello", "hello", *map);
    if (res < 0) {
        print_error(res, INSERT_ERROR);
        free_map(*map);
        return res;
    }

    return 0;
}

void print_test_name(char *name) { printf("****%s****\n", name); }

void print_test_result(char *expected, char *actual) {
    printf("expected: %s, actual: %s\n", expected, actual);
}

void print_hash_result(char *key, tb_size hash) {
    printf("hash: %s -> %d\n", key, hash);
}

void insert_test() {
    print_test_name("insert test");
    hashmap *map = NULL;
    short res = create_map(&map);
    if (res < 0) {
        FAIL_TEST;
        print_error(res, CREATE_MAP_ERROR);
        free_map(map);
        return;
    }

    res = hm_insert("hi", "hi", map);
    if (res < 0) {
        FAIL_TEST;
        print_error(res, INSERT_ERROR);
        free_map(map);
        return;
    }

    res = hm_insert("hello", "hello", map);
    if (res < 0) {
        FAIL_TEST;
        print_error(res, INSERT_ERROR);
        free_map(map);
        return;
    }
    PASS_TEST;
    free_map(map);
}

void insert_same_key_test() {
    print_test_name("insert same key test");
    hashmap *map = NULL;
    short res = create_map(&map);
    if (res < 0) {
        FAIL_TEST;
        print_error(res, CREATE_MAP_ERROR);
        return;
    }

    res = hm_insert("test", "test", map);
    if (res < 0) {
        FAIL_TEST;
        print_error(res, INSERT_ERROR);
        free_map(map);
        return;
    }

    res = hm_insert("test", "hello", map);
    if (res < 0) {
        PASS_TEST;
        print_error(res, INSERT_ERROR);
        free_map(map);
        return;
    }

    FAIL_TEST;
    free_map(map);
    return;
}

void get_test() {
    print_test_name("get test");
    hashmap *map = NULL;
    int res = before(&map);
    if (res < 0) {
        FAIL_TEST;
        print_error(res, BEFORE_ERROR);
        return;
    }

    char *expected_one = "hi";
    char *actual_one = NULL;
    if (hm_get(expected_one, &actual_one, map) < 0) {
        FAIL_TEST;
        print_test_result(expected_one, actual_one);
        free_map(map);
        return;
    }

    char *expected_two = "hello";
    char *actual_two = NULL;
    if (hm_get(expected_two, &actual_two, map) < 0) {
        FAIL_TEST;
        print_test_result(expected_two, actual_two);
        free_map(map);
        return;
    }

    char *no_exist = NULL;
    if (hm_get("test", &no_exist, map) < 0) {
        PASS_TEST;
    } else {
        FAIL_TEST;
        print_test_result(NULL, no_exist);
    }

    free_map(map);
}

void hash_test() {
    print_test_name("hash test");
    char *key_one = "test";
    print_hash_result(key_one, hash(key_one));

    char *key_two = "hello";
    print_hash_result(key_two, hash(key_two));
    PASS_TEST;
}

void delete_test() {
    print_test_name("delete test");

    hashmap *map = NULL;
    short res = before(&map);
    if (res < 0) {
        FAIL_TEST;
        print_error(res, BEFORE_ERROR);
        return;
    }

    res = hm_delete("hi", map);
    if (res < 0) {
        FAIL_TEST;
        print_error(res, DELETE_ERROR);
        free_map(map);
        return;
    }

    res = hm_delete("hello", map);
    if (res < 0) {
        FAIL_TEST;
        print_error(res, DELETE_ERROR);
        free_map(map);
        return;
    }

    PASS_TEST;
    free_map(map);
}

void delete_same_key_test() {
    print_test_name("delete same key test");

    hashmap *map = NULL;
    short res = before(&map);
    if (res < 0) {
        FAIL_TEST;
        print_error(res, BEFORE_ERROR);
        return;
    }

    res = hm_delete("hi", map);
    if (res < 0) {
        FAIL_TEST;
        print_error(res, DELETE_ERROR);
        free_map(map);
        return;
    }

    res = hm_delete("hi", map);
    if (res < 0) {
        PASS_TEST;
        print_error(res, DELETE_ERROR);
        free_map(map);
        return;
    }

    FAIL_TEST;
    free_map(map);
}

void delete_and_insert_test() {
    print_test_name("delete and insert test");

    hashmap *map = NULL;
    short res = create_map(&map);
    if (res < 0) {
        FAIL_TEST;
        print_error(res, CREATE_MAP_ERROR);
        return;
    }

    res = hm_delete("hello", map);
    if (res >= 0) {
        FAIL_TEST;
        print_error(res, DELETE_ERROR);
        return;
    }

    // insert users
    char users[5][10] = {"Bob", "Patrick", "Jack", "Samantha", "Jolly"};
    for (int i = 0; i < 5; i++) {
        char str[8];
        sprintf(str, "%d", i);
        res = hm_insert(users[i], str, map);
        if (res < 0) {
            FAIL_TEST;
            print_error(res, INSERT_ERROR);
            return;
        }
    }

    // get users to check
    for (int i = 0; i < 5; i++) {
        char str[8];
        sprintf(str, "%d", i);
        char *idx = NULL;
        if (hm_get(users[i], &idx, map) < 0) {
            FAIL_TEST;
            print_error(res, GET_ERROR);
            return;
        }
    }

    // delete users
    for (int i = 0; i < 5; i++) {
        res = hm_delete(users[i], map);
        if (res < 0) {
            FAIL_TEST;
            print_error(res, DELETE_ERROR);
            return;
        }
    }

    PASS_TEST;
    free_map(map);
}

void update_test() {
    print_test_name("update test");

    hashmap *map = NULL;
    short res = before(&map);
    if (res < 0) {
        FAIL_TEST;
        print_error(res, BEFORE_ERROR);
        return;
    }

    res = hm_update("hi", "new value!", map);
    if (res < 0) {
        FAIL_TEST;
        print_error(res, UPDATE_ERROR);
        free_map(map);
        return;
    }

    res = hm_update("hello", "Hello World!", map);
    if (res < 0) {
        FAIL_TEST;
        print_error(res, UPDATE_ERROR);
        free_map(map);
        return;
    }

    res = hm_update("no exist", "no exist", map);
    if (res < 0) {
        PASS_TEST;
        print_error(res, UPDATE_ERROR);
    } else {
        FAIL_TEST;
    }
    free_map(map);
}
