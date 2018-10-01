//
//  shell.h
//  myshell
//
//  Copyright © 2018 樊晔. All rights reserved.
//

#ifndef shell_h
#define shell_h

#include <stdio.h>
#include <time.h>

#define CMD_BUFFER_SIZE 128

int execve_cmd(int argc, const char * argv[], char **envp, int timeout);

extern pid_t child_pid;

struct build_in_cmd{
    char* cmd_name;
    int (*command)(int, const char* []);
};

extern char ** envs;

extern struct build_in_cmd build_in_cmds[];

#endif /* shell_h */
