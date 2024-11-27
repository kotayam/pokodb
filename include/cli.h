#ifndef CLI_H
#define CLI_H

#define _POSIX_C_SOURCE 199309L

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

#define WELCOME "\nWelcome to PokoDB!\n"
#define INSTRUCTION "For further instructions, please type help and press enter\n"
#define EXIT "SIGINT received.\n"

void cli_loop();

#endif