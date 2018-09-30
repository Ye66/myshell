//
//  pwd.c
//  myshell
//
//  Copyright © 2018 樊晔. All rights reserved.
//

#include "pwd.h"
#include <stdio.h>
#include <unistd.h>

#include "utils.h"

int cmd_pwd(int argc, const char* argv[]) {
    if (argc > 1) {
        fprintf(stderr, "pwd: Too many arguments\n");
    }
    char buffer[CWD_MAX_PATH_LEN] = {};
    const char* p = getcwd(buffer, CWD_MAX_PATH_LEN);
    printf("%s\n", p);
    return 0;
}
