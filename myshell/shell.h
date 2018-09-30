//
//  shell.h
//  myshell
//
//  Copyright © 2018 樊晔. All rights reserved.
//

#ifndef shell_h
#define shell_h

#include <stdio.h>

#define CMD_BUFFER_SIZE 128

struct build_in_cmd{
    char* cmd_name;
    int (*command)(int, const char* []);
};

extern char ** envs;
extern struct build_in_cmd build_in_cmds[];

int execve_cmd(int argc, const char * argv[], char **envp, int timeout);

#endif /* shell_h */
