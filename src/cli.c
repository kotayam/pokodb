#include "../include/cli.h"

void write_prompt();
short get_operation(char **operation, char **arg_one, char **arg_two,
                    const char *cmd);
short execute_command(char *operation, char *arg_one, char *arg_two,
                      hashmap *map);
void free_command(char **operation, char **arg_one, char **arg_two);
void print_command(char *operation, char *arg_one, char *arg_two);
void print_message(short res);

volatile sig_atomic_t terminate = false;

void handle_sigint() { terminate = true; }

void cli_loop() {
    struct sigaction sa;
    sa.sa_handler = handle_sigint;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGINT, &sa, NULL) < 0) {
        printf(SIGNAL_HANDLER_ERROR);
        return;
    }

    hashmap *map = NULL;
    short res = create_map(&map);
    if (res < 0) {
        print_message(res);
        return;
    }
    printf(WELCOME);
    printf(INSTRUCTION);

    char *operation = NULL;
    char *arg_one = NULL;
    char *arg_two = NULL;

    while (true && !terminate) {
        write_prompt();

        char cmd[COMMAND_LENGTH];

        if (fgets(cmd, COMMAND_LENGTH, stdin) == NULL) {
            if (terminate) {
                printf(EXIT);
                break;
            }
            print_message(READ_COMMAND_ERROR);
            continue;
        }
        // if \n
        if (cmd[0] == '\n') {
            continue;
        }

        res = get_operation(&operation, &arg_one, &arg_two, cmd);
        if (res < 0) {
            print_message(res);
            free_command(&operation, &arg_one, &arg_two);
            continue;
        }

        res = execute_command(operation, arg_one, arg_two, map);
        if (res == 1) {
            break;
        } else if (res < 0) {
            print_message(res);
            free_command(&operation, &arg_one, &arg_two);
            continue;
        }

        free_command(&operation, &arg_one, &arg_two);
    }

    free_command(&operation, &arg_one, &arg_two);
    free_map(map);
}

void write_prompt() { printf(PROMPT); }

short get_operation(char **operation, char **arg_one, char **arg_two,
                    const char *cmd) {
    char *cmd_copy = strdup(cmd);
    if (cmd_copy == NULL) {
        return COPY_COMMAND_ERROR;
    }

    char *delimiters = " \t\n";

    char *res = strtok(cmd_copy, delimiters);
    if (res == NULL) {
        free(cmd_copy);
        return COMMAND_NOT_PROVIDED;
    }
    *operation = strdup(res);

    res = strtok(NULL, delimiters);
    if (res != NULL) {
        *arg_one = strdup(res);
    }

    res = strtok(NULL, delimiters);
    if (res != NULL) {
        *arg_two = strdup(res);
    }

    free(cmd_copy);
    return 0;
}

short execute_command(char *operation, char *arg_one, char *arg_two,
                      hashmap *map) {
    if (strcmp(operation, QUIT) == 0) {
        return 1;
    } else if (strcmp(operation, HELP) == 0) {
        printf(HELP_MESSAGE);
        return 0;
    } else if (strcmp(operation, INSERT) == 0) {
        if (arg_one == NULL || arg_two == NULL) {
            return KEY_OR_VALUE_NOT_PROVIDED;
        }
        return hm_insert(arg_one, arg_two, map);
    } else if (strcmp(operation, GET) == 0) {
        if (arg_one == NULL) {
            return KEY_NOT_PROVIDED;
        }
        char *res = NULL;
        if (hm_get(arg_one, &res, map) < 0) {
            return KEY_DOES_NOT_EXIST;
        } else {
            printf("%s\n", res);
            return 0;
        }
    } else if (strcmp(operation, UPDATE) == 0) {
        if (arg_one == NULL || arg_two == NULL) {
            return KEY_OR_VALUE_NOT_PROVIDED;
        }
        return hm_update(arg_one, arg_two, map);
    } else if (strcmp(operation, DELETE) == 0) {
        if (arg_one == NULL) {
            return KEY_NOT_PROVIDED;
        }
        return hm_delete(arg_one, map);
    } else if (strcmp(operation, PRINT) == 0) {
        print_map(map);
        return 0;
    } else if (strcmp(operation, BATCH) == 0) {
        if (arg_one == NULL || arg_two == NULL) {
            return NUM_OPS_THR_NOT_PROVIDED;
        }
        int num_operations = atoi(arg_one);
        int num_threads = atoi(arg_two);
        return run_batch(num_operations, num_threads, map);
    } else {
        return INVALID_COMMAND;
    }
}

void free_command(char **operation, char **arg_one, char **arg_two) {
    free(*operation);
    free(*arg_one);
    free(*arg_two);
    *operation = NULL;
    *arg_one = NULL;
    *arg_two = NULL;
}

void print_command(char *operation, char *arg_one, char *arg_two) {
    if (operation != NULL) {
        printf("operation: %s\n", operation);
    }

    if (arg_one != NULL) {
        printf("arg1: %s\n", arg_one);
    }

    if (arg_two != NULL) {
        printf("arg2: %s\n", arg_two);
    }
}

void print_message(short res) {
    switch (res) {
    case NOT_ENOUGH_MEMORY:
        printf("Error: Not enough memory\n");
        break;
    case KEY_EXISTS:
        printf("Error: Key already exists\n");
        break;
    case KEY_DOES_NOT_EXIST:
        printf("Error: Key does not exist\n");
        break;
    case COMMAND_NOT_PROVIDED:
        printf("Error: Command not provided\n");
        break;
    case READ_COMMAND_ERROR:
        printf("Error: Failed to read command\n");
        break;
    case COPY_COMMAND_ERROR:
        printf("Error: Failed to print command\n");
        break;
    case INVALID_COMMAND:
        printf("Error: Command not found\n");
        break;
    case KEY_OR_VALUE_NOT_PROVIDED:
        printf("Error: Missing key or value\n");
        break;
    case KEY_NOT_PROVIDED:
        printf("Error: Missing key\n");
        break;
    case NUM_OPS_THR_NOT_PROVIDED:
        printf("Error: Missing number of operations or number of threads\n");
        break;
    default:
        printf("An error occurred\n");
        break;
    }
}
