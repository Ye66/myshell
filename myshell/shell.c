//
//  shell.c
//  myshell
//
//  Copyright © 2018 樊晔. All rights reserved.
//

#include "shell.h"

#include "which.h"
#include "where.h"
#include "exit.h"
#include "pwd.h"
#include "pid.h"
#include "cd.h"
#include "prompt.h"
#include "list.h"
#include "printenv.h"
#include "alias.h"
#include "history.h"
#include "setenv.h"
#include "utils.h"
#include "kill.h"
#include "signal.h"

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>

char ** envs;
struct build_in_cmd build_in_cmds[] = {
    {.cmd_name = "which", .command = &cmd_which},
    {.cmd_name = "where", .command = &cmd_where},
    {.cmd_name = "exit", .command = &cmd_exit},
    {.cmd_name = "pwd", .command = &cmd_pwd},
    {.cmd_name = "pid", .command = &cmd_pid},
    {.cmd_name = "cd", .command = &cmd_cd},
    {.cmd_name = "prompt", .command = &cmd_prompt},
    {.cmd_name = "ls", .command = &cmd_list},
    {.cmd_name = "printenv", .command = &cmd_printenv},
    {.cmd_name = "alias", .command = &cmd_alias},
    {.cmd_name = "history", .command = &cmd_history},
    {.cmd_name = "setenv", .command = &cmd_setenv},
    {.cmd_name = "kill", .command = &cmd_kill},

    {.cmd_name = NULL, .command = NULL },
};

int execve_cmd(int argc, const char * argv[], char **envp, timeout) {
    if (argc == 0) {
        return 0;
    }
    char* real_cmd = NULL;
    if (is_path(argv[0])) {
        if (access(argv[0], X_OK) == 0) {
            real_cmd = dup_str(argv[0]);
        } else {
            fprintf(stderr, "cmd not found\n");
            return 1;
        }
    } else {
        real_cmd = find_cmd_in_path(argv[0]);
        if (!real_cmd) {
            fprintf(stderr, "cmd not found\n");
            return 1;
        }
    }
    printf("Executing [%s]\n", real_cmd);

    // Now we have the real command.
    pid_t pid;
    int ret;
    if (!(pid = fork())) {
        // This is a child.
        unignore_signal();
        execve(real_cmd, (char **) argv, envp);
        fprintf(stderr, "Fail to run cmd");
        ret = 1;
    } else {
        int status;
        waitpid(pid, &status, 0);
        if (status) {
            printf("%d\n", status);
        }
        ret = status;
    }
    free(real_cmd);
    return ret;
}

