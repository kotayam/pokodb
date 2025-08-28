#ifndef CLI_H
#define CLI_H

#define _POSIX_C_SOURCE 200809L

#include "hashmap.h"
#include "hashmap_batch.h"
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COMMAND_LENGTH 4096

#define PROMPT "> "

// commands
#define QUIT "quit"
#define HELP "help"
#define PRINT "print"

#define WELCOME "\nWelcome to PokoDB!\n"
#define INSTRUCTION                                                            \
    "For further instructions, please type help and press enter\n"
#define EXIT "SIGINT received."
#define HELP_MESSAGE                                                           \
    "Here is the list of commands:\n"                                          \
    "- quit: quit the program.\n"                                              \
    "- help: show help.\n"                                                     \
    "- print: print out the stored data.\n"                                    \
    "- insert [key] [value]: insert value in key.\n"                           \
    "- get [key]: get value stored in key.\n"                                  \
    "- update [key] [value]: update the value in stored at key.\n"             \
    "- delete [key]: delete key.\n"                                            \
    "- batch [num_operations] [num_threads]: execute a batch of operations "   \
    "- using threads.\n"

void cli_loop();

#endif
