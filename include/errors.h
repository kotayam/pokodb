#ifndef ERRORS_H
#define ERRORS_H

#include <stdio.h>

// error codes
#define NOT_ENOUGH_MEMORY -1
#define KEY_EXISTS -2

// error message
#define CREATE_MAP_ERROR "error creating map"
#define INSERT_ERROR "error inserting"
#define BEFORE_ERROR "error in test before"
#define FAIL_TEST "test failed!\n"
#define PASS_TEST "test passed!\n"

void print_error(short code, char* message);

#endif