#ifndef ERRORS_H
#define ERRORS_H

#include <stdio.h>

// error codes for hashmap
#define NOT_ENOUGH_MEMORY -11
#define KEY_EXISTS -12
#define KEY_DOES_NOT_EXIST -13

// error message for hashmap
#define CREATE_MAP_ERROR "error creating map"
#define GET_ERROR "error in get"
#define INSERT_ERROR "error inserting"
#define BEFORE_ERROR "error in test before"
#define DELETE_ERROR "error deleting"
#define UPDATE_ERROR "error updating"
#define FAIL_TEST "test failed!\n"
#define PASS_TEST "test passed!\n"

// error codes for CLI
#define COMMAND_NOT_PROVIDED -21
#define READ_COMMAND_ERROR -22
#define COPY_COMMAND_ERROR -23
#define INVALID_COMMAND -24
#define KEY_OR_VALUE_NOT_PROVIDED -25
#define KEY_NOT_PROVIDED -26

// error message for CLI
#define SIGNAL_HANDLER_ERROR "failed to set signal handler\n"
#define COMMAND_ERROR "error with command"
#define EXECUTE_ERROR "error while executing command"

void print_error(short code, char* message);

#endif