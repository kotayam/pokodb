#ifndef HASHMAP_TEST_H
#define HASHMAP_TEST_H

#include "../include/errors.h"
#include "../include/hashmap.h"
#include <stdio.h>
#include <stdlib.h>

extern int tests_failed;

#define PASS_TEST                                                              \
    do {                                                                       \
        printf("PASS\n");                                                      \
    } while (0)
#define FAIL_TEST                                                              \
    do {                                                                       \
        printf("FAIL\n");                                                      \
        tests_failed++;                                                        \
    } while (0)

void insert_test();

void insert_same_key_test();

void get_test();

void hash_test();

void delete_test();

void delete_same_key_test();

void delete_and_insert_test();

void update_test();

#endif
