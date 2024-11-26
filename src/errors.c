#include "../include/errors.h"

void print_error(short code, char* message) {
    printf("%d: %s\n", code, message);
}