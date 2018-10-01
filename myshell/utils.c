//
//  utils.c
//  myshell
//
//  Copyright © 2018 樊晔. All rights reserved.
//

#include "utils.h"

#include "shell.h"
#include "str_list.h"
#include "get_path.h"

#include <string.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

char* dup_str(const char* s) {
    char* ret = malloc(strlen(s) + 1);
    if (ret) strcpy(ret, s);
    return ret;
}

char* find_cmd_in_path(const char* cmd_in) {
    static struct str_list_node* p= NULL;
    static const char* cmd = NULL;
    static char* buffer = NULL;
    if (cmd_in) {
        p = get_path();
        cmd = cmd_in;
    }
    while (1) {
        if (!p) return NULL;
        unsigned long buffer_len = strlen(p->content) + strlen(cmd) + 2;
        buffer = (char*) malloc(buffer_len);
        memset(buffer, 0, buffer_len);
        sprintf(buffer, "%s/%s", p->content, cmd);
        p = p->next;
        if (access(buffer, X_OK) == 0) {
            return buffer;
        }
    }
}

// return a pointer to build-in command function
struct build_in_cmd* find_build_in_cmd(const char* cmd) {
    if(!cmd) return NULL;
    int i = 0;
    while (1) {
        if (!build_in_cmds[i].cmd_name) {
            break;
        }
        if(!strcmp(cmd, build_in_cmds[i].cmd_name)){
            return &build_in_cmds[i];
        }
        i++;
    }
    return NULL;
}
// check if str is a path
int is_path(const char* str) {
    if (str[0] == '/') {
        return 1;
    }
    if (str[0] == 0) return 0;

    if (str[0] == '.' && str[1] == '.') {
        return 1;
    }
    if (str[0] == '.' && str[1] == '/') {
        return 1;
    }
    return 0;
}
