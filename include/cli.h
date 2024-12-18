#ifndef CLI_H
#define CLI_H

#define _POSIX_C_SOURCE 200809L

#include "hashmap.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>


#define COMMAND_LENGTH 4096

#define PROMPT "> "

// commands
#define QUIT "quit"
#define HELP "help"
#define INSERT "insert"
#define GET "get"
#define UPDATE "update"
#define DELETE "delete"
#define PRINT "print"

#define WELCOME "\nWelcome to PokoDB!\n"
#define INSTRUCTION "For further instructions, please type help and press enter\n"
#define EXIT "SIGINT received."
#define HELP_MESSAGE "Here is the list of commands:\n"

void cli_loop();

#endif