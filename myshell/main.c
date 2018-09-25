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

#define BUFFER_SIZE 128
#define CMD_ARV_BUFFER_SIZE 128

int main(int argc, const char * argv[]) {
    char buffer[BUFFER_SIZE];
    char* cmd_argv[CMD_ARV_BUFFER_SIZE];
    
    while (1) {
        if (!fgets(buffer, BUFFER_SIZE, stdin)){
            perror("command line too long");
            exit(1);
        }
        int cmd_argc = 0;
        char * p;
        p = strtok(buffer, " ");
        
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
        
    }
    return 0;
}
