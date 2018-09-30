//
//  alias.c
//  myshell
//
//  Copyright © 2018 樊晔. All rights reserved.
//

#include "alias.h"
#include "utils.h"
#include "shell.h"
#include <string.h>
#include <stdio.h>

#define MAX_ALIAS_NUM 128
#define MAX_ALIAS_LEN 128

struct alias_t all_alias[128] = { {.alias = NULL, .cmd = NULL } };

struct alias_t* find_alias(char* cmd);
void print_all_alias();
void append_to_all_alias(const char* a, const char* c);

/// lss ls /
/// lss ./ -> ls / ./
void do_alias(char* cmdline)  {
    char buffer[CMD_BUFFER_SIZE] = {0};
    memcpy(buffer, cmdline, CMD_BUFFER_SIZE);
    char * p;
    p = strtok(buffer, " ");
    if (!p) {
        return;
    }

    struct alias_t* a_ptr = find_alias(p);
    if (!a_ptr) return;
    
    // Handle alias too long.
    unsigned long cmd_line_str_len = strlen(cmdline);
    if (cmd_line_str_len + strlen(a_ptr->cmd) + 2 > CMD_BUFFER_SIZE) {
        fprintf(stderr, "Cmd too long");
        return;
    }
    
    memset(cmdline, 0, CMD_BUFFER_SIZE);

    strcat(cmdline, a_ptr->cmd);

    while ((p = strtok(NULL, " "))) {
        strcat(cmdline, " ");
        strcat(cmdline, p);
    }
}

int cmd_alias(int argc, const char* argv[]) {
    if (argc == 1) {
        print_all_alias();
    } else if (argc == 2) {
        append_to_all_alias(argv[1], "");
    } else {
        char buffer[MAX_ALIAS_LEN] = {0};
        for (int i = 2; i < argc; i++) {
            if (strlen(buffer) + strlen(argv[i]) + 2 > MAX_ALIAS_LEN) {
                fprintf(stderr, "alias: Alias too long");
                return 1;
            }
            strcat(buffer, argv[i]);
            strcat(buffer, " ");
        }
        append_to_all_alias(argv[1], buffer);
    }
    return 0;
}

struct alias_t* find_alias(char* cmd) {
    struct alias_t *a_ptr = all_alias;
    while (a_ptr->alias) {
        if (!strcmp(a_ptr->alias, cmd)) {
            return a_ptr;
        }
        a_ptr ++;
    }
    return NULL;
}

void print_all_alias() {
    struct alias_t *a_ptr = all_alias;
    while (a_ptr->alias) {
        printf("%s   %s\n", a_ptr->alias, a_ptr->cmd);
        a_ptr ++;
    }
}

void append_to_all_alias(const char* a, const char* c) {
    struct alias_t *a_ptr = all_alias;
    int idx = 0;
    while (a_ptr->alias) {
        a_ptr ++;
        idx ++;
    }
    if (idx >= MAX_ALIAS_NUM) {
        fprintf(stderr, "alias: Already have too many alias");
    }
    
    a_ptr->alias = dup_str(a);
    a_ptr->cmd = dup_str(c);
}
