//
//  printenv.c
//  myshell
//
//  Copyright © 2018 樊晔. All rights reserved.
//

#include "printenv.h"
#include "shell.h"

#include <stdlib.h>
#include <string.h>

// 1 argument: print all env
// 2 arguments: print a particular env
int cmd_printenv(int argc, const char* argv[]) {
    if (argc == 1) {
        char** env = envs;
        while (*env) {
            printf("%s\n", *(env++));
        }
    } else if (argc == 2){
        char* p = getenv(argv[1]);
        if (p) printf("%s\n", p);

    } else {
        fprintf(stderr, "printenv: Too many arguments\n");
        return 1;
    }
    return 0;
}
