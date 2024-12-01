#include "../include/cli.h"

void write_prompt();
short get_operation(char** operation, char** key, char** value, const char* cmd);
short execute_command(char* operation, char* key, char* value, hashmap* map);
void free_command(char** operation, char** key, char** value);
void print_command(char* operation, char* key, char* value);

volatile sig_atomic_t terminate = false;

void handle_sigint() {
    terminate = true;
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
            if (terminate) {
                printf(EXIT);
                break;
            }
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
            free_command(&operation, &key, &value);
            continue;
        }

        res = execute_command(operation, key, value, map);
        if (res == 1) {
            break;
        } else if (res < 0) {
            print_error(res, EXECUTE_ERROR);
            free_command(&operation, &key, &value);
            continue;
        }

        free_command(&operation, &key, &value);
    }

    free_command(&operation, &key, &value);
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

    char* delimiters = " \t\n";

    char* res = strtok(cmd_copy, delimiters);
    if (res == NULL) {
        free(cmd_copy);
        return COMMAND_NOT_PROVIDED;
    }
    *operation = strdup(res);

    res = strtok(NULL, delimiters);
    if (res != NULL) {
        *key = strdup(res);
    }

    res = strtok(NULL, delimiters);
    if (res != NULL) {
        *value = strdup(res);
    }

    free(cmd_copy);
    return 0;
}

short execute_command(char* operation, char* key, char* value, hashmap* map) {
    if (strcmp(operation, QUIT) == 0) {
        return 1;
    } else if (strcmp(operation, HELP) == 0) {
        printf(HELP_MESSAGE);
        return 0;
    } else if (strcmp(operation, INSERT) == 0) {
        return insert(key, value, map);
    } else if (strcmp(operation, GET) == 0) {
        char* res = get(key, map);
        if (res == NULL) {
            return KEY_DOES_NOT_EXIST;
        } else {
            printf("%s\n", res);
            return 0;
        }
    } else if (strcmp(operation, UPDATE) == 0) {
        return update(key, value, map);
    } else if (strcmp(operation, DELETE) == 0) {
        return delete(key, map);
    } else {
        return INVALID_COMMAND;
    }
}

void free_command(char** operation, char** key, char** value) {
    free(*operation);
    free(*key);
    free(*value);
    *operation = NULL;
    *key = NULL;
    *value = NULL;
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