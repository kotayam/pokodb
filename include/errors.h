#ifndef ERRORS_H
#define ERRORS_H

#include <stdio.h>

// error codes
#define NOT_ENOUGH_MEMORY -1
#define KEY_EXISTS -2
#define KEY_DOES_NOT_EXIST -3

// error message
#define CREATE_MAP_ERROR "error creating map"
#define GET_ERROR "error in get"
#define INSERT_ERROR "error inserting"
#define BEFORE_ERROR "error in test before"
#define DELETE_ERROR "error deleting"
#define UPDATE_ERROR "error updating"
#define FAIL_TEST "test failed!\n"
#define PASS_TEST "test passed!\n"

void print_error(short code, char* message);

#endif