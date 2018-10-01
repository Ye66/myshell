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
#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <string.h>

char ** envs;
pid_t child_pid;

void sig_handler(int signo);
// store all build-in commands
struct build_in_cmd build_in_cmds[] = {
    {.cmd_name = "which", .command = &cmd_which},
    {.cmd_name = "where", .command = &cmd_where},
    {.cmd_name = "exit", .command = &cmd_exit},
    {.cmd_name = "pwd", .command = &cmd_pwd},
    {.cmd_name = "pid", .command = &cmd_pid},
    {.cmd_name = "cd", .command = &cmd_cd},
    {.cmd_name = "prompt", .command = &cmd_prompt},
    {.cmd_name = "list", .command = &cmd_list},
    {.cmd_name = "printenv", .command = &cmd_printenv},
    {.cmd_name = "alias", .command = &cmd_alias},
    {.cmd_name = "history", .command = &cmd_history},
    {.cmd_name = "setenv", .command = &cmd_setenv},
    {.cmd_name = "kill", .command = &cmd_kill},

    {.cmd_name = NULL, .command = NULL },
};

// execute command in PATH
int execve_cmd(int argc, const char * argv[], char **envp, int timeout) {
    if (argc == 0) {
        return 0;
    }
    child_pid = -1;
    char* real_cmd = NULL;
    if (is_path(argv[0])) {
        if (access(argv[0], X_OK) == 0) {
            real_cmd = dup_str(argv[0]);
        } else {
            fprintf(stderr, "Path doesn't exist\n");
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
        child_pid = pid;
        // set a timer
        timer_t timerid;
        if (timeout > 0)
        {
            struct sigevent evp;
            struct sigaction act;
            memset(&act, 0, sizeof(act));
            act.sa_handler = sig_handler;
            act.sa_flags = 0;
            sigemptyset(&act.sa_mask);

            if (sigaction(SIGUSR1, &act, NULL) == -1)
            {
                perror("fail to sigaction");
                exit(-1);
            }
            memset(&evp, 0, sizeof(struct sigevent));
            evp.sigev_signo = SIGUSR1;
            evp.sigev_notify = SIGEV_SIGNAL;
            if (timer_create(CLOCK_REALTIME, &evp, &timerid) == -1)
            {
                perror("fail to timer_create");
                exit(-1);
            }
            struct itimerspec it;
            it.it_interval.tv_sec = timeout;
            it.it_interval.tv_nsec = 0;
            it.it_value.tv_sec = timeout;
            it.it_value.tv_nsec = 0;
            if (timer_settime(timerid, 0, &it, 0) == -1) {
                perror("fail to timer_settime");
                exit(-1);
            }
        }
        int status;
        waitpid(pid, &status, WUNTRACED);
        child_pid = -1;
        if (status) {
            printf("%d\n", status);
        }
        if (timeout > 0) {
            timer_delete(timerid);
        }
        ret = status;
    }
    free(real_cmd);
    return ret;
}

void sig_handler(int signo) {
    if(child_pid > 0) {
        kill(child_pid, SIGTERM);
        printf("!!! taking too long to execute this command !!!\n");
    }
}

