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

void print_delete_result(char* key) {
    printf("deleted key: %s\n", key);
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
        return;
    }

    print_map(map);
    free_map(map);
}

void insert_same_key_test() {
    print_test_name("insert same key test");
    hashmap* map = NULL;
    short res = create_map(&map);
    if (res < 0) {
        print_error(res, CREATE_MAP_ERROR);
        free_map(map);
        return;
    }

    res = insert("test", "test", map);
    if (res < 0) {
        print_error(res, INSERT_ERROR);
        free_map(map);
        return;
    }

    res = insert("test", "hello", map);
    if (res < 0) {
        print_error(res, INSERT_ERROR);
        printf(PASS_TEST);
        free_map(map);
        return;
    }

    printf(FAIL_TEST);
    free_map(map);
    return;
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

void delete_test() {
    print_test_name("delete test");

    hashmap* map = NULL;
    short res = before(&map);
    if (res < 0) {
        print_error(res, BEFORE_ERROR);
        return;
    }

    res = delete("hi", map);
    if (res < 0) {
        print_error(res, DELETE_ERROR);
        printf(FAIL_TEST);
        free_map(map);
        return;
    }
     print_delete_result("hi");
     print_map(map);

    res = delete("hello", map);
    if (res < 0) {
        print_error(res, DELETE_ERROR);
        printf(FAIL_TEST);
        free_map(map);
        return;
    }
    print_delete_result("hello");

    print_map(map);
    free_map(map);
}

void delete_same_key_test() {
    print_test_name("delete same key test");

    hashmap* map = NULL;
    short res = before(&map);
    if (res < 0) {
        print_error(res, BEFORE_ERROR);
        return;
    }

    res = delete("hi", map);
    if (res < 0) {
        print_error(res, DELETE_ERROR);
        printf(FAIL_TEST);
        free_map(map);
        return;
    }
    print_delete_result("hi");
    print_map(map);

    res = delete("hi", map);
    if (res < 0) {
        print_error(res, DELETE_ERROR);
        printf(PASS_TEST);
        free_map(map);
        return;
    }
    print_delete_result("hi");
    print_map(map);
    printf(FAIL_TEST);

    free_map(map);
}

void delete_and_insert_test() {
    print_test_name("delete and insert");

    hashmap* map = NULL;
    short res = create_map(&map);
    if (res < 0) {
        print_error(res, CREATE_MAP_ERROR);
        return;
    }

    res = delete("hello", map);
    if (res < 0) {
        print_error(res, DELETE_ERROR);
    } else {
        printf(FAIL_TEST);
    }
    print_map(map);

    // insert users
    char users[5][10] = {"Bob", "Patrick", "Jack", "Samantha", "Jolly"};
    for (int i = 0; i < 5; i++) {
        char str[8];
        sprintf(str, "%d", i);
        res = insert(str, users[i], map);
        if (res < 0) {
            print_error(res, INSERT_ERROR);
        }
    }
    print_map(map);

    // get users to check
    for (int i = 0; i < 5; i++) {
        char str[8];
        sprintf(str, "%d", i);
        char* name = get(str, map);
        if (name == NULL) {
            print_error(res, GET_ERROR);
            continue;
        }
        print_test_result(users[i], name);
    }

}