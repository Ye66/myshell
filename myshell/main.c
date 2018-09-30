//
//  main.c
//  myshell
//
//  Created by 樊晔 on 2018/9/24.
//  Copyright © 2018 樊晔. All rights reserved.
//

#include <stdio.h>

#include <string.h>
#include <stdlib.h>
#include "shell.h"
#include "utils.h"
#include "prompt.h"
#include "alias.h"
#include "history.h"
#include "signal.h"

#define CMD_ARV_BUFFER_SIZE 128

int main(int argc, const char * argv[], char **envp) {
    envs = envp;
    char buffer[CMD_BUFFER_SIZE];
    char* cmd_argv[CMD_ARV_BUFFER_SIZE] = {NULL};
    ignore_signals();
    
    int timeout = -1;
    if (argc == 2) {
        timeout = atoi(argv[1]);
    }
    
    while (1) {
        print_prompt();
        if (!fgets(buffer, CMD_BUFFER_SIZE, stdin)){
            if (feof(stdin)) {
                clearerr(stdin);
                printf("\n");
                continue;
            }
            perror("command line too long");
            exit(1);
        }
        memset(cmd_argv, 0, CMD_ARV_BUFFER_SIZE);
        // Delete "\n".
        if(strlen(buffer) > 0)
             buffer[strlen(buffer)-1] = '\0';
        
        add_history(buffer);
        do_alias(buffer);
        
        int cmd_argc = 0;
        char * p;
        p = strtok(buffer, " ");
        if (!p) continue;
        do
        {
            if (cmd_argc >= CMD_ARV_BUFFER_SIZE){
                perror("too many arguments");
                exit(1);
            }
            cmd_argv[cmd_argc] = (char *) malloc(strlen(p) + 1);
            strcpy(cmd_argv[cmd_argc], p);
            cmd_argc++;
        } while ((p = strtok(NULL, " ")));
        
        // check if it's the build-in command
        struct build_in_cmd* cmd = NULL;
        if ((cmd = find_build_in_cmd(cmd_argv[0]))) {
            printf("Executing built-in [%s]\n", cmd->cmd_name);
            (*cmd->command)(cmd_argc, (const char**) cmd_argv);
        } else {
            execve_cmd(cmd_argc, (const char**) cmd_argv, envp, timeout);
        }
        
        for(int i = 0; i < cmd_argc; i++){
            free(cmd_argv[i]);
        }
    }

    return 0;
}
