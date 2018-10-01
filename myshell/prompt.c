//
//  prompt.c
//  myshell
//
//  Copyright © 2018 樊晔. All rights reserved.
//

#include "prompt.h"
#include "utils.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define MAX_PROMPT_LEN 128

void print_cwd();
char prompt[MAX_PROMPT_LEN] = { 0 };

// command prompt
int cmd_prompt(int argc, const char* argv[]) {
    if (argc > 2) {
        fprintf(stderr, "prompt: Too many arguments\n");
    }
    if (argc == 1) {
        printf("input prompt prefix: ");
        if (!fgets((char*) prompt, MAX_PROMPT_LEN, stdin)){
            perror("prompt line too long");
            return 1;
        }
        int len = 0;
        if ((len = (int)strlen(prompt)) > 0) {
            prompt[len - 1] = 0;
        }
    } else {
        if (strlen(argv[1]) >= MAX_PROMPT_LEN) {
            perror("prompt line too long");
            return 1;
        }
        strcpy(prompt, argv[1]);
    }
    return 0;
}

void print_cwd() {
    char buffer[CWD_MAX_PATH_LEN] = {};
    const char* p = getcwd(buffer, CWD_MAX_PATH_LEN);
    printf(" [%s] ", p);
}

void print_prompt() {
    printf("%s", prompt);
    print_cwd();
}

