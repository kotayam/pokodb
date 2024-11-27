#include "../include/cli.h"

void write_prompt();
short get_operation(char** operation, char** key, char** value, const char* cmd);
short execute_command(char* operation, char* key, char* value);
void quit();
void free_command(char* operation, char* key, char* value);
void print_command(char* operation, char* key, char* value);

volatile sig_atomic_t terminate = 0;

void handle_sigint() {
    terminate = 1;
    printf(EXIT);
}

void cli_loop() {
    struct sigaction sa;
    sa.sa_handler = handle_sigint;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGINT, &sa, NULL) < 0) {
        printf(SIGNAL_HANDLER_ERROR);
        return;
    }

    hashmap* map = NULL;
    short res = create_map(&map);
    if (res < 0) {
        print_error(res, CREATE_MAP_ERROR);
        return;
    }
    printf(WELCOME);
    printf(INSTRUCTION);

    char* operation = NULL;
    char* key = NULL;
    char* value = NULL;

    while(true && !terminate) {
        write_prompt();

        char cmd[COMMAND_LENGTH];
        
        if (fgets(cmd, COMMAND_LENGTH, stdin) == NULL) {
            print_error(READ_COMMAND_ERROR, COMMAND_ERROR);
            continue;
        }
        // if \n
        if (cmd[0] == '\n') {
            continue;
        }

        res = get_operation(&operation, &key, &value, cmd);
        if (res < 0) {
            print_error(res, COMMAND_ERROR);
            free_command(operation, key, value);
            continue;
        }
        print_command(operation, key, value);

        res = execute_command(operation, key, value);
        if (res == 1) {
            break;
        } else if (res < 0) {
            print_error(res, EXECUTE_ERROR);
            free_command(operation, key, value);
            continue;
        }

        free_command(operation, key, value);
    }

    free_command(operation, key, value);
    free_map(map);
}

void write_prompt() {
    printf(PROMPT);
}

short get_operation(char** operation, char** key, char** value, const char* cmd) {
    char* cmd_copy = strdup(cmd);
    if (cmd_copy == NULL) {
        return COPY_COMMAND_ERROR;
    }

    char* res = strtok(cmd_copy, " ");
    if (res == NULL) {
        free(cmd_copy);
        return COMMAND_NOT_PROVIDED;
    }
    *operation = strdup(res);

    res = strtok(NULL, " ");
    if (res != NULL) {
        *key = strdup(res);
    }

    res = strtok(NULL, " ");
    if (res != NULL) {
        *value = strdup(res);
    }

    free(cmd_copy);
    return 0;
}

short execute_command(char* operation, char* key, char* value) {
    if (strcmp(operation, QUIT) == 0) {
        return 1;
    } else if (strcmp(operation, HELP) == 0) {
        
    }
    return INVALID_COMMAND;
}

void free_command(char* operation, char* key, char* value) {
    free(operation);
    free(key);
    free(value);
}

void print_command(char* operation, char* key, char* value) {
    if (operation != NULL) {
        printf("operation: %s\n", operation);
    }

    if (key != NULL) {
        printf("key: %s\n", key);
    }

    if (value != NULL) {
        printf("value: %s\n", value);
    }
}